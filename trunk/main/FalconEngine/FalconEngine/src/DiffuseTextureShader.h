#ifndef FALCONENGINE_DIFFUSETEXTURESHADER_H
#define FALCONENGINE_DIFFUSETEXTURESHADER_H

#include "Shader.h"
#include "typedefs.h"

namespace falcon
{
	class DiffuseTextureShader : public Shader
	{
	public:
		DiffuseTextureShader(std::string vert, std::string frag):Shader(vert, frag){};
		virtual ~DiffuseTextureShader(void){};

	protected:
		void CreateVariables();
		void SetShaderVariables();
	private:
		//disabled copy constructor and assignment operator
		DiffuseTextureShader(const DiffuseTextureShader& shader);
		DiffuseTextureShader& operator=(const DiffuseTextureShader& shader);
	};

}

#endif //FALCONENGINE_DIFFUSETEXTURESHADER_H
