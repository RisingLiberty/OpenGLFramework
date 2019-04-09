#include "VertexAttribute.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

VertexAttribute::VertexAttribute(const std::string& name, VertexAttributeType type) :
	m_Name(name),
	m_Type(type)
{

}

const std::string& VertexAttribute::GetName() const
{
	return m_Name;
}

VertexAttributeType VertexAttribute::GetType() const
{
	return m_Type;
}

unsigned char VertexAttribute::GetSize() const
{
	switch (m_Type)
	{
	case VertexAttributeType::UNSIGNED_INT:	return sizeof(unsigned int);
	case VertexAttributeType::INT:			return sizeof(int);
	case VertexAttributeType::FLOAT:		return sizeof(float);
	case VertexAttributeType::VEC2:			return sizeof(float) * 2;
	case VertexAttributeType::VEC3:			return sizeof(float) * 3;
	case VertexAttributeType::VEC4:			return sizeof(float) * 4;
	}
	return 0;
}

int VertexAttribute::GetOpenGLType() const
{
	switch (m_Type)
	{
	case VertexAttributeType::UNSIGNED_INT: return GL_UNSIGNED_INT;
	case VertexAttributeType::INT:			return GL_INT;
	case VertexAttributeType::FLOAT:		return GL_FLOAT;
	case VertexAttributeType::VEC2:			return GL_FLOAT;
	case VertexAttributeType::VEC3:			return GL_FLOAT;
	case VertexAttributeType::VEC4:			return GL_FLOAT;
	}

	return GL_FALSE;
}

size_t VertexAttribute::GetOpenGLCount() const
{
	switch (m_Type)
	{
	case VertexAttributeType::UNDEFINED:	return 0;
	case VertexAttributeType::UNSIGNED_INT: return 1;
	case VertexAttributeType::INT:			return 1;
	case VertexAttributeType::FLOAT:		return 1;
	case VertexAttributeType::VEC2:			return 2;
	case VertexAttributeType::VEC3:			return 3; 
	case VertexAttributeType::VEC4:			return 4;
	}

	return 0;
}