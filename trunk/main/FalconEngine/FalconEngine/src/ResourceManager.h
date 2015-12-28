#ifndef FALCONENGINE_RESOURCEMANAGER_H
#define FALCONENGINE_RESOURCEMANAGER_H

#include "stdafx.h"
#include "TextureManager.h"
#include "FalconLuaBind.h"
#include "MeshManager.h"

namespace falcon
{
	class Mesh;
	class Shader;
	class GameObject;
	class Element2D;
	class FalconFont;

	class ResourceManager
	{
		friend class falcon::MeshManager;
	public:
		ResourceManager(float clientWidth, float clienHeight);
		ResourceManager(){};
		virtual ~ResourceManager();

		bool LoadMesh(const std::string& path);
		//Mesh* GetMesh(const std::string& id);
		void GetMesh(const std::string& id, GameObject& object);
		bool UnloadMesh(const std::string& id);

		bool LoadShader(const std::string& shader);
		Shader* GetShader(const std::string& id);
		bool UnloadShader(const std::string& id);

		bool LoadTexture(const std::string& path);
		TextureID GetTexture(const std::string& id);
		bool UnloadTexture(const std::string& id);

		bool LoadCubeTexture(const std::string& path);
		TextureID GetCubeTexture(const std::string& id);

		void LoadFont(const std::string& fontName, int fontSize);
		falcon::FalconFont* GetFont( const std::string& fontName );

		void Add2DElement(Element2D* element);

		static luabind::scope Register();
		
	};
}

#endif /*FALCONENGINE_RESOURCEMANAGER_H*/