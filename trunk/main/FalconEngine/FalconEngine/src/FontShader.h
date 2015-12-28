#ifndef FALCONENGINE_FONTSHADER_H
#define FALCONENGINE_FONTSHADER_H

#include "Shader.h"
#include "typedefs.h"

namespace falcon
{
	class FontShader : public Shader
	{
	public:
		FontShader(std::string vert, std::string frag):Shader(vert, frag){};
		virtual ~FontShader(void){};

	protected:
		void CreateVariables();
		void SetShaderVariables();
	private:
		//disabled copy constructor and assignment operator
		FontShader(const FontShader& shader);
		FontShader& operator=(const FontShader& shader);
	};

}

#endif //FALCONENGINE_FONTSHADER_H
