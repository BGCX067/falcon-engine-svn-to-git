#include "stdafx.h"
#include "DiffuseTextureShader.h"

void falcon::DiffuseTextureShader::SetShaderVariables()
{
	GetShaderVariable("WorldMatrix") = m_shaderData->GetWorldMatrix();
	GetShaderVariable("WorldViewProjectionMatrix") = m_shaderData->GetWorldViewProjectionMatrix();
	GetShaderVariable("uDiffuseTextureSampler").SetTexture(m_shaderData->GetTexture(),1);
}

void falcon::DiffuseTextureShader::CreateVariables()
{
	AddShaderVariable("WorldMatrix");
	AddShaderVariable("WorldViewProjectionMatrix");
	AddShaderVariable("uDiffuseTextureSampler");
}
