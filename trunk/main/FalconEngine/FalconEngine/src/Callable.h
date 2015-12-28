#ifndef FALCONENGINE_ICALLABLE_H
#define FALCONENGINE_ICALLABLE_H

#include "FalconLuaBind.h"

namespace falcon
{
	class Element2D;

	class Callable
	{
	public:

		Callable(){};
		virtual ~Callable(){};

		virtual void Notify(Element2D* /*callerPtr*/){};
	};

	struct CallableWrapper: Callable, luabind::wrap_base
	{
		CallableWrapper():Callable(){};
		virtual ~CallableWrapper(){};

		virtual void Notify(Element2D* callerPtr) {call<void>("Notify", callerPtr);}
		static void default_Notify(Callable* ptr, Element2D* callerPtr) {return ptr->Callable::Notify(callerPtr);}

		static luabind::scope Register()
		{
			return
				luabind::class_<Callable, CallableWrapper>("Callable")
				.def(luabind::constructor<>())
				.def("Notify", &Callable::Notify, &CallableWrapper::default_Notify);
		};
	};
}

#endif //FALCONENGINE_ICALLABLE_H