#pragma once

#include "VertexAttribute.h"
#include <vector>

class InputLayout
{
public:
	InputLayout();
	InputLayout(const std::vector<VertexAttribute>& attributes);

	void AddAttribute(const VertexAttribute& attribute);
	
	const std::vector<VertexAttribute>& GetAttributes() const;
	unsigned short GetSize() const;
private:
	std::vector<VertexAttribute> m_Attributes;
};