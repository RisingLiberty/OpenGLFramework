#include "InputLayout.h"

InputLayout::InputLayout()
{
}

InputLayout::InputLayout(const std::vector<VertexAttribute>& attributes) :
	m_Attributes(attributes)
{

}

void InputLayout::AddAttribute(const VertexAttribute& attribute)
{
	m_Attributes.emplace_back(attribute);
}

const std::vector<VertexAttribute>& InputLayout::GetAttributes() const
{
	return m_Attributes;
}

unsigned short InputLayout::GetSize() const
{
	unsigned short size = 0;
	for (VertexAttribute attribute : m_Attributes)
	{
		size += attribute.GetSize();
	}

	return size;
}