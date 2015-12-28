#include "stdafx.h"
#include "SkyBoxShader.h"

void falcon::SkyBoxShader::SetShaderVariables()
{
	GetShaderVariable("WorldViewProjectionMatrix") = m_shaderData->GetWorldViewProjectionMatrix();
	GetShaderVariable("uSkyBoxSampler").SetCubeTexture(m_shaderData->GetCubeTexture(),1);
}

void falcon::SkyBoxShader::CreateVariables()
{
	AddShaderVariable("WorldViewProjectionMatrix");
	AddShaderVariable("uSkyBoxSampler");
}
