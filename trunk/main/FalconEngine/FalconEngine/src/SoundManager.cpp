#include "SoundManager.h"
#include "LogManager.h"
#include "fmod_errors.h"

bool falcon::SoundManager::s_bInitialized = false;
FMOD::System* falcon::SoundManager::m_System = 0;
falcon::SoundManager* falcon::SoundManager::s_Instance = 0;

falcon::SoundManager::SoundManager()
{
	s_bInitialized = true;

	FMOD_RESULT result;
	result = FMOD::System_Create(&m_System);
	if(result != FMOD_OK)
	{
		LOG(LOG_Error, FMOD_ErrorString(result));
		return;
	}

	unsigned int version;
	m_System->getVersion(&version);

	if(version < FMOD_VERSION)
	{
		LOG(LOG_Error, "You are using an old version of FMOD!");
		return;
	}

	result = m_System->init(32, FMOD_INIT_NORMAL, 0);
	if(result != FMOD_OK)
	{
		LOG(LOG_Error, FMOD_ErrorString(result));
	}
}

void falcon::SoundManager::Create()
{
	s_Instance = new falcon::SoundManager();
}

falcon::SoundManager* falcon::SoundManager::GetInstance()
{
	return s_Instance;
}

void falcon::SoundManager::Destroy()
{
	delete s_Instance;
	s_Instance = 0;
}

FMOD::Sound* falcon::SoundManager::LoadSound( const std::string& path, const std::string& name)
{
	FMOD_RESULT result;
	FMOD::Sound* sound;
	result = m_System->createSound(path.c_str(), FMOD_HARDWARE, 0, &sound);

	if(result != FMOD_OK)
	{
		LOG(LOG_Error, FMOD_ErrorString(result));
		return nullptr;
	}

	m_sounds.insert(make_pair(name, sound));
	return sound;
}

FMOD::Sound* falcon::SoundManager::GetSound( const std::string& name )
{
	std::map<std::string, FMOD::Sound*>::iterator it = m_sounds.find(name);

	if(it != m_sounds.end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}

void falcon::SoundManager::Play_Sound( const std::string& name )
{
	FMOD_RESULT result;
	FMOD::Sound* sound = GetSound(name);
	FMOD::Channel *channel;

	if(sound != nullptr)
	{
		result = m_System->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);

		if(result != FMOD_OK)
		{
			LOG(LOG_Error, FMOD_ErrorString(result));
			return;
		}

		m_channels.insert(make_pair(name, channel));
	}
}

void falcon::SoundManager::Pause_Sound( const std::string& name)
{
	std::map<std::string, FMOD::Channel*>::iterator it = m_channels.find(name);

	if(it != m_channels.end())
	{
		it->second->setPaused(true);
	}
}

void falcon::SoundManager::UnPause_Sound( const std::string& name )
{
	std::map<std::string, FMOD::Channel*>::iterator it = m_channels.find(name);

	if(it != m_channels.end())
	{
		it->second->setPaused(false);
	}
}


void falcon::SoundManager::Stop_Sound( const std::string& name )
{
	std::map<std::string, FMOD::Channel*>::iterator it = m_channels.find(name);

	if(it != m_channels.end())
	{
		it->second->stop();
	}
}


void falcon::SoundManager::Update()
{
	m_System->update();
}

falcon::SoundManager::~SoundManager()
{
	std::map<std::string, FMOD::Sound*>::iterator iter = m_sounds.begin();
	std::map<std::string, FMOD::Sound*>::iterator itEnd = m_sounds.end();

	for(iter; iter != itEnd; ++iter)
	{
		(*iter).second->release();
	}
	m_sounds.clear();

	m_System->close();
	m_System->release();
}
