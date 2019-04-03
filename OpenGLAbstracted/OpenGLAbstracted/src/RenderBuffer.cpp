#include "RenderBuffer.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

RenderBuffer::RenderBuffer(int width, int height)
{
	// As we're using a depth and stencil buffer to render the spinnig cube, we'll have to create them aswell.
	// OpenGL allows you to combine those into one image, so we'll have to create just one more before we can use the framebuffer.
	// Although we could do this by creating another texture, it is more efficient to store htese buffers in a Renderbuffer Object,
	// because we're only interested in reading the color buffer in a shader.
	glGenRenderbuffers(1, &m_Id);
	this->Bind();
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
}

void RenderBuffer::Bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, m_Id);
}

void RenderBuffer::Unbind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

unsigned int RenderBuffer::GetId() const
{
	return m_Id;
}