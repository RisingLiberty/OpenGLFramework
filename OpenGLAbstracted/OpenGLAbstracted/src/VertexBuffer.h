#pragma once

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	void Bind();
	void Unbind();

	void SetData(void* vertices, size_t size);

private:
	unsigned int m_Id;
	void* m_Data;
	size_t m_Size;

};