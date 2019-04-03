#include "FragmentShader.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

FragmentShader::FragmentShader(const std::string& source) :
	Shader(source)
{
	// Just like vertex buffers, creating a shade itself starts with creating a shader object and loading data into it
	m_Id = glCreateShader(GL_FRAGMENT_SHADER);
	const char* sourceRaw = source.c_str();

	// Unlike VBOs, you can simply pass a reference to shader functions instead of making it active
	// or anything like that. The glShaderSource function can take multiple source string in an array,
	// but you'll usually have your source code in one char array. The last parameter can contain an array of source code string lengths.
	// passing NULL simply makes it stop at the null terminator.
	glShaderSource(m_Id, 1, &sourceRaw, nullptr);

	this->Compile();

}