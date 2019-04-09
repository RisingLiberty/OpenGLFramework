#pragma once

#include "InputLayout.h"

enum class PrimitiveTopology
{
	UNDEFINED,

	TRIANGLE_LIST
};

struct InputAssembler
{
public:
	InputAssembler();
	InputAssembler(class VertexBuffer* vertexBuffer, class IndexBuffer* indexBuffer, const class InputLayout& inputLayout, PrimitiveTopology primitiveTopology);

	int ToOpenGLTopology() const;

	class VertexBuffer* VertexBuffer;
	class IndexBuffer* IndexBuffer;
	class InputLayout InputLayout;
	PrimitiveTopology Topology;
};