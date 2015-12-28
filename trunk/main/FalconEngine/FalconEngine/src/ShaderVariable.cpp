#include "stdafx.h"
#include "ShaderVariable.h"


falcon::ShaderVariable::ShaderVariable(GLint uniformLocation):m_UniformLocation(uniformLocation)
{
}

falcon::ShaderVariable::ShaderVariable():m_UniformLocation(-1)
{
	//set location by default to -1 ( OGL's way of saying none)
}


falcon::ShaderVariable::~ShaderVariable()
{
	//nothing to delete
}

//WARNING
//make sure textures are set in the same order they appear in the shader code!!
void falcon::ShaderVariable::SetTexture(GLint texid, short samplerPosition)
{
	assert(samplerPosition < 32); //GLSL shaders can maximum have 32 samplers
	glActiveTexture(GL_TEXTURE0 + samplerPosition);
	glBindTexture(GL_TEXTURE_2D, texid);
	glEnable(GL_TEXTURE_2D);
	glUniform1iARB(m_UniformLocation, samplerPosition);

}

void falcon::ShaderVariable::SetCubeTexture(GLint texid, short samplerPosition)
{
	assert(samplerPosition < 32); //GLSL shaders can maximum have 32 samplers
	glActiveTexture(GL_TEXTURE0 + samplerPosition);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texid);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glUniform1iARB(m_UniformLocation, samplerPosition);

}
//call the appropriate assignment operator;
//clean way of hiding glcode
void falcon::ShaderVariable::operator=(const Vec4& v)
{
	glUniform4f(m_UniformLocation,v.x,v.y,v.z, v.w);
}

void falcon::ShaderVariable::operator=(const Vec3& v)
{
	glUniform3f(m_UniformLocation,v.x,v.y,v.z);
}

void falcon::ShaderVariable::operator=(const Vec2& v)
{
	glUniform2f(m_UniformLocation,v.x,v.y);
}

void falcon::ShaderVariable::operator=(const float f)
{
	glUniform1f(m_UniformLocation,f);
}

void falcon::ShaderVariable::operator=(const unsigned int i)
{
	glUniform1i(m_UniformLocation,i);
}

void falcon::ShaderVariable::operator=(const Mat3& m)
{
	glUniformMatrix3fv(m_UniformLocation,1, false, m.data);
}
void falcon::ShaderVariable::operator=(const Mat4& m)
{
	glUniformMatrix4fv(m_UniformLocation,1, false, m.data);
}