#pragma once

#include <string>

enum class UniformType
{
	BOOL,
	UNSIGNED_BYTE,
	BYTE,
	UNSIGNED_SHORT,
	SHORT,
	UNSIGNED_INT,
	INT,
	FLOAT,
	DOUBLE,
	VEC2,
	VEC3,
	MAT3,
	MAT4
};

class Uniform
{
public:
	Uniform();
	~Uniform();

	int GetLocation() const;
	std::string GetName() const;
	UniformType GetType() const;

private:
	int m_Location;
	std::string m_Name;
	UniformType m_Type;
};