#ifndef FALCONENGINE_SOUNDMANAGER_H
#define FALCONENGINE_SOUNDMANAGER_H 

#include <string>
#include <fmod.hpp>
#include <map>

namespace falcon
{
	class SoundManager
	{
	public:

		static void Create();
		static SoundManager* GetInstance();
		static void Destroy();

		FMOD::Sound* LoadSound(const std::string& path, const std::string& name);
		FMOD::Sound* GetSound(const std::string& name);

		void Play_Sound(const std::string& name);
		void Stop_Sound(const std::string& name);
		void Pause_Sound(const std::string& name);
		void UnPause_Sound(const std::string& name);

		// Call this once per frame
		void Update();

	private:
		static bool s_bInitialized;
		static SoundManager* s_Instance;
		static FMOD::System* m_System;

		void ERRCHECK(FMOD_RESULT result);

		std::map<std::string, FMOD::Sound*> m_sounds;
		std::map<std::string, FMOD::Channel*> m_channels;

		SoundManager();
		virtual ~SoundManager();
		

	};
}
#endif //FALCONENGINE_SOUNDMANAGER_H