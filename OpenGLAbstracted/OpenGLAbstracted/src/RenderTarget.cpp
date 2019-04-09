#include "RenderTarget.h"


RenderTarget::RenderTarget(int width, int height):
	FrameBuffer(),
	ColorBuffer(width, height),
	DepthStencilBuffer(width, height)
{
	FrameBuffer.AttachColorBuffer(ColorBuffer);
	FrameBuffer.AttachRenderBuffer(DepthStencilBuffer);
}

void RenderTarget::Bind()
{
	FrameBuffer.Bind();
}

void RenderTarget::Unbind()
{
	FrameBuffer.Unbind();
	ColorBuffer.Activate(0);
	ColorBuffer.Bind();
}