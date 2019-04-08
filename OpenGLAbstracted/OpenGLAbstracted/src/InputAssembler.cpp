#include "InputAssembler.h"

#include "VertexBuffer.h"

InputAssembler::InputAssembler():
	m_VertexBuffer(nullptr),
	m_IndexBuffer(nullptr),
	m_InputLayout(),
	m_Topology(PrimitiveTopology::UNDEFINED)
{

}

InputAssembler::InputAssembler(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, const InputLayout& inputLayout, PrimitiveTopology primitiveTopology) :
	m_VertexBuffer(vertexBuffer),
	m_IndexBuffer(indexBuffer),
	m_InputLayout(inputLayout),
	m_Topology(primitiveTopology)
{

}
