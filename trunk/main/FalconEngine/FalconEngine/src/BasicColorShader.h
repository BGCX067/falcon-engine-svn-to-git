#ifndef FALCONENGINE_BASICCOLORSHADER_H
#define FALCONENGINE_BASICCOLORSHADER_H

#include "Shader.h"

namespace falcon
{

	class BasicColorShader : public Shader
	{
	public:
		BasicColorShader(std::string vert, std::string frag):Shader(vert, frag){};
		virtual ~BasicColorShader(void){};
		
	protected:
		void CreateVariables();
		void SetShaderVariables();

	private:
		//disabled copy constructor and assignment operator
		BasicColorShader(const BasicColorShader& shader);
		BasicColorShader& operator=(const BasicColorShader& shader);
	};

}

#endif //FALCONENGINE_BASICCOLORSHADER_H
