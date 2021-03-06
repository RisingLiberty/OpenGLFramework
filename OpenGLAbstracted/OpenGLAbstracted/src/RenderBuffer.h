#pragma once

class RenderBuffer
{
public:
	RenderBuffer(int width, int height);
	~RenderBuffer();
	void Bind();
	void Unbind();

	unsigned int GetId() const;

private:
	unsigned int m_Id;
};