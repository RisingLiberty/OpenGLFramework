#pragma once

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	void Bind();
	void Unbind();

	void SetData(size_t size, void* vertices);

private:
	unsigned int m_Id;

};