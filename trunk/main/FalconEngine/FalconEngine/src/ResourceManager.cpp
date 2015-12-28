#include "stdafx.h"
#include "ResourceManager.h"
#include "ShaderManager.h"
#include "Mesh.h"
#include "Shader.h"
#include "BoostUtils.h"
#include "GameObject.h"
#include "Element2DManager.h"
#include "FontManager.h"
#include "SoundManager.h"

luabind::scope falcon::ResourceManager::Register()
{
	return 
		luabind::class_<ResourceManager, ResourceManager*>("ResourceManager")
		.def(luabind::constructor<>())
		.def("LoadTexture", &ResourceManager::LoadTexture)
		.def("GetTexture", &ResourceManager::GetTexture)
		.def("GetShader", &ResourceManager::GetShader)
		.def("RemoveTexture", &ResourceManager::UnloadTexture)
		.def("LoadMesh", &ResourceManager::LoadMesh)
		.def("GetMesh", &ResourceManager::GetMesh)
		.def("UnloadMesh", &ResourceManager::UnloadMesh)
		.def("Add2DElement", &ResourceManager::Add2DElement);
}


falcon::ResourceManager::ResourceManager(float clientWidth, float clientHeight)
{
	//creating Managers
	TextureManager::Create();
	MeshManager::Create();
	ShaderManager::Create();
	Element2DManager::Create();
	FontManager::Create(clientWidth, clientHeight, this);
	SoundManager::Create();
}

falcon::ResourceManager::~ResourceManager()
{
	//Destroying Managers
	TextureManager::Destroy();
	MeshManager::Destroy();
	ShaderManager::Destroy();
	Element2DManager::Destroy();
	FontManager::Destroy();
	SoundManager::Destroy();
}

bool falcon::ResourceManager::LoadTexture(const std::string& path)
{
	TextureID texID =  TextureManager::GetInstance()->LoadTexture(path);
	if(texID == 0) return false;
	else return true;
}

bool falcon::ResourceManager::UnloadTexture(const std::string& id )
{
	return TextureManager::GetInstance()->UnloadTexture(id);
}

TextureID falcon::ResourceManager::GetTexture(const std::string& id)
{
	return TextureManager::GetInstance()->LoadTexture(id);
}

bool falcon::ResourceManager::LoadCubeTexture(const std::string& path)
{
	TextureID texID =  TextureManager::GetInstance()->LoadCubeTexture(path);
	if(texID == 0) return false;
	else return true;
}

TextureID falcon::ResourceManager::GetCubeTexture(const std::string& id)
{
	return TextureManager::GetInstance()->LoadCubeTexture(id);
}

bool falcon::ResourceManager::LoadMesh(const std::string& /*path*/)
{
// 	Mesh* meshptr = MeshManager::GetInstance()->LoadMesh(path);
// 	if(meshptr == NULL) return false;
// 	else return true;
	return true;
}

bool falcon::ResourceManager::UnloadMesh(const std::string& id)
{
	return MeshManager::GetInstance()->UnLoadMesh(id);
}

void falcon::ResourceManager::GetMesh( const std::string& id, GameObject& object )
{
// 	boost::thread meshLoader(bind(&MeshManager::LoadMesh, MeshManager::GetInstance(), id, object));
// 	meshLoader.join();
	MeshManager::GetInstance()->LoadMesh(id, object);
}

bool falcon::ResourceManager::LoadShader(const std::string& shader)
{
	Shader* shaderptr = ShaderManager::GetInstance()->LoadShader(shader);
	if(shaderptr == NULL) return false;
	else return true;
}

bool falcon::ResourceManager::UnloadShader(const std::string& id)
{
	return ShaderManager::GetInstance()->UnLoadShader(id);
}

falcon::Shader* falcon::ResourceManager::GetShader(const std::string& id)
{
	return ShaderManager::GetInstance()->LoadShader(id);
}

void falcon::ResourceManager::Add2DElement( Element2D* element )
{
	Element2DManager::GetInstance()->AddElement(element);
}

void falcon::ResourceManager::LoadFont( const std::string& fontName, int fontSize )
{
	FontManager::GetInstance()->LoadFont(fontName, fontSize);
}

falcon::FalconFont* falcon::ResourceManager::GetFont( const std::string& fontName )
{
	return FontManager::GetInstance()->GetFont(fontName);
}
