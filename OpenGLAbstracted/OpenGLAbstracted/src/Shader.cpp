#include "Shader.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace
{
	void LogShaderOutput(unsigned int id)
	{
		// get the compile status
		int status;
		glGetShaderiv(id, GL_COMPILE_STATUS, &status);

		// Successful compilation?
		if (status == GL_FALSE)
		{
			// buffer for debug info
			char buffer[512];

			// get the debug info of the shader compilation
			glGetShaderInfoLog(id, 512, NULL, buffer);
			std::cout << "Shader compile error\n";
			std::cout << buffer << "\n";
		}
		else
			std::cout << "Shader compiled successfuly\n";
	}
}

Shader::Shader(const std::string& source):
	m_Source(source)
{

}

Shader::~Shader()
{
	glDeleteShader(m_Id);
}

unsigned int Shader::GetId() const
{
	return m_Id;
}

const std::string& Shader::GetSource() const
{
	return m_Source;
}

bool Shader::IsMarkedForDeletion() const
{
	int status;
	glGetShaderiv(m_Id, GL_DELETE_STATUS, &status);
	return status;
}

bool Shader::Compile()
{
	// Compile the shader
	glCompileShader(m_Id);
	glGetShaderiv(m_Id, GL_COMPILE_STATUS, &m_CompileStatus);

	LogShaderOutput(m_Id);

	return m_CompileStatus;
}
