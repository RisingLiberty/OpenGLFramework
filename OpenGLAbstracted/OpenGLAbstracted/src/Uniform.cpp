#include "Uniform.h"

Uniform::Uniform()
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