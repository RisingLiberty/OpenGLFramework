#include "IndexBuffer.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

IndexBuffer::IndexBuffer(void* data, size_t size, IndexBufferFormat format):
	m_Data(data),
	m_Size(size),
	m_Format(format)
{
	glGenBuffers(1, &m_Id);
	this->Bind();
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_Id);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void IndexBuffer::SetBuffer(void* indices, size_t size)
{
	m_Data = indices;
	m_Size = size;

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void IndexBuffer::SetFormat(IndexBufferFormat format)
{
	m_Format = format;
}

unsigned int IndexBuffer::GetId() const
{
	return m_Id;
}

void* IndexBuffer::GetData() const
{
	return m_Data;
}

size_t IndexBuffer::GetSize() const
{
	return m_Size;
}

IndexBufferFormat IndexBuffer::GetFormat() const
{
	return m_Format;
}