#pragma once

#include "RenderBuffer.h"
#include "FrameBuffer.h"
#include "Texture.h"

class RenderTarget
{
public:
	RenderTarget(int width, int height);

	void Bind();
	void Unbind();

private:
	FrameBuffer m_FrameBuffer;
	Texture m_ColorBuffer;
	RenderBuffer m_DepthStencilBuffer;
};