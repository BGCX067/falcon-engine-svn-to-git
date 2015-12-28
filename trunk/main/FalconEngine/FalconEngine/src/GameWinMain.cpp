#include "stdafx.h"
#include "GameWinMain.h"
#include "BaseApp.h"
#include "LogManager.h"
#include "LuaVirtualMachine.h"
//-----------------------------------------------------------------
// Function called by Windows
//-----------------------------------------------------------------

int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*prevInstance*/, PSTR /*cmdLine*/, int /*showCmd*/)
{
	
	#ifdef _DEBUG
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
		//_CrtSetBreakAlloc(5006);
	#endif

	falcon::LuaVirtualMachine* pLuaVM = new falcon::LuaVirtualMachine();
	int ret  = pLuaVM->load();
	ret;
	//destroy objects
	delete pLuaVM;

	return ret;

}