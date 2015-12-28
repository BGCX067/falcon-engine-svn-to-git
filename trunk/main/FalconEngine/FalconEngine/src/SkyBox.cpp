#include "stdafx.h"
#include "SkyBox.h"
#include "ResourceManager.h"
#include "RenderContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

//////////////////////////////////////////////////////////////////////////
///						LUA REGISTRATION							   ///
//////////////////////////////////////////////////////////////////////////
luabind::scope falcon::SkyBox::Register()
{
	return
		luabind::class_<SkyBox, SkyBox*>("SkyBox")
		.def(luabind::constructor<std::string>())
		.def("Init", &SkyBox::Init);
}

falcon::SkyBox::SkyBox(std::string texturePath): 
	m_texturePath(texturePath),
	m_vBuffer(0),
	m_iBuffer(0),
	m_shader(0),
	m_shaderData(0),
	m_textureID(0),
	m_location(Vec3(0,0,0))
{

}

falcon::SkyBox::~SkyBox()
{
	delete m_shaderData;
	delete m_vBuffer;
	delete m_iBuffer;
}

void falcon::SkyBox::Init(ResourceManager* resourceManager)
{
	BuildCube();
	m_shader = resourceManager->GetShader("SkyBox");
	m_textureID = resourceManager->GetCubeTexture(m_texturePath);
	m_shaderData = new ShaderData();
	m_shaderData->SetCubeTexture(m_textureID);
}

void falcon::SkyBox::Draw(RenderContext& renderContext)
{
	Mat4 worldMatrix = Mat4();
	worldMatrix.setTranslation(m_location);

	Mat4 worldViewProjectionMatrix = renderContext.GetViewProjectionMatrix() * worldMatrix;

	if(m_shader != 0  && m_vBuffer != 0 && m_iBuffer != 0){
		m_shaderData->SetWorldViewProjectionMatrix(worldViewProjectionMatrix);
		m_shader->SetShaderData(m_shaderData);

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
}

void falcon::SkyBox::SetLocation(const Vec3& location)
{
	m_location = location;
}

void falcon::SkyBox::BuildCube()
{
	m_vBuffer = new VertexBuffer();

	m_vBuffer->AddVertex(VertexStruct(Vec3(-500,-500,-500),Vec3(0,0,0), Vec2(0,0)));
	m_vBuffer->AddVertex(VertexStruct(Vec3(-500,500,-500),Vec3(0,0,0), Vec2(0,0)));
	m_vBuffer->AddVertex(VertexStruct(Vec3(500,500,-500),Vec3(0,0,0), Vec2(0,0)));
	m_vBuffer->AddVertex(VertexStruct(Vec3(500,-500,-500),Vec3(0,0,0), Vec2(0,0)));

	m_vBuffer->AddVertex(VertexStruct(Vec3(-500,-500,500),Vec3(0,0,0), Vec2(0,0)));
	m_vBuffer->AddVertex(VertexStruct(Vec3(-500,500,500),Vec3(0,0,0), Vec2(0,0)));
	m_vBuffer->AddVertex(VertexStruct(Vec3(500,500,500),Vec3(0,0,0), Vec2(0,0)));
	m_vBuffer->AddVertex(VertexStruct(Vec3(500,-500,500),Vec3(0,0,0), Vec2(0,0)));

	m_vBuffer->Init();

	m_iBuffer = new IndexBuffer();

	AddQuad(0,1,2,3);
	AddQuad(2,6,7,3);
	AddQuad(6,5,4,7);
	AddQuad(5,1,0,4);
	AddQuad(1,5,6,2);
	AddQuad(0,3,7,4);

	m_iBuffer->Init();
}	

void falcon::SkyBox::AddQuad(const unsigned int a, const unsigned int b, const unsigned int c, const unsigned int d)
{
	m_iBuffer->AddIndex(c);
	m_iBuffer->AddIndex(b);
	m_iBuffer->AddIndex(a);

	m_iBuffer->AddIndex(d);
	m_iBuffer->AddIndex(c);
	m_iBuffer->AddIndex(a);
}