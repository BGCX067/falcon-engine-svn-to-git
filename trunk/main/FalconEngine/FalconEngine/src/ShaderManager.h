#ifndef FALCONENGINE_SHADERMANAGER_H
#define FALCONENGINE_SHADERMANAGER_H

#include <map>

namespace falcon
{
	class Shader;

	class ShaderManager
	{
	public:

		static void Create();
		static ShaderManager* GetInstance();
		static void Destroy();

		ShaderManager();
		virtual ~ShaderManager();

		//checks if mesh exists in memory (if not, load it) and return it,
		Shader* LoadShader(std::string shader);
		//unload the mesh
		bool UnLoadShader(std::string shader);

	private:
		static bool s_bInitialized;
		static ShaderManager* s_Instance;

		std::map<std::string, Shader*> m_shaders;
	};
}

#endif //FALCONENGINE_SHADERMANAGER_H
