#pragma once

enum class IndexBufferFormat
{
	UINT16,
	UINT32
};

class IndexBuffer
{
public: 
	IndexBuffer();
	IndexBuffer(void* data, size_t size, IndexBufferFormat format);
	~IndexBuffer();

	void Bind();
	void Unbind();

	void SetBuffer(void* indices, size_t size);
	void SetFormat(IndexBufferFormat format);

	unsigned int GetId() const;
	void* GetData() const;
	size_t GetSize() const;
	size_t GetCount() const;
	IndexBufferFormat GetFormat() const;

	int ToOpenGLFormat() const;

private:
	unsigned int m_Id;

	void* m_Data;
	size_t m_Size;

	IndexBufferFormat m_Format;
};