#pragma once

class Vertex;

class VertexBuffer
{
public:
	VertexBuffer();
	VertexBuffer(void* data, size_t size);
	~VertexBuffer();

	void Bind();
	void Unbind();

	void SetData(void* vertices, size_t size);

private:
	unsigned int m_Id;
	void* m_Data;
	size_t m_Size;
	
};