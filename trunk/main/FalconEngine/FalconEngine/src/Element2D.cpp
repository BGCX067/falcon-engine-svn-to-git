#include "Element2D.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Mesh.h"
#include <boost\shared_ptr.hpp>
#include <boost\ref.hpp>

falcon::Element2D::Element2D(float x, float y, float width, float height)
	:m_shader(nullptr)
	,m_shaderData(nullptr)
	,m_mesh(nullptr)
{
	m_pos.x = x;
	m_pos.y = y;
	m_width = width;
	m_height = height;
}

falcon::Element2D::~Element2D()
{
	delete m_shaderData;
	delete m_mesh;
}

void falcon::Element2D::Draw()
{
	if (m_shader != 0 && m_mesh != 0)
	{
		m_shader->SetShaderData(m_shaderData);
		m_mesh->SetShader(m_shader);
		m_mesh->Draw();
	}
}

void falcon::Element2D::Init()
{
 	VertexBuffer* vb = new VertexBuffer();
 	IndexBuffer* ib = new IndexBuffer();

	// TODO: Find a better way to convert to NDC
	// NO MAGIC NUMBERS!!!!
	float xPos = (m_pos.x/1280)*2.0f-1.0f;
	float yPos = (m_pos.y/720)*2.0f-1.0f;
	float width = (m_width/1280)*2.0f;
	float height = (m_height/720)*2.0f;

	// Flip Y
	yPos *= -1;

	vb->AddVertex(VertexStruct(Vec3(xPos,yPos,0), Vec3(0,0,-1), Vec2(0,0)));
	vb->AddVertex(VertexStruct(Vec3(xPos + width, yPos,0), Vec3(0,0,-1), Vec2(1,0)));
	vb->AddVertex(VertexStruct(Vec3(xPos + width,yPos - height,0), Vec3(0,0,-1), Vec2(1,1)));
	vb->AddVertex(VertexStruct(Vec3(xPos,yPos - height,0), Vec3(0,0,-1), Vec2(0,1)));

	ib->AddIndex(0);
	ib->AddIndex(1);
	ib->AddIndex(2);
	ib->AddIndex(0);
	ib->AddIndex(2);
	ib->AddIndex(3);

	m_mesh = new Mesh();

	vb->Init();
	m_mesh->SetVertexBuffer(vb);

	ib->Init();
	m_mesh->SetIndexBuffer(ib);
}

void falcon::Element2D::Translate(float xDiff, float yDiff)
{
	// TODO: Find a better way to convert to NDC
	// NO MAGIC NUMBERS!!!!
	float xPos = ((m_pos.x + xDiff)/1280)*2.0f-1.0f;
	float yPos = ((m_pos.y + yDiff)/720)*2.0f-1.0f;
	float width = (m_width/1280)*2.0f;
	float height = (m_height/720)*2.0f;

	// Flip Y
	yPos *= -1;

	VertexBuffer& buffer = m_mesh->GetVertexBuffer();
	buffer.Clear();
	buffer.AddVertex(VertexStruct(Vec3(xPos,yPos,0), Vec3(0,0,-1), Vec2(0,0)));
	buffer.AddVertex(VertexStruct(Vec3(xPos + width, yPos,0), Vec3(0,0,-1), Vec2(1,0)));
	buffer.AddVertex(VertexStruct(Vec3(xPos + width,yPos - height,0), Vec3(0,0,-1), Vec2(1,1)));
	buffer.AddVertex(VertexStruct(Vec3(xPos,yPos - height,0), Vec3(0,0,-1), Vec2(0,1)));
	buffer.Init();
 
	m_pos.x += xDiff;
	m_pos.y += yDiff;
}

void falcon::Element2D::SetPos( const Vec2 pos )
{
	float xPos = (pos.x / 1280)*2.0f-1.0f;
	float yPos = (pos.y / 720)*2.0f-1.0f;
	float width = (m_width/1280)*2.0f;
	float height = (m_height/720)*2.0f;

	VertexBuffer& buffer = m_mesh->GetVertexBuffer();
	buffer.Clear();
	buffer.AddVertex(VertexStruct(Vec3(xPos,yPos,0), Vec3(0,0,-1), Vec2(0,0)));
	buffer.AddVertex(VertexStruct(Vec3(xPos + width, yPos,0), Vec3(0,0,-1), Vec2(1,0)));
	buffer.AddVertex(VertexStruct(Vec3(xPos + width,yPos - height,0), Vec3(0,0,-1), Vec2(1,1)));
	buffer.AddVertex(VertexStruct(Vec3(xPos,yPos - height,0), Vec3(0,0,-1), Vec2(0,1)));
	buffer.Init();

	m_pos.x = pos.x;
	m_pos.y = pos.y;
}

void falcon::Element2D::SetWidth( const float width )
{
	float xPos = (m_pos.x / 1280)*2.0f-1.0f;
	float yPos = (m_pos.y / 720)*2.0f-1.0f;
	float newWidth = (width/1280)*2.0f;
	float height = (m_height/720)*2.0f;

	VertexBuffer& buffer = m_mesh->GetVertexBuffer();
	buffer.Clear();
	buffer.AddVertex(VertexStruct(Vec3(xPos,yPos,0), Vec3(0,0,-1), Vec2(0,0)));
	buffer.AddVertex(VertexStruct(Vec3(xPos + newWidth, yPos,0), Vec3(0,0,-1), Vec2(1,0)));
	buffer.AddVertex(VertexStruct(Vec3(xPos + newWidth,yPos - height,0), Vec3(0,0,-1), Vec2(1,1)));
	buffer.AddVertex(VertexStruct(Vec3(xPos,yPos - height,0), Vec3(0,0,-1), Vec2(0,1)));
	buffer.Init();

	m_width = width;
}

void falcon::Element2D::SetHeight( const float height )
{
	float xPos = (m_pos.x / 1280)*2.0f-1.0f;
	float yPos = (m_pos.y / 720)*2.0f-1.0f;
	float width = (m_width/1280)*2.0f;
	float newHeight = (height/720)*2.0f;

	VertexBuffer& buffer = m_mesh->GetVertexBuffer();
	buffer.Clear();
	buffer.AddVertex(VertexStruct(Vec3(xPos,yPos,0), Vec3(0,0,-1), Vec2(0,0)));
	buffer.AddVertex(VertexStruct(Vec3(xPos + width, yPos,0), Vec3(0,0,-1), Vec2(1,0)));
	buffer.AddVertex(VertexStruct(Vec3(xPos + width,yPos - newHeight,0), Vec3(0,0,-1), Vec2(1,1)));
	buffer.AddVertex(VertexStruct(Vec3(xPos,yPos - newHeight,0), Vec3(0,0,-1), Vec2(0,1)));
	buffer.Init();

	m_height = height;
}

//  luabind::scope falcon::Element2D::Register()
//  {
//  	return
//  		luabind::class_<Element2D, Element2D*>("Element2D")
//  		.def(luabind::constructor<float, float, float, float>());
//  }

