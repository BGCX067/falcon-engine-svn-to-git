#include "stdafx.h"
#include "ShaderManager.h"
#include "LogManager.h"
#include "FalconMath.h"

#include "BasicColorShader.h"
#include "DiffuseTextureShader.h"
#include "SkyBoxShader.h"
#include "FontShader.h"

bool falcon::ShaderManager::s_bInitialized = false;
falcon::ShaderManager* falcon::ShaderManager::s_Instance = 0;

falcon::ShaderManager::ShaderManager()
{
	s_bInitialized = true;
}

falcon::ShaderManager::~ShaderManager()
{
	std::map<std::string, Shader*>::iterator iter = m_shaders.begin();
	std::map<std::string, Shader*>::iterator itEnd = m_shaders.end();
	
	for(iter; iter != itEnd; ++iter)
	{
		delete (*iter).second;

		std::stringstream buffer;
		buffer << "Successfully deleted Shader " << (*iter).first;
		LOG(LOG_Info, buffer.str());
	}
	m_shaders.clear();
}

void falcon::ShaderManager::Create()
{
	s_Instance = new falcon::ShaderManager();
}

falcon::ShaderManager* falcon::ShaderManager::GetInstance()
{
	return s_Instance;
}

void falcon::ShaderManager::Destroy()
{
	delete s_Instance;
	s_Instance = 0;
}

falcon::Shader* falcon::ShaderManager::LoadShader(std::string shader)
{	
	std::map<std::string, Shader*>::iterator it = m_shaders.find(shader);

	if(it == m_shaders.end())
	{
		std::string vertPath = "./data/shaders/" + shader + ".vert";
		std::string fragPath = "./data/shaders/" + shader + ".frag";

		Shader* shaderObject = 0;
		if(shader == "BasicColor")
			shaderObject = new BasicColorShader(vertPath, fragPath);
		
		if(shader == "DiffuseTexture")
			shaderObject = new DiffuseTextureShader(vertPath, fragPath);

		if(shader == "SkyBox")
			shaderObject = new SkyBoxShader(vertPath, fragPath);

		if(shader == "Font")
			shaderObject = new FontShader(vertPath, fragPath);

		if(shaderObject == 0)
		{
			LOG(LOG_Error, "Shader Doesn't Exist.\n" + shader + "\n");
			return nullptr;
		}else{
			LOG(LOG_Info, "Successfully loaded Shader " + shader);
		}

		//initialise shader
		bool result  = shaderObject->Init();

		if(result)
		{
			m_shaders.insert(make_pair(shader, shaderObject));
			return shaderObject;
		}else{
			return nullptr;
		}
	}else{
		return (*it).second;
	}
}

bool falcon::ShaderManager::UnLoadShader(std::string shader)
{
	std::map<std::string, Shader*>::iterator it = m_shaders.find(shader);

	if(it != m_shaders.end())
	{
		delete (*it).second;
		m_shaders.erase(it);

		std::stringstream buffer;
		buffer << "Successfully deleted Shader " << shader;
		LOG(LOG_Info, buffer.str());

		return true;
	}else{
		LOG(LOG_Error, "Shader Doesn't Exist.\n" + shader + "\n");
		return false;
	}
}