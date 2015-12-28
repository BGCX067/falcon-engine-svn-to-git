#include "stdafx.h"
#include "RenderContext.h"

falcon::RenderContext::RenderContext():
	m_diffuseColor(Vec3(0.3f, 0.6f, 0.8f))
{

}

falcon::RenderContext::~RenderContext()
{

}

void falcon::RenderContext::SetViewProjectionMatrix(const Mat4& view, const Mat4& projection)
{
	m_viewMatrix = view;
	m_projectionMatrix = projection;
	//COLUMN MAJOR ==> PROJ x VIEW (row major = view x proj)
	m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix; 
}