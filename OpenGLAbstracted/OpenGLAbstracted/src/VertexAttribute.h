#pragma once

#include <string>

enum class VertexAttributeType
{
	UNDEFINED,

	UNSIGNED_INT,
	INT,
	FLOAT,
	VEC2,
	VEC3,
	VEC4
};

class VertexAttribute
{
public:
	VertexAttribute(const std::string& name, VertexAttributeType type);

	const std::string& GetName() const;
	VertexAttributeType GetType() const;
	unsigned char GetSize() const;

	int GetOpenGLType() const;
	size_t GetOpenGLCount() const;

private:
	std::string m_Name;
	VertexAttributeType m_Type;

};