#pragma once

#include "RenderBuffer.h"
#include "FrameBuffer.h"
#include "Texture.h"

struct RenderTarget
{
public:
	RenderTarget(int width, int height);

	void Bind();
	void Unbind();

	FrameBuffer FrameBuffer;
	Texture ColorBuffer;
	RenderBuffer DepthStencilBuffer;
};