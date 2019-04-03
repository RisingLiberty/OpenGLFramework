#include "Texture.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture::Texture(int width, int height)
{
	// Framebuffers can only be used as a render target if memory has been allocated to store the results.
	// This is done by attaching images for each buffer (color, depth, stencil or a combinatoin of depth and stencil).
	// There are 2 kinds of objects that can function as images: texture objects and renderbuffer objects.
	// The advantage of the formet is that they can be directly used in shaders as seen in the previous chapter, 
	// but renderbuffer objects may be more optimized specifically as render targets depending on your implementation.

	// We'd like to be able to render a scene and then use the result in the color buffer in another rendering operation,
	// so a texture is ideal in this case. Creating a texture for use as an image for the color buffer of the new framebuffer is as imple as
	// creating any texture.
	glGenTextures(1, &m_Id);
	this->Bind();

	// The difference between this texture and the textures you've seen before is the NULL value for the data parameter.
	// that makes sense, because the data is going to be created dynamically this time with rendering operations.
	// Since this is the image for the color buffer, the format and internalFormat parameters are a bit more restricted
	// the format parameter will typically be limited to either GL_RGB or GL_RGBA and the internalFormat to the color formats.
	// The resolution doesn't have to match the one of the default framebuffer but don't forget a glViewport call if you decide to vary.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::Texture(const std::string& path)
{
	// Textures are typically used for images to decorate 3D models, but in reality
	// they can be used to store many different kinds of data. It's possible to have 1D, 2D and even 3D textures, 
	// which can be used to store bulk data on the GPU. an example of another use for textures is storing certain
	// terrain information.
	glGenTextures(1, &m_Id);

	// Just like other objects, textures have to be bound to apply operations on them.
	// Since images are 2D arrays of pixels, it will be bound to the GL_TEXTURE_2D target.

	// The pixels in the texture will be addressed using texture coordinates during drawing operations.
	// These coordinates range from 0.0 to 1.0 where (0,0) is conventionally the bottom-left corner and (1,1) is the top right corner of the texture image.
	// The operation that uses these texture coordinates to retrieve color information from the pixels is called sampling.
	// There are different ways to approach this problem, each being appropriate for different scenarios.
	// OpenGL offers you many options to control how this sampling is done.

	// The amount of texture units supported differs per graphics card, but it will be at least 48.
	// It is safe to say that you will never hit this limit in even the most extreme graphics applications
	int width, height;
	unsigned char* data;

	data = stbi_load(path.c_str(), &width, &height, nullptr, STBI_rgb);

	// The first parameter after the texture target is the level of detail, where 0 is the base image.
	// This parameter can be used to load your own mipmap images.
	// The second parameter specifies the internal pixel format, the format in which pixels should be stored on the gpu.
	// many different formats are available, including compressed formats, so it's certainly worth taking a look at all of the options.
	// The third and fourth parameters specify the width and height of the image.
	// the fifth parameter should always have a value of 0 per specification.
	// The next 2 parameters describe the format of the pixels in the array that will be loaded.
	// The final parameters specifies the array itself.
	// the functions begins loading the image at coordinate (0,0) so pay attention to this.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);

	// The first thing you'll have to consider is how the texture should be sampled when a coordinate outside the range of 0 to 1 is given. 
	// OpenGL offers 4 ways of handling this.
	// GL_REPEAT: The integer part of the coordinate will be ignored and a repeating pattern is formed.
	// GL_MIRROERED_REPEAT: The texture will also be repeated, but it will be mirrored when the integer part of the coordinate is odd.
	// GL_CLAMP_TO_EDGE: the coordinate will simply be clamped between 0 and 1.
	// GL_CLAMP_TO_BORDER: the coordinates that fall outside the range will be given a specified border color.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// and you want to change the border color, you need to change the value of GL_TEXTURE_BORDER_COLOR bypassing an RGBA float array
	float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

	// Since texture coordinates are resolution independent, they won't always match a pixel exactly.
	// this happens when a texture image is stretched beyond its original size or when it's sized down. OpenGL offers various methods to decide
	// on the sampled color when this happens. This process is called filtering and the following methods are available.
	
	// GL_NEAREST: returns the pixel is closest to the coordinates.
	// GL_LINEAR: returns the weighted average of the 4 pixels surrounding the given coordinates.
	// GL_NEAREST_MIPMAP, GL_LINEAR_MIP_MAP_NEAREST,
	// GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR: Sample from mipmaps instead.
	
	// There is another way to filter textures: mipmaps
	// Mipmaps are smaller copies of your textures that have been sized down and filtered in advance.
	// It is recommended that you use them because they result in both a higher quality and higher performance.
	
	// To use mipmaps, select one of the four mipmap filtering methods.
	// GL_NEAREST_MIPMAP_NEAREST: Uses the mipmap that most  closely matches the size of the pixel being textured
	// and samples with nearest neighbor interpolation
	// GL_LINEAR_MIPMAP_NEAREST: Samples the closest mipmap with linear interpolation
	// GL_NEAREST_MIPMAP_LINEAR: Uses the 2 mipmaps that most closely match the size of the pixel being textures
	// and samples with nearest neighbor interpolation.
	// GL_LINEAR_MIPMAP_LINEAR: Samples closet two mipmaps with linear 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// As mentioned before, OpenGL expects the first pixel to be located in the bottom-left corner, 
	// which means that textures will be flipped when loaded with STB directly. To counteract that, the code 
	// will use flipped Y coordinates for texture coordinates from now on.
	// That means that (0,0) will be assumed to be the top0left corner instead of the bottom-left. This practice might
	// make texture coordinates more intuitive as a side-effect.
	
	// But how is the pixel array itself established? Textures in graphics applications will usually be a lot more sophisticated than simple patterns and
	// will be loaded from files. Best practice is to ave your files in a format that is natively supported by the hardware, but it may sometimes be more convenient to load
	// textures from common image formats like JPG and PNG. Unfortunately OpenGL doesn't offer any helper functions to load pixels from these image files, 
	// but that's where third-party libraries come in handy again!
	this->Bind();
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_Id);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_Id);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::GetId() const
{
	return m_Id;
}