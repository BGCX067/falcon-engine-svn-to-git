#include "stdafx.h"
#include "Scene.h"
#include "GameObject.h"
#include "FlyCamera.h"
#include "FalconMath.h"
#include "FalconUtils.h"
#include "SkyBox.h"
#include "PhysicsWorld.h"
//////////////////////////////////////////////////////////////////////////
///						LUA REGISTRATION							   ///
//////////////////////////////////////////////////////////////////////////
luabind::scope falcon::Scene::Register()
{
	return
		luabind::class_<Scene, Scene*>("Scene")
		.def(luabind::constructor<>())
		.def("Init", &Scene::Init)
		.def("AttachChild", &Scene::AttachChild)
		.def("RemoveChild", &Scene::RemoveChild)
		.def("AddCamera", &Scene::AddCamera)
		.def("RemoveCamera", &Scene::RemoveCamera)
		.def("SetActive", &Scene::SetActive)
		.def("SetSkyBox", &Scene::SetSkyBox);
}

falcon::Scene::Scene():
	m_renderContext(RenderContext()),
	m_skyBox(nullptr),
	m_activeCamera(nullptr),
	m_physicsWorld(nullptr)
{

}

falcon::Scene::~Scene()
{
	ClearCameras();
	ClearGameObjects();
	m_activeCamera = 0;

	delete m_skyBox;
	delete m_physicsWorld;
}

void falcon::Scene::ClearCameras()
{
	std::vector<Camera*>::iterator iter = m_cameras.begin();
	std::vector<Camera*>::iterator itEnd = m_cameras.end();

	for(iter; iter != itEnd; ++iter)
		delete (*iter);

	m_cameras.clear();
}

void falcon::Scene::ClearGameObjects()
{
 	//std::vector<GameObject*>::iterator iter = m_children.begin();
 	//std::vector<GameObject*>::iterator itEnd = m_children.end();
 
 	//for(iter; iter != itEnd; ++iter)
 	//	delete (*iter);
 
 	//m_children.clear();
}
//add default fly-cam
void falcon::Scene::Init()
{
	Camera* cam = new FlyCamera();
	cam->Place(Vec3(-3,2,3),Vec3(0,0,0));
	cam->Activate();

	AddCamera(cam);
	m_activeCamera = cam;

	m_physicsWorld = new PhysicsWorld();
	m_physicsWorld->Init();
}

int falcon::Scene::AddCamera(Camera* cam)
{
	assert(cam != 0);

	m_cameras.push_back(cam);
	return m_cameras.size() - 1;
}

void falcon::Scene::RemoveCamera(unsigned int index)
{
	if(index >= m_cameras.size())
	{
		LOG(LOG_Warning, "Camera at given index does not exist. Doing nothing");
		return;
	}

	if(index >= m_cameras.size())
	{
		LOG(LOG_Warning, "Cannot Remove Active Camera. Doing nothing");
		return;
	}

	SearchItem<Camera> predicate(m_cameras[index]);
	m_cameras.erase(remove_if(m_cameras.begin(), m_cameras.end(), predicate), m_cameras.end());
}

void falcon::Scene::SetActive(unsigned int index)
{
	if(index >= m_cameras.size())
	{
		LOG(LOG_Warning, "Camera at given index does not exist. Doing nothing");
		return;
	}
	m_activeCamera = m_cameras.at(index);
}

void falcon::Scene::AttachChild(GameObject* object)
{
	assert(object != 0);
	m_children.push_back(object);

	if(m_physicsWorld != 0)
		m_physicsWorld->AddObject(object);
}

void falcon::Scene::RemoveChild(GameObject* object )
{
	SearchItem<GameObject> predicate(object);
	m_children.erase(remove_if(m_children.begin(), m_children.end(), predicate), m_children.end());
}

void falcon::Scene::SetSkyBox(SkyBox* skyBox)
{
	m_skyBox = skyBox;
}

void falcon::Scene::Update( InputState* inputState )
{
	m_fps = 1 / inputState->GetDeltaTime();

	m_activeCamera->Update(inputState);
	m_skyBox->SetLocation(m_activeCamera->GetPosition());

	m_renderContext.SetViewProjectionMatrix(m_activeCamera->GetViewMatrix(), m_activeCamera->GetProjectionMatrix());
	m_physicsWorld->Update(*inputState);

	std::vector<GameObject*>::iterator it;
	for(it = m_children.begin(); it != m_children.end(); ++it)
	{
		if((*it) != 0)
			(*it)->Update(inputState);
	}
}

void falcon::Scene::Render()
{
	std::vector<GameObject*>::iterator it;
	for(it = m_children.begin(); it != m_children.end(); ++it)
	{
		if((*it) != 0)
		(*it)->Draw(m_renderContext);
	}

	//drawing skybox last reduces bandwith overhead
	if(m_skyBox != 0)
		m_skyBox->Draw(m_renderContext);

	m_physicsWorld->DebugDraw();
}