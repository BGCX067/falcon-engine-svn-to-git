#ifndef FALCONENGINE_INPUTSTATE_H
#define FALCONENGINE_INPUTSTATE_H

#include "FalconMath.h"
#include "luabind\scope.hpp"

namespace falcon
{
	class InputState
	{
	public:
		InputState(bool bMouseMoved, bool bLMBPressed, bool bRMBPressed, int iWheelPos, falcon::Vec2 mouseDelta, falcon::Vec2 mousePos,unsigned char *keys, float dTime, float gameTime);
		virtual ~InputState(void);
	
		bool IsKeyDown(int vKey) const;
		bool IsMouseMoving() const {return m_bMouseMoving;}
		falcon::Vec2 GetMouseMovement() const {return m_deltaMousePos;}
		falcon::Vec2 GetMousePos() const {return m_mousePos;}
		short GetWheelPos() const {return m_wheelPos;}
		bool IsLeftMouseButtonDown() const {return m_bLMBPressed;}
		bool IsRightMouseButtonDown() const {return m_bRMBPressed;}
		float GetDeltaTime() const{return m_deltaTime;}
		float GetGameTime()const{return m_gameTime;}

		static luabind::scope Register();

		// Implement assignment operator and copy constructor
		InputState& operator=(const InputState& g);
		InputState(const InputState& g);
	
		//Constants
		static const int NUMKEYS = 256;
	
	private:
		bool m_bLMBPressed;
		bool m_bRMBPressed;
		bool m_bMouseMoving;
		short m_wheelPos;
		falcon::Vec2 m_mousePos;
		falcon::Vec2 m_deltaMousePos;
		float m_deltaTime;
		float m_gameTime;
		unsigned char m_keys[NUMKEYS];
	};
}

#endif //FALCONENGINE_INPUTSTATE_H