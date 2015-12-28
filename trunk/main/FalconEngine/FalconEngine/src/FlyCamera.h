#ifndef FALCONENGINE_FLYCAMERA_H
#define FALCONENGINE_FLYCAMERA_H

#include "Camera.h"

namespace falcon
{
	class FlyCamera : public Camera
	{
	public:
		FlyCamera();
		virtual ~FlyCamera(){};

		virtual void Update(const InputState* inputState);
	protected:
		void CheckPerpendicularYView();
		bool m_bLockPitchUp;
		bool m_bLockPitchDown;
	private:
		FlyCamera(const FlyCamera& t);
		FlyCamera& operator=(const FlyCamera& t);
	};
}

#endif //FALCONENGINE_FLYCAMERA_H