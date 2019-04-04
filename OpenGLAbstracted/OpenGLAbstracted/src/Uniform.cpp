#include "Uniform.h"

Uniform::Uniform() :
	m_Location(-1),
	m_Name(""),
	m_Type(UniformType::UNDEFINED)
{
}

Uniform::Uniform(int location, const std::string& name, UniformType type):
	m_Location(location),
	m_Name(name),
	m_Type(type)
{

}

Uniform::~Uniform()
{

}

int Uniform::GetLocation() const
{
	return m_Location;
}

std::string Uniform::GetName() const
{
	return m_Name;
}

UniformType Uniform::GetType() const
{
	return m_Type;
}