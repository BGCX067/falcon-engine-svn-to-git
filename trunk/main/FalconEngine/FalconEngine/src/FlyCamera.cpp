#include "stdafx.h"
#include "FlyCamera.h"
#include "typedefs.h"

falcon::FlyCamera::FlyCamera():Camera(), m_bLockPitchDown(false), m_bLockPitchUp(false)
{
}

void falcon::FlyCamera::Update( const InputState* inputState )
{
	if(!m_isActive)return;

	bool bRunning=false;

	Vec3 viewDir = Vec3(m_viewMatrix.at(0,2), m_viewMatrix.at(1,2), m_viewMatrix.at(2,2));
	viewDir *= -1;
	viewDir.normalize();
	Vec3 rightvector = m_worldUp.crossProduct(viewDir);
	rightvector.normalize();

	Vec3 direction = Vec3(0,0,0);
	if(inputState->IsKeyDown(VK_W) )
		direction += viewDir;
	if(inputState->IsKeyDown(VK_S) )
		direction -= viewDir;
	if(inputState->IsKeyDown(VK_D) )
		direction += rightvector;
	if(inputState->IsKeyDown(VK_A) )
		direction -= rightvector;
	if(inputState->IsKeyDown(VK_LSHIFT) )
		bRunning = true;

	float finalspeed = m_speed;
	if(bRunning)finalspeed *= m_runMultiplier;

	m_position = m_position + direction*finalspeed*inputState->GetDeltaTime();

	if (inputState->IsMouseMoving())
	{
		Vec2 mouseMovement = inputState->GetMouseMovement();

		float yaw = mouseMovement.x / CAMERA_MOUSE_SCALE;
		float pitch  = mouseMovement.y / CAMERA_MOUSE_SCALE;
	
		
		//ignore near-perpendicular view
		if((m_bLockPitchDown && yaw < 0) || (m_bLockPitchUp && yaw > 0) || (!m_bLockPitchDown && !m_bLockPitchUp))
		{
			Vec3 rightvector = m_worldUp.crossProduct(viewDir);
			rightvector.normalize();

			Quaternion qPitchRot = Quaternion::fromAxisRot(rightvector, -pitch);
			Quaternion qYawRot = Quaternion::fromAxisRot(m_worldUp, -yaw);
			Quaternion totalRotation = qPitchRot * qYawRot;
			m_rotation = m_rotation * totalRotation.rotMatrix();
		}
	}
	UpdateViewMatrix();

	//check perpendicular-locks
	CheckPerpendicularYView();
}

void falcon::FlyCamera::CheckPerpendicularYView()
{
	Vec3 viewDir = Vec3(m_viewMatrix.at(0,2), m_viewMatrix.at(1,2), m_viewMatrix.at(2,2));
	float viewDirDotUp = m_worldUp.dotProduct(viewDir);

	if(!(viewDirDotUp < 0.99f)) m_bLockPitchDown = true;
	else m_bLockPitchDown = false;

	if(!(viewDirDotUp > -0.99f)) m_bLockPitchUp = true;
	else m_bLockPitchUp = false;
}