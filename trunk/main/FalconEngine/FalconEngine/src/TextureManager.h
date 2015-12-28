#ifndef FALCONENGINE_TEXTUREMANAGER_H
#define FALCONENGINE_TEXTUREMANAGER_H

#include "stdafx.h"
#include "typedefs.h"
#include "SOIL.h"
#include <string>
#include <map>

namespace falcon
{
	class TextureManager
	{
	public:

		static void Create();
		static TextureManager* GetInstance();
		static void Destroy();

		TextureID LoadTexture(const std::string& path);
		TextureID LoadCubeTexture(const std::string& path);
		bool UnloadTexture(const std::string& id);

		

	private:
		TextureManager(const TextureManager& t);
		TextureManager& operator=(const TextureManager& t);

		TextureManager();
		virtual ~TextureManager();

		static TextureManager* s_Instance;

		std::map<std::string, TextureID> m_textures;
	};
}

#endif FALCONENGINE_TEXTUREMANAGER_H