#include "InputAssembler.h"

#include "VertexBuffer.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <cassert>

InputAssembler::InputAssembler():
	VertexBuffer(nullptr),
	IndexBuffer(nullptr),
	InputLayout(),
	Topology(PrimitiveTopology::UNDEFINED)
{

}

InputAssembler::InputAssembler(class VertexBuffer* vertexBuffer, class IndexBuffer* indexBuffer, const class InputLayout& inputLayout, PrimitiveTopology primitiveTopology):
	VertexBuffer(vertexBuffer),
	IndexBuffer(indexBuffer),
	InputLayout(inputLayout),
	Topology(primitiveTopology)
{

}

int InputAssembler::ToOpenGLTopology() const
{
	switch (Topology)
	{
	case PrimitiveTopology::TRIANGLE_LIST:
		return GL_TRIANGLES;
	}

	assert(false);
	return GL_FALSE;
}
