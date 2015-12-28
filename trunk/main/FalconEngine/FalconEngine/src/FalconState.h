#ifndef FALCONENGINE_FALCONSTATE_H
#define FALCONENGINE_FALCONSTATE_H

#include "FalconLuaBind.h"
#include "InputState.h"

namespace falcon
{
	class RenderContext;

	class FalconState
	{
	public:

		FalconState();
		virtual void Init(){};

		virtual void Pause(){m_isPaused = true;}
		virtual void Resume(){m_isPaused = false;}
		virtual bool isPaused(){return m_isPaused;}

		virtual void Update(const InputState* /*inputState*/){};

		// Methods you won't call by hand
		void Draw(RenderContext& /*renderContext*/){};
		void CleanUp(){};

	private:
		bool m_isPaused;
	};

	struct FalconStateWrapper: FalconState, luabind::wrap_base
	{
		FalconStateWrapper():FalconState(){};

		virtual void Init() {call<void>("Init");}
		static void default_Init(FalconState* state) {return state->FalconState::Init();}

		virtual void Pause() {call<void>("Pause");}
		static void default_Pause(FalconState* state) {return state->FalconState::Pause();}

		virtual void Resume() {call<void>("Resume");}
		static void default_Resume(FalconState* state) {return state->FalconState::Resume();}

		virtual void Update(const InputState* inputState) { call<void>("Update", inputState); }
		static void default_Update(FalconState* state, const InputState* inputState) { return state->FalconState::Update(inputState); }
	};
}

#endif //FALCONENGINE_FALCONSTATE_H