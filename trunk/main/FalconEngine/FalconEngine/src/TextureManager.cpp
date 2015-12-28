#include "TextureManager.h"
#include "LogManager.h"

falcon::TextureManager* falcon::TextureManager::s_Instance = 0;

falcon::TextureManager::TextureManager()
{
}

falcon::TextureManager::~TextureManager()
{
	std::map<std::string, TextureID>::iterator iter = m_textures.begin();
	std::map<std::string, TextureID>::iterator itEnd = m_textures.end();

	for(iter; iter != itEnd; ++iter)
	{
		glDeleteTextures(1, &(*iter).second);

		std::stringstream buffer;
		buffer << "Successfully deleted Texture " << (*iter).first;
		LOG(LOG_Info, buffer.str());
	}
	m_textures.clear();
}

TextureID falcon::TextureManager::LoadTexture(const std::string& path )
{
	std::map<std::string, TextureID>::iterator it = m_textures.find(path);

	if(it == m_textures.end())
	{
		GLuint texture2D = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		if( texture2D == 0)
		{
			std::stringstream buffer;
			buffer << "\t" << path;
			LOG(LOG_Error, SOIL_last_result() + buffer.str());
			return 0;
		}else{
			m_textures.insert(std::pair<std::string, TextureID>(path, texture2D));
			std::stringstream buffer;
			buffer << "Successfully loaded " << path;
			LOG(LOG_Info, buffer.str());
			return texture2D;
		}
	}else{
		return (*it).second;
	}
}

bool falcon::TextureManager::UnloadTexture(const std::string& texture)
{
	std::map<std::string, TextureID>::iterator it = m_textures.find(texture);

	if(it != m_textures.end())
	{
		glDeleteTextures(1, &(*it).second);
		m_textures.erase(it);

		std::stringstream buffer;
		buffer << "Successfully deleted Texture " << texture;
		LOG(LOG_Info, buffer.str());

		return true;
	}else{
		LOG(LOG_Error, "Shader Doesn't Exist.\n" + texture + "\n");
		return false;
	}
}

TextureID falcon::TextureManager::LoadCubeTexture(const std::string& path )
{
	std::map<std::string, TextureID>::iterator it = m_textures.find(path);

	if(it == m_textures.end())
	{
		GLuint texture2D = SOIL_load_OGL_single_cubemap(path.c_str(), SOIL_DDS_CUBEMAP_FACE_ORDER, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_DDS_LOAD_DIRECT);
		
		//reduces seams at the edges
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		if( texture2D == 0)
		{
			std::stringstream buffer;
			buffer << "\t" << path;
			LOG(LOG_Error, SOIL_last_result() + buffer.str());
			return 0;
		}else{
			m_textures.insert(std::pair<std::string, TextureID>(path, texture2D));
			std::stringstream buffer;
			buffer << "Successfully loaded " << path;
			LOG(LOG_Info, buffer.str());
			return texture2D;
		}
	}else{
		return (*it).second;
	}
}

void falcon::TextureManager::Create()
{
	s_Instance = new falcon::TextureManager();
}

falcon::TextureManager* falcon::TextureManager::GetInstance()
{
	return s_Instance;
}

void falcon::TextureManager::Destroy()
{
	delete s_Instance;
	s_Instance = 0;
}
