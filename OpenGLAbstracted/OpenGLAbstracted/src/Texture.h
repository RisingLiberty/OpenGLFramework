#pragma once

#include <string>

class Texture
{
public:
	Texture(int width, int height);
	Texture(const std::string& path);
	~Texture();

	void Bind();
	void Unbind();

	unsigned int GetId() const;

private:
	unsigned int m_Id;
};