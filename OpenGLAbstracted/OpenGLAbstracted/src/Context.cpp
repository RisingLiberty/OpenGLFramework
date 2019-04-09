#include "Context.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

Context::Context()
{
	glewExperimental = true;
	glewInit();

	glfwWindowHint(GLFW_SAMPLES, 4);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
}

std::string Context::GetVersion() const
{
	const GLubyte* version = glGetString(GL_VERSION);
	return std::string((const char*)version);
}

std::string Context::GetRenderer() const
{
	const GLubyte* version = glGetString(GL_RENDERER);
	return std::string((const char*)version);
}

std::string Context::GetVendor() const
{
	const GLubyte* version = glGetString(GL_VENDOR);
	return std::string((const char*)version);
}

std::string Context::GetShadingLanguageVersion() const
{
	const GLubyte* version = glGetString(GL_SHADING_LANGUAGE_VERSION);
	return std::string((const char*)version);
}