#include "stdafx.h"
#include "Mesh.h"
#include "RenderContext.h"

//////////////////////////////////////////////////////////////////////////
///						LUA REGISTRATION							   ///
//////////////////////////////////////////////////////////////////////////
luabind::scope falcon::Mesh::Register()
{
	return
		luabind::class_<Mesh, Mesh*>("Mesh")
			.def(luabind::constructor<>());
}

falcon::Mesh::Mesh(): m_vBuffer(nullptr), m_iBuffer(nullptr)
{
}

falcon::Mesh::~Mesh()
{
	if(m_vBuffer != nullptr) delete m_vBuffer;
	m_vBuffer = 0;

	if(m_iBuffer != nullptr) delete m_iBuffer;
	m_iBuffer = 0;

}

void falcon::Mesh::Draw(/*const RenderContext& / *renderContext* /*/)
{
	m_shader->Activate();
	m_vBuffer->Activate();
	m_iBuffer->Activate();

	//Bind buffers to vertex Attributes in shader
	m_shader->SetAttributes();
	m_shader->SetShaderVariables();
	//draw the mesh
	glDrawElements(GL_TRIANGLES, m_iBuffer->GetLength(), GL_UNSIGNED_INT,0);

	m_iBuffer->Deactivate();
	m_vBuffer->Deactivate();
	m_shader->Deactivate();
}