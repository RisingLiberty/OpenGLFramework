#pragma once

#include "Texture.h"
#include "RenderBuffer.h"

class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	void AttachColorBuffer(const Texture& texture);
	void AttachRenderBuffer(const RenderBuffer& renderBuffer);

	void Bind();
	void Unbind();

private:
	unsigned int m_Id;
};