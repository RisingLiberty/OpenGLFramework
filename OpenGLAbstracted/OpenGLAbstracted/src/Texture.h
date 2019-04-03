#pragma once

#include <string>

#include <glm/glm.hpp>

enum class TextureWrapType
{
	REPEAT,
	MIRROR_REPEAT,
	CLAMP_TO_EDGE,
	CLAMP_TO_BORDER
};

enum class FilteringMode
{
	NEAREST,
	LINEAR,
	NEAREST_MIPMAP,
	NEAREST_MIPMAP_LINEAR
};

class Texture
{
public:
	Texture(int width, int height);
	Texture(const std::string& path);
	~Texture();

	void Bind();
	void Unbind();
	
	void LoadData(const std::string& path);
	void LoadDefaultParameters();

	void SetWrapMode(TextureWrapType wrapType);
	void SetBorderColor(const glm::vec4& color);
	void SetFilterMode(FilteringMode mode);

	unsigned int GetId() const;

private:
	unsigned int m_Id;
};