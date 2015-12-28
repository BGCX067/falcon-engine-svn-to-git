#ifndef FALCONENGINE_MENU_H
#define FALCONENGINE_MENU_H

#include "Callable.h"
#include <vector>
#include "FalconLuaBind.h"

namespace falcon
{
	class Element2D;
	class Button;

	class Menu: public Callable
	{
	public:
		Menu();
		~Menu();

		virtual void Notify(Element2D* callerPtr){callerPtr;};
		void AddButton(Button* button);
		void Draw();

	private:
		std::vector<Button*> m_Buttons;
	};

	struct MenuWrapper: Menu, luabind::wrap_base
	{
		MenuWrapper():Menu(){};
		virtual ~MenuWrapper(){};

		virtual void Notify(Element2D* callerPtr) {call<void>("Notify", callerPtr);}
		static void default_Notify(Menu* ptr, Element2D* callerPtr) {return ptr->Menu::Notify(callerPtr);}

		static luabind::scope Register()
		{
			return
				luabind::class_<Menu, MenuWrapper>("Menu")
				.def(luabind::constructor<>())
				.def("Notify", &Menu::Notify, &MenuWrapper::default_Notify)
				.def("AddButton", &Menu::AddButton);
		};
	};
}

#endif //FALCONENGINE_MENU_H