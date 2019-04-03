#include "RenderTarget.h"


RenderTarget::RenderTarget(int width, int height):
	m_FrameBuffer(),
	m_ColorBuffer(width, height),
	m_DepthStencilBuffer(width, height)
{
	m_FrameBuffer.AttachColorBuffer(m_ColorBuffer);
	m_FrameBuffer.AttachRenderBuffer(m_DepthStencilBuffer);
}

void RenderTarget::Bind()
{
	m_FrameBuffer.Bind();
}

void RenderTarget::Unbind()
{
	m_FrameBuffer.Unbind();
}