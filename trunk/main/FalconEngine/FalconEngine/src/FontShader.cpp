#include "FontShader.h"

void falcon::FontShader::SetShaderVariables()
{
	GetShaderVariable("WorldMatrix") = m_shaderData->GetWorldMatrix();
	GetShaderVariable("WorldViewProjectionMatrix") = m_shaderData->GetWorldViewProjectionMatrix();
	GetShaderVariable("uDiffuseTextureSampler").SetTexture(m_shaderData->GetTexture(),1);
}

void falcon::FontShader::CreateVariables()
{
	AddShaderVariable("WorldMatrix");
	AddShaderVariable("WorldViewProjectionMatrix");
	AddShaderVariable("uDiffuseTextureSampler");
}
