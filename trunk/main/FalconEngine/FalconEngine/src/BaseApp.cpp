#include "stdafx.h"
#include "BaseApp.h"
#include "LogManager.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "GameObject.h"

#include "InputStateManager.h"
#include "Shader.h"
#include "FalconMath.h"
#include "CallCenter.h"
#include "Button.h"
#include "Element2D.h"
#include "Menu.h"
#include "Element2DManager.h"
#include "SoundManager.h"
#include "FalconFont.h"
#include <boost\thread.hpp>

//////////////////////////////////////////////////////////////////////////
///						LUA REGISTRATION							   ///
//////////////////////////////////////////////////////////////////////////
luabind::scope falcon::BaseApp::Register()
{
	return
		luabind::class_<BaseApp>("BaseApp")
		.def(luabind::constructor<std::string>())
		.def("Run", &BaseApp::Run)
		.property("scene", &BaseApp::GetScene, &BaseApp::SetScene)
		.property("resourceManager", &BaseApp::GetResourceManager, &BaseApp::SetResourceManager)
		.def("Create", &BaseApp::Create)
		.def("Load", &BaseApp::Load);
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static falcon::BaseApp* app = 0;

	switch( msg )
	{
		case WM_CREATE:
		{
			// Get the 'this' pointer we passed to CreateWindow via the lpParam parameter.
			CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
			app = (falcon::BaseApp*)cs->lpCreateParams;
			return 0;
		}
	}

	// Don't start processing messages until after WM_CREATE.
	if( app )
		return app->MsgProc(msg, wParam, lParam);
	else
		return DefWindowProc(hwnd, msg, wParam, lParam);
}

falcon::BaseApp::BaseApp(std::string title):
	m_hAppInst(nullptr),
	m_hMainWnd(nullptr),
	m_hDC(nullptr),
	m_hRC(nullptr),
	m_appPaused(false),
	m_minimized(false),
	m_maximized(false),
	m_resizing(false),
	m_exit(false),
	m_clientWidth(1280),
	m_clientHeight(720),
	m_title(title),
	m_scene(nullptr),
	m_rm(nullptr)
{
}

falcon::BaseApp::~BaseApp()
{
 //delete BEFORE rendercontext has been deleted!!
}

bool falcon::BaseApp::Create()
{
	GLuint		PixelFormat;
	WNDCLASS	wc;

	m_hAppInst			= GetModuleHandle(nullptr);
	wc.style			= CS_HREDRAW | CS_VREDRAW;				// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= MainWndProc;							// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= m_hAppInst;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);		// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= (HBRUSH)GetStockObject(NULL_BRUSH);	// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= m_title.c_str();						// Set The Class Name

	//Register The Window Class
	if (!RegisterClass(&wc))									
	{
		LOG(LOG_Error, "Failed To Register The Window Class");
		return false;
	}
	
	RECT R = { 0, 0, m_clientWidth, m_clientHeight };
    AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int width  = R.right - R.left;
	int height = R.bottom - R.top;

	// Create The Window
	m_hMainWnd = CreateWindowEx(NULL,m_title.c_str(), m_title.c_str(), 
		WS_OVERLAPPEDWINDOW, GetSystemMetrics(SM_CXSCREEN)/2 - width/2, GetSystemMetrics(SM_CYSCREEN)/2 - height/2, width, height, 0, 0, m_hAppInst, this); 
	
	if( !m_hMainWnd )
	{
		LOG(LOG_Error, "Window Creation Error.");
		KillWindow();
		return false;
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		32,											// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	//Get A Device Context?
	m_hDC=GetDC(m_hMainWnd);
	if (!m_hDC)
	{
		KillWindow();
		LOG(LOG_Error,"Can't Create A GL Device Context.");
		return false;
	}
	//Find A Matching Pixel Format
	PixelFormat=ChoosePixelFormat(m_hDC,&pfd);
	if (!PixelFormat)
	{	
		KillWindow();
		LOG(LOG_Error,"Can't Find A Suitable PixelFormat.");
		return false;
	}
	//Set The Pixel Format
	if(!SetPixelFormat(m_hDC,PixelFormat,&pfd))
	{
		KillWindow();
		LOG(LOG_Error,"Can't Set The PixelFormat.");
		return false;
	}
	//Get A Rendering Context
	m_hRC=wglCreateContext(m_hDC);
	if (!m_hRC)
	{
		KillWindow();
		LOG(LOG_Error,"Can't Create A GL Rendering Context.");
		return false;
	}
	//Activate The Rendering Context
	if(!wglMakeCurrent(m_hDC,m_hRC))
	{
		KillWindow();
		LOG(LOG_Error,"Can't Activate The GL Rendering Context.");
		return false;
	}

	ShowWindow(m_hMainWnd,SW_SHOW);
	// Give Window Priority
	SetForegroundWindow(m_hMainWnd);
	// Set Keyboard Focus To The Window
	SetFocus(m_hMainWnd);
	// Set Up Our Perspective openGL Screen
	Resize();

	// Create an inputStateManager
	InputStateManager::Create();

	if (!InitOpenGL())
	{
		KillWindow();
		LOG(LOG_Error,"Initialization Failed.");
		return false;
	}

	//setup scene and resourcemanager
	m_rm = new ResourceManager((float)m_clientWidth, (float)m_clientHeight);
 	m_scene = new Scene();
 	m_scene->Init();

	CallCenter::Create();

	m_rm->LoadFont("./data/fonts/arial.ttf", 32);
	m_font = m_rm->GetFont("./data/fonts/arial.ttf");

	SoundManager::GetInstance()->LoadSound("./data/sounds/Kalimba.mp3", "Song");
	SoundManager::GetInstance()->Play_Sound("Song");

	//m_font->printString("Test", 100, 250);

	return true;	
}

void falcon::BaseApp::Resize()
{
	if (m_clientHeight==0)// Prevent A Divide By Zero By
	{
		m_clientHeight=1;
	}
}

int falcon::BaseApp::Run()
{
	MSG msg = {0};
	while(!m_exit)
	{
		// If there are Window messages then process them.
		//else do Game stuff
		if(PeekMessage( &msg, 0, 0, 0, PM_REMOVE ))
		{
            if (msg.message==WM_QUIT)
			{
				m_exit=true;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
        {	
			if( !m_appPaused )
			{
				Update();
				Render();
				SwapBuffers(m_hDC);
			}
			else
				Sleep(50);

        }
    }
	KillWindow();
	return (int)msg.wParam;
}

void falcon::BaseApp::Render() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(m_scene != NULL)
	{
		m_scene->Render();

		std::stringstream b;
		b << "Fps = " << m_scene->GetFPS();
		//OutputDebugString(b.str().c_str());
		//boost::thread stringthr(&FalconFont::printString, m_rm->GetFont("./data/fonts/8bitoperator_jve.ttf"), b.str().c_str(), 100, 250);
		m_font->printString(b.str().c_str(), 5, 5);
		//m_font->printString("Test!", 100, 250);
		//m_font->printString("This is a very long sentence to test the performance of the text rendering engine. The more letters we draw, the heavier it is for the engine!", 100, 250);
		Element2DManager::GetInstance()->Render();
	}
}

void falcon::BaseApp::Update() 
{
	InputState refInputState =  InputStateManager::GetInstance()->GenerateInputState();

	if(m_scene != NULL)
	{
		m_scene->Update(&refInputState);
		SoundManager::GetInstance()->Update();
	}
}

 bool falcon::BaseApp::InitOpenGL()
 {
	glewInit();

	//Disable VSync (1 = enable Vsync)
	wglSwapIntervalEXT(0);

	glClearColor(0.3f, 0.3f, 0.3f, 0.3f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do

	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	return true;
 }

 LRESULT falcon::BaseApp::MsgProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	POINTS currentpos;
	short zPos=0;

	switch( msg )
	{
	// WM_ACTIVATE is sent when the window is activated or deactivated.  
	// We pause the game when the window is deactivated and unpause it 
	// when it becomes active.  
	case WM_ACTIVATE:
		if( LOWORD(wParam) == WA_INACTIVE )
		{
			m_appPaused = true;
			InputStateManager::GetInstance()->Stop();
		}
		else
		{
			m_appPaused = false;
			InputStateManager::GetInstance()->Start();
		}
		return 0;

	// WM_SIZE is sent when the user resizes the window.  
	case WM_SIZE:
		m_clientWidth  = LOWORD(lParam);
		m_clientHeight = HIWORD(lParam);
		if( m_hDC )
		{
			if( wParam == SIZE_MINIMIZED )
			{
				m_appPaused = true;
				m_minimized = true;
				m_maximized = false;
			}
			else if( wParam == SIZE_MAXIMIZED )
			{
				m_appPaused = false;
				m_minimized = false;
				m_maximized = true;
				Resize();
			}
			else if( wParam == SIZE_RESTORED )
			{
				if( m_minimized )
				{
					m_appPaused = false;
					m_minimized = false;
					Resize();
				}
				else if( m_maximized )
				{
					m_appPaused = false;
					m_maximized = false;
					Resize();
				}
				else if( m_resizing )
				{
					//while user is resizing, do nothing
				}
				else
				{
					Resize();
				}
			}
		}
		return 0;

	// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
	case WM_ENTERSIZEMOVE:
		m_appPaused = true;
		m_resizing  = true;
		InputStateManager::GetInstance()->Stop();
		return 0;

	// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
	case WM_EXITSIZEMOVE:
		m_appPaused = false;
		m_resizing  = false;
		InputStateManager::GetInstance()->Start();
		Resize();
		return 0;
 
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

	// The WM_MENUCHAR message is sent when a menu is active and the user presses 
	// a key that does not correspond to any mnemonic or accelerator key. 
	case WM_MENUCHAR:
        // Don't beep when we alt-enter.
        return MAKELRESULT(0, MNC_CLOSE);

	// Catch this message so to prevent the window from becoming too small.
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200; 
		return 0;

	//mouse moves for input state
	case WM_MOUSEMOVE:
		currentpos = MAKEPOINTS(lParam);
		InputStateManager::GetInstance()->SetMousePos();
		
		return 0;

	case WM_LBUTTONDOWN:
		InputStateManager::GetInstance()->SetLMousePressed(true);
		CallCenter::GetInstance()->OnLMBClick((short)LOWORD(lParam),(short)HIWORD(lParam));
		return 0;

	case WM_LBUTTONUP:
		InputStateManager::GetInstance()->SetLMousePressed(false);
		CallCenter::GetInstance()->OnLMBReleased();
		return 0;

	case WM_RBUTTONDOWN:
		InputStateManager::GetInstance()->SetRMousePressed(true);
		return 0;

	case WM_RBUTTONUP:
		InputStateManager::GetInstance()->SetRMousePressed(false);
		return 0;

	case WM_MOUSEWHEEL:
		zPos = GET_WHEEL_DELTA_WPARAM(wParam);
		InputStateManager::GetInstance()->SetWheelPos(zPos);
		return 0;

	case WM_MBUTTONDOWN:
		InputStateManager::GetInstance()->ToggleActiveCamera();
		InputStateManager::GetInstance()->SetMMousePressed(true);
		return 0;

	case WM_MBUTTONUP:
		InputStateManager::GetInstance()->SetMMousePressed(false);
		return 0;
	}
	return DefWindowProc(m_hMainWnd, msg, wParam, lParam);
}

void falcon::BaseApp::KillWindow()
{
	//Delete all objects first
	delete m_scene;
	delete m_rm;

	CallCenter::Destroy();

	if (m_hRC)// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(nullptr,nullptr))
		{
			LOG(LOG_Error, "SHUTDOWN ERROR! \n Release Of Device Context And Rendering Context Failed.");
		}

		if (!wglDeleteContext(m_hRC))
		{
			LOG(LOG_Error, "SHUTDOWN ERROR! \n Release Rendering Context Failed.");
		}
		m_hRC=nullptr;
	}
	//Release The Device Context
	if (m_hDC && !ReleaseDC(m_hMainWnd,m_hDC))
	{
		LOG(LOG_Error, "SHUTDOWN ERROR! \n Release Of Device Context Failed.")
		m_hDC=nullptr;
	}
	//Destroy The Window?
	if (m_hMainWnd && !DestroyWindow(m_hMainWnd))
	{
		LOG(LOG_Error, "SHUTDOWN ERROR! \n Could Not Release Window Handle.");
		m_hMainWnd=nullptr;	
	}
	//Unregister Class
	if (!UnregisterClass(m_title.c_str(),m_hAppInst)) 
	{
		LOG(LOG_Error, "SHUTDOWN ERROR! \n Could Not Unregister Class.");
		m_hAppInst=nullptr;
	}

	InputStateManager::Destroy();
}
