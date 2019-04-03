#include "VertexBuffer.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &m_Id);
	this->Bind();
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_Id);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_Id);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(size_t size, void* vertices)
{
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}