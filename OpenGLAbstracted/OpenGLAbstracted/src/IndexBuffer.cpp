#include "IndexBuffer.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <cassert>

IndexBuffer::IndexBuffer()
{
	glGenBuffers(1, &m_Id);
	this->Bind();
}

IndexBuffer::IndexBuffer(void* data, size_t size, IndexBufferFormat format):
	m_Format(format)
{
	glGenBuffers(1, &m_Id);
	this->Bind();
	this->SetBuffer(data, size);
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

size_t IndexBuffer::GetCount() const
{
	if (m_Format == IndexBufferFormat::UINT16)
		return m_Size / sizeof(uint16_t);
	else
		return m_Size / sizeof(uint32_t);
}

IndexBufferFormat IndexBuffer::GetFormat() const
{
	return m_Format;
}

int IndexBuffer::ToOpenGLFormat() const
{
	switch (m_Format)
	{
	case IndexBufferFormat::UINT16:
		return GL_UNSIGNED_SHORT;
	case IndexBufferFormat::UINT32:
		return GL_UNSIGNED_INT;
	}
	
	assert(false);
}