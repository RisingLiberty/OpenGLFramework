#include "VertexAttribute.h"

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