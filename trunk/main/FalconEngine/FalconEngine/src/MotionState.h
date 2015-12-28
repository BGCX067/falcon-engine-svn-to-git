#ifndef FALCONENGINE_MOTIONSTATE_H
#define FALCONENGINE_MOTIONSTATE_H

#include "FalconBulletBind.h"

namespace falcon
{
	class InputState; 
	class MotionState : public btMotionState, public luabind::wrap_base
	{
		public:
		virtual ~MotionState(){};

		virtual void getWorldTransform (btTransform& /*worldTrans*/) const{};
		virtual void setWorldTransform (const btTransform& /*worldTrans*/){};

		static luabind::scope falcon::MotionState::Register(){
			return
				luabind::class_<MotionState, btMotionState>("MotionState")
				.def(luabind::constructor<>());
		}
	};
}
#endif //FALCONENGINE_MOTIONSTATE_H