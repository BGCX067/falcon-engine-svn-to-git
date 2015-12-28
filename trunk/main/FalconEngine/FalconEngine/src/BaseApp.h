#ifndef FALCONENGINE_BASEAPP_H
#define FALCONENGINE_BASEAPP_H

#include "FalconLuaBind.h"
#include "FalconMath.h"

namespace falcon
{
	class Scene;
	class ResourceManager;
	class CallCenter;
	class Menu;
	class Button;
	class FalconFont;
	class Element2D;

	class BaseApp
	{
	public:
		BaseApp(std::string title);
		virtual ~BaseApp();

		virtual LRESULT MsgProc(UINT msg, WPARAM wParam, LPARAM lParam);

		int Run();
		virtual void Render();
		virtual void Update();
		virtual void Load(){};
		bool Create();

		void SetScene(Scene* scene) {m_scene = scene;}
		Scene* GetScene() const {return m_scene;};

		void SetResourceManager(ResourceManager* rm) {m_rm	= rm;}
		ResourceManager* GetResourceManager() const {return m_rm;}

		static luabind::scope Register();

	protected:
		bool m_appPaused;
		std::string	m_title;
		int m_clientWidth;
		int m_clientHeight;

		//Scene*	m_scene;
	private:
		void KillWindow();
		bool InitOpenGL();
		void Resize();

		HINSTANCE m_hAppInst;
		HWND m_hMainWnd;
		HDC m_hDC;		// Private GDI Device Context
		HGLRC m_hRC;		// Permanent Rendering Context

		bool m_minimized;
		bool m_maximized;
		bool m_resizing;
		bool m_exit;

		Scene* m_scene;
		ResourceManager* m_rm;

		FalconFont* m_font;

		BaseApp(const BaseApp& t);
		BaseApp& operator=(const BaseApp& t);
	};
}

#endif //FALCONENGINE_BASEAPP_H
