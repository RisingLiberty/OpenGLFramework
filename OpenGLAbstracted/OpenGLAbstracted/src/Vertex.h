#pragma once

#include "VertexAttribute.h"

class Vertex
{
public:
	Vertex(void* data, unsigned short size);

	void* GetData() const;
	unsigned short GetSize() const;

private:
	void* m_Data;
	unsigned short m_Size;

};