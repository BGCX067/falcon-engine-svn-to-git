#ifndef FALCONENGINE_SCENE_H
#define FALCONENGINE_SCENE_H

#include <vector>
#include "RenderContext.h"
#include "FalconLuaBind.h"

namespace falcon
{
	class GameObject;
	class InputState;
	class RenderContext;
	class Camera;
	class SkyBox;
	class PhysicsWorld;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void Init();

		void AttachChild(GameObject* object);
		void RemoveChild(GameObject* object);

		//skyBox gets cleaned up by Scene
		void SetSkyBox(SkyBox* skyBox);

		void Update(InputState* inputState);
		void Render();
		int AddCamera(Camera* cam);
		void RemoveCamera(unsigned int index);
		void SetActive(unsigned int index);
		const float GetFPS() const {return m_fps;}

		static luabind::scope Register();

	private:

		void ClearGameObjects();
		void ClearCameras();

		std::vector<GameObject*> m_children;
		std::vector<Camera*> m_cameras;

		PhysicsWorld* m_physicsWorld;
		RenderContext m_renderContext;
		Camera* m_activeCamera;
		SkyBox* m_skyBox;
		float m_fps;

		Scene(const Scene& scene);
		Scene& operator=(const Scene& scene);
	};
}

#endif /*FALCONENGINE_SCENE_H*/