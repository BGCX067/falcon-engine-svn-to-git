#ifndef FALCONENGINE_BUTTON_H
#define FALCONENGINE_BUTTON_H

#include "Element2D.h"

namespace falcon
{
	class Callable;

	class Button: public Element2D
	{
	public:
		Button(float x, float y, float width, float height);
		virtual ~Button(){}
		bool OnLMBClick(float x, float y);
		void OnLMBReleased();
		void AddCallListener(Callable* ptr);

		static luabind::scope Register()
		{
			return
				luabind::class_<Button, Element2D>("Button")
				.def(luabind::constructor<float, float, float, float>())
				.def("AddCallListener", &Button::AddCallListener);
		};
	};
}
#endif //FALCONENGINE_BUTTON_H
