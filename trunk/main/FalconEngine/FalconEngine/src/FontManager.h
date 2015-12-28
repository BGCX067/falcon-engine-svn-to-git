#ifndef FALCONENGINE_FONTMANAGER_H
#define FALCONENGINE_FONTMANAGER_H 
#include <string>
#include <vector>
#include <boost\smart_ptr\scoped_ptr.hpp>
#include "FalconFont.h"

namespace falcon
{
	class ResourceManager;

	class FontManager
	{
	public:

		static void Create(float screenWidth, float screenHeight, ResourceManager* rm);
		static FontManager* GetInstance();
		static void Destroy();

		void LoadFont(const std::string& path, const int fontSize);
		FalconFont* GetFont( const std::string& path);

		FontManager(float screenWidth, float screenHeight, ResourceManager* rm);
		virtual ~FontManager();
		

	private:
		static bool s_bInitialized;
		static FontManager* s_Instance;

		float m_screenWidth,
			  m_screenHeight;

		ResourceManager* m_ResourceManager;
		std::map<std::string, FalconFont*> m_Fonts;
	};
}

#endif //FALCONENGINE_FONTMANAGER_H