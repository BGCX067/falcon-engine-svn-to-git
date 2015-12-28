#include "stdafx.h"
#include "Inputstate.h"
#include "FalconLuaBind.h"

luabind::scope falcon::InputState::Register()
{
	//////////////////////////////////////////////////////////////////////////
	///						LUA REGISTRATION							   ///
	//////////////////////////////////////////////////////////////////////////
	return
		luabind::class_<InputState, InputState*>("InputState")
		.def(luabind::constructor<bool, bool, bool, int, Vec2, Vec2, unsigned char*, float, float>())
		.def("IsKeyDown", &InputState::IsKeyDown)
		.def("IsMouseMoving", &InputState::IsMouseMoving)
		.def("GetMouseMovement", &InputState::GetMouseMovement)
		.def("GetMousePos", &InputState::GetMousePos)
		.def("GetWheelPos", &InputState::GetWheelPos)
		.def("IsLeftMouseButtonDown", &InputState::IsLeftMouseButtonDown)
		.def("IsRightMouseButtonDown", &InputState::IsRightMouseButtonDown)
		.def("GetDeltaTime", &InputState::GetDeltaTime)
		.def("GetGameTime", &InputState::GetGameTime);
}

falcon::InputState::InputState( bool bMouseMoved, bool bLMBPressed, bool bRMBPressed, int iWheelPos, falcon::Vec2 mouseDelta, falcon::Vec2 mousePos,unsigned char *keys, float dTime, float gameTime )
	:m_bMouseMoving(bMouseMoved)
	,m_bRMBPressed(bRMBPressed)
	,m_bLMBPressed(bLMBPressed)
	,m_wheelPos((short)iWheelPos)
	,m_deltaMousePos(mouseDelta)
	,m_mousePos(mousePos)
	,m_deltaTime(dTime)
	,m_gameTime(gameTime)
{
	memcpy(m_keys, keys, (short)NUMKEYS);
}

falcon::InputState::InputState( const InputState& g )
{
	m_bLMBPressed = g.m_bLMBPressed;
	m_bRMBPressed = g.m_bRMBPressed;
	m_wheelPos = g.m_wheelPos;
	m_deltaMousePos = g.m_deltaMousePos;
	m_mousePos = g.m_mousePos;
	m_bMouseMoving = g.m_bMouseMoving;
	m_deltaTime = g.m_deltaTime;
	m_gameTime = g.m_gameTime;

	//deep copy keys
	memcpy(m_keys, g.m_keys, NUMKEYS);

}

falcon::InputState::~InputState(void)
{

}

bool falcon::InputState::IsKeyDown( int vKey ) const
{
	// TODO: find out what this piece of code does
	if(m_keys[vKey] & 0x80)return true;
	return false;
}

falcon::InputState& falcon::InputState::operator=( const InputState& g )
{
	m_bLMBPressed = g.m_bLMBPressed;
	m_bRMBPressed = g.m_bRMBPressed;
	m_wheelPos = g.m_wheelPos;
	m_deltaMousePos = g.m_deltaMousePos;
	m_mousePos = g.m_mousePos;
	m_bMouseMoving = g.m_bMouseMoving;

	//deep copy keys
	memcpy(m_keys, g.m_keys, NUMKEYS);
	m_deltaTime = g.m_deltaTime;
	m_gameTime = g.m_gameTime;

	return *this;
}
