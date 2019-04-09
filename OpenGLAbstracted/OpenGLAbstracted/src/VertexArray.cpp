#include "VertexArray.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_Id);
	this->Bind();
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_Id);
}

void VertexArray::Bind()
{
	glBindVertexArray(m_Id);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}