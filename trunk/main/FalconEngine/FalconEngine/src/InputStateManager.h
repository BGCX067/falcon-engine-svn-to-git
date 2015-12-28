#ifndef FALCONENGINE_INPUTSTATEMANAGER_H
#define FALCONENGINE_INPUTSTATEMANAGER_H

#include "InputState.h"
#include "GameTimer.h"

namespace falcon
{
	class InputStateManager
	{
	public:

		static void Create();
		static InputStateManager* GetInstance();
		static void Destroy();

		falcon::InputState GenerateInputState();
		void Stop() {m_gameTimer.Stop();}
		void Start() {m_gameTimer.Start();}
		float GetGameTime() {m_gameTimer.GetDeltaTime();}

		// Set inputdata
		void SetMousePos();
		void SetLMousePressed(bool isPressed) {m_bLMBPressed = isPressed;}
		void SetRMousePressed(bool isPressed) {m_bRMBPressed = isPressed;}
		void SetMMousePressed(bool isPressed) {m_bMMBPressed = isPressed;}
		void SetMouseMove(bool hasMoved){m_bMouseMoved = hasMoved;}
		void SetWheelPos(short wheelPos){m_wheelPos = wheelPos;}
		void ToggleActiveCamera();

	private:
		InputStateManager(const InputStateManager& t);
		InputStateManager& operator=(const InputStateManager& t);

		void ResetCursor();

		InputStateManager();
		virtual ~InputStateManager(){};
		static InputStateManager* s_Instance;

		// DATA
		falcon::Vec2		m_mousePos,
							m_oldMousePos,
							m_deltaMousePos;
		POINT				m_pointMousePos,
							m_pointOldMousePos;
		unsigned char		m_keys[256];
		bool				m_bLMBPressed,
							m_bRMBPressed,
							m_bMMBPressed,
							m_bMouseMoved,
							m_bActiveCam;
		short				m_wheelPos;
		falcon::GameTimer   m_gameTimer;
	};
}

#endif //FALCONENGINE_INPUTSTATEMANAGER_H