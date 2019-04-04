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
	VEC4,
	MAT3,
	MAT4,

	UNDEFINED
};

class Uniform
{
public:
	Uniform();
	Uniform(int location, const std::string& name, UniformType type);
	~Uniform();

	int GetLocation() const;
	std::string GetName() const;
	UniformType GetType() const;

private:
	int m_Location;
	std::string m_Name;
	UniformType m_Type;
}; 