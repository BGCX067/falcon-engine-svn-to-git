#include "stdafx.h"
#include "VertexBuffer.h"

#define BUFFER_OFFSET(bytes) ((GLubyte*)NULL + (bytes))


falcon::VertexBuffer::VertexBuffer():m_bufferID(0)
{

}

falcon::VertexBuffer::~VertexBuffer()
{
	if(m_bufferID != 0)
		glDeleteBuffers(1,&m_bufferID);
}

void falcon::VertexBuffer::Init()
{
	glGenBuffers(1, &m_bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
	int size = GetSize();
	glBufferData(GL_ARRAY_BUFFER, size, m_buffer.data(), GL_STATIC_DRAW);
}

void falcon::VertexBuffer::Activate()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
}

void falcon::VertexBuffer::Deactivate()
{
	glBindBuffer(GL_ARRAY_BUFFER,0);
}