#include "stdafx.h"
#include "IndexBuffer.h"

falcon::IndexBuffer::IndexBuffer():m_bufferID(0)
{

}

falcon::IndexBuffer::~IndexBuffer()
{
	//if(m_bufferID != 0)
		glDeleteBuffers(1,&m_bufferID);
}

void falcon::IndexBuffer::Init()
{
	glGenBuffers(1, &m_bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetSize(), m_buffer.data(), GL_STATIC_DRAW);
}

void falcon::IndexBuffer::Activate()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
}

void falcon::IndexBuffer::Deactivate()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

