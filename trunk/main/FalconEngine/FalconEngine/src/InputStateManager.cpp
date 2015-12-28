#include "stdafx.h"
#include "InputStateManager.h"

falcon::InputStateManager* falcon::InputStateManager::s_Instance = 0;

falcon::InputStateManager::InputStateManager(): 
	m_deltaMousePos(Vec2(0,0)),
	m_bLMBPressed(false),
	m_bRMBPressed(false),
	m_bActiveCam(false),
	m_wheelPos(0)
{
	m_oldMousePos.x=0;
	m_oldMousePos.y=0;
	m_mousePos = m_oldMousePos;

	m_gameTimer.Reset();
}
void falcon::InputStateManager::Create()
{
	s_Instance = new falcon::InputStateManager();
}

falcon::InputStateManager* falcon::InputStateManager::GetInstance()
{
	return s_Instance;
}

void falcon::InputStateManager::Destroy()
{
	delete s_Instance;
	s_Instance = 0;
}

falcon::InputState falcon::InputStateManager::GenerateInputState()
{
	if (m_bActiveCam)
	{
		// Calculate delta mouse pos
		m_deltaMousePos.x = static_cast<float>(m_pointMousePos.x - m_pointOldMousePos.x);
		m_deltaMousePos.y = static_cast<float>(m_pointMousePos.y - m_pointOldMousePos.y);
		m_pointOldMousePos = m_pointMousePos;
		ResetCursor();

		if(m_deltaMousePos.x == 0 && m_deltaMousePos.y == 0)
		{
			m_bMouseMoved = false;
		}
		else
		{
			m_bMouseMoved = true;	
		}
	}

	if(GetKeyboardState(m_keys))
	{
		m_gameTimer.Tick();
		float dTime = m_gameTimer.GetDeltaTime();
		float gameTime = m_gameTimer.GetGameTime();
		Vec2 mousePosition;
		mousePosition.x = static_cast<float>(m_pointMousePos.x);
		mousePosition.y = static_cast<float>(m_pointMousePos.y);

		falcon::InputState inputState(m_bMouseMoved, m_bLMBPressed, m_bRMBPressed, m_wheelPos, m_deltaMousePos, mousePosition, m_keys, dTime, gameTime);
		m_wheelPos = 0;
		
		return inputState;
	}
}

void falcon::InputStateManager::SetMousePos()
{
	GetCursorPos(&m_pointMousePos);
}

void falcon::InputStateManager::ResetCursor()
{
	m_pointOldMousePos.x = GetSystemMetrics(SM_CXSCREEN)/2;
	m_pointOldMousePos.y = GetSystemMetrics(SM_CYSCREEN)/2;
	SetCursorPos(GetSystemMetrics(SM_CXSCREEN)/2, GetSystemMetrics(SM_CYSCREEN)/2);
}
void falcon::InputStateManager::ToggleActiveCamera()
{
	if(m_bActiveCam)
	{
		ResetCursor();
		ShowCursor(true);
		m_bMouseMoved = false;
	}else{
		ShowCursor(false);
		ResetCursor();
	}

	m_bActiveCam = !m_bActiveCam;
}
