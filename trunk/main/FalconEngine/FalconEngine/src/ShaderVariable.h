#ifndef FALCONENGINE_SHADERVARIABLE_H
#define FALCONENGINE_SHADERVARIABLE_H
#include "GL/glew.h"

#include "FalconMath.h"

namespace falcon
{
	class ShaderVariable
	{
	public:

		ShaderVariable(GLint uniformLocation);

		ShaderVariable();
		virtual ~ShaderVariable(void);

		void SetLocation(GLint uniformLocation) {m_UniformLocation = uniformLocation;}
		void SetTexture(GLint textid, short samplerPosition);
		void SetCubeTexture(GLint textid, short samplerPosition);

		void operator=(const float f);
		void operator=(const unsigned int i);
		void operator=(const Vec2& v);
		void operator=(const Vec3& v);
		void operator=(const Vec4& v);
		void operator=(const Mat3& m);
		void operator=(const Mat4& m);
	private:
		GLint m_UniformLocation;
	};
}

#endif //FALCONENGINE_SHADERVARIABLE_H

