#include "FontManager.h"
#include "Boost/thread.hpp"
#include <boost/ref.hpp>

bool falcon::FontManager::s_bInitialized = false;
falcon::FontManager* falcon::FontManager::s_Instance = 0;

falcon::FontManager::FontManager(float screenWidth, float screenHeight, ResourceManager* rm)
{
	s_bInitialized = true;

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	m_ResourceManager = rm;
}

falcon::FontManager::~FontManager()
{
	std::map<std::string, FalconFont*>::iterator iter = m_Fonts.begin();
	std::map<std::string, FalconFont*>::iterator itEnd = m_Fonts.end();

	for(iter; iter != itEnd; ++iter)
	{
		delete (*iter).second;
	}

	m_Fonts.clear();
}


void falcon::FontManager::Create(float screenWidth, float screenHeight, ResourceManager* rm)
{
	s_Instance = new falcon::FontManager(screenWidth, screenHeight, rm);
}

falcon::FontManager* falcon::FontManager::GetInstance()
{
	return s_Instance;
}

void falcon::FontManager::Destroy()
{
	delete s_Instance;
	s_Instance = 0;
}

void falcon::FontManager::LoadFont( const std::string& path, const int fontSize )
{
	FalconFont* font = new FalconFont(path, m_screenWidth, m_screenHeight, fontSize);
	font->Init(m_ResourceManager);

	m_Fonts.insert(make_pair(path, font));
}

falcon::FalconFont* falcon::FontManager::GetFont( const std::string& path)
{
	std::map<std::string, FalconFont*>::iterator it = m_Fonts.find(path);

	if(it != m_Fonts.end())
	{
		return it->second;
	}
}
