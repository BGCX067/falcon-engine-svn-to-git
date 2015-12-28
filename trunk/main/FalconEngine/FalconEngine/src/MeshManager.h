#ifndef FALCONENGINE_MESHMANAGER_H
#define FALCONENGINE_MESHMANAGER_H

#include <map>

namespace falcon
{
	class Mesh;
	class GameObject;

	class MeshManager
	{
	public:

		static void Create();
		static MeshManager* GetInstance();
		static void Destroy();

		MeshManager();
		virtual ~MeshManager();

		//checks if mesh exists in memory (if not, load it) and return it,
		void LoadMesh(std::string path , GameObject& object);
		//unload the mesh
		bool UnLoadMesh(std::string path);

	private:
		static bool s_bInitialized;
		static MeshManager* s_Instance;

		std::map<std::string, Mesh*> m_Meshes;

		void (*MeshLoaded) ();
	};
}

#endif //FALCONENGINE_MESHMANAGER_H
