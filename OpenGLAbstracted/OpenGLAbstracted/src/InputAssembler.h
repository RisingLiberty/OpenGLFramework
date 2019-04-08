#pragma once

#include "InputLayout.h"

class VertexBuffer;
class IndexBuffer;

enum class PrimitiveTopology
{
	UNDEFINED,

	TRIANGLE_LIST
};

struct InputAssembler
{
public:
	InputAssembler();
	InputAssembler(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, const InputLayout& inputLayout, PrimitiveTopology primitiveTopology);

	VertexBuffer* m_VertexBuffer;
	IndexBuffer* m_IndexBuffer;
	InputLayout m_InputLayout;
	PrimitiveTopology m_Topology;
};