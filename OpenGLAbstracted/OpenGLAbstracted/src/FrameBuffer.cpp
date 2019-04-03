#include "FrameBuffer.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

FrameBuffer::FrameBuffer()
{
	//Create framebuffer
	// You cannot use the framebuffer yet at this point, because it is not complete.
	// A framebuffer is generally complete if:
	// 1) at least one buffer has been attached (eg. color, depth or stencil)
	// 2) There must be at least one color attachment (OpenGL 4.1 and earlier)
	// 3) All attachments are copmlete (For example, a texture attachment needs to have memory reserved).
	// 4) All attachments must have the same number of multisamples.
	glGenFramebuffers(1, &m_Id);

	this->Bind();
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_Id);
}

void FrameBuffer::AttachColorBuffer(const Texture& texture)
{
	// attach the image to the framebuffer
	// the second parameter implies that you can have mulitple color attachments.
	// a fragment shader can output different data to any of these by linking out variables to attachments with the glBindFragDataLocation
	// function we used earlier. We'll stick to one output for now. The last parameter specifies the mipmap level the image should be attached to.
	// Mipmapping is not of any use, since the color buffer image will be rendered at its riginal size when using it for post-processing.
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.GetId(), 0);
}

void FrameBuffer::AttachRenderBuffer(const RenderBuffer& renderBuffer)
{
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer.GetId());
}

void FrameBuffer::Bind()
{
	// You can check if a framebuffer is complete at any time by calling glCheckFramebufferStatus and check if it returns GL_FRAMEBUFFER_COMPLETE.
	// you don't have to do this check, but it's usually a good thing to verify, just like checking if your shaders compiled successfully.

	// The first parameter specifies the target the framebuffer should be attached to.
	// OpenGL makes a distinciton here between GL_DRAW_FRAMEBUGGER and GL_READ_FRAMEBUFFER.
	// The tramebuffer bound to read is used in calls to glReadPixels, but since this distinction in normal applications
	// is fairly rare, you can have your actions aply to both by using GL_FRAMEBUFFER
	glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
}

void FrameBuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}