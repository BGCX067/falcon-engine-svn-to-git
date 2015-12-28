#ifndef FALCONENGINE_SKYBOXSHADER_H
#define FALCONENGINE_SKYBOXSHADER_H

#include "Shader.h"
#include "typedefs.h"

namespace falcon
{
	class SkyBoxShader : public Shader
	{
	public:
		SkyBoxShader(std::string vert, std::string frag):Shader(vert, frag){};
		virtual ~SkyBoxShader(void){};

	protected:
		void CreateVariables();
		void SetShaderVariables();
	private:
		//disabled copy constructor and assignment operator
		SkyBoxShader(const SkyBoxShader& shader);
		SkyBoxShader& operator=(const SkyBoxShader& shader);
	};

}

#endif //FALCONENGINE_SKYBOXSHADER_H
