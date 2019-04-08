#include "Vertex.h"

Vertex::Vertex(void* data, unsigned short size):
	m_Data(data),
	m_Size(size)
{

}

void* Vertex::GetData() const
{
	return m_Data;
}

unsigned short Vertex::GetSize() const
{
	return m_Size;
}