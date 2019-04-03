#include "ShaderProgram.h"

#include <iostream>

ShaderProgram::ShaderProgram()
{
	m_Id = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_Id);
}

void ShaderProgram::AttachShader(unsigned int shaderId)
{
	glAttachShader(m_Id, shaderId);
	m_AttachedShaders.emplace_back(shaderId);
}

void ShaderProgram::Detachshader(unsigned int shaderId)
{
	glDetachShader(m_Id, shaderId);
	m_AttachedShaders.remove(shaderId);
}

void ShaderProgram::Bind()
{
	glUseProgram(m_Id);
}

void ShaderProgram::UnBind()
{
	glUseProgram(0);
}

void ShaderProgram::Link()
{
	glLinkProgram(m_Id);
}

void ShaderProgram::BindFragDataLocation(unsigned int colorNumber, const std::string& name)
{
	glBindFragDataLocation(m_Id, colorNumber, name.c_str());
}

unsigned int ShaderProgram::GetUniformLocation(const std::string& name)
{
	unsigned int loc = glGetUniformLocation(m_Id, name.c_str());

	if (loc == -1)
		std::cout << "warning in shader with id"<< m_Id << "\nUniform with name " << name << " has -1 as location\n";

	return loc;
}

