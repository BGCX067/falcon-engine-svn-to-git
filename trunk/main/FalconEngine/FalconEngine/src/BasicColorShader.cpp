#include "stdafx.h"
#include "BasicColorShader.h"

void falcon::BasicColorShader::SetShaderVariables()
{
	GetShaderVariable("WorldMatrix") = m_shaderData->GetWorldMatrix();
	GetShaderVariable("WorldViewProjectionMatrix") = m_shaderData->GetWorldViewProjectionMatrix();
	GetShaderVariable("uColor") = m_shaderData->GetDiffuseColor();
}

void falcon::BasicColorShader::CreateVariables()
{
	AddShaderVariable("WorldMatrix");
	AddShaderVariable("WorldViewProjectionMatrix");
	AddShaderVariable("uColor");
}