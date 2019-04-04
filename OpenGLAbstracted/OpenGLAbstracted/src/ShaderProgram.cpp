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
	if (m_Uniforms.find(name) != m_Uniforms.cend())
		return m_Uniforms[name].GetLocation();

	unsigned int loc = glGetUniformLocation(m_Id, name.c_str());

	if (loc == -1)
		std::cout << "warning in shader with id "<< m_Id << "\nUniform with name " << name << " has -1 as location\n";
	else
		this->StoreUniform(loc, name);


	return loc;
}

void ShaderProgram::StoreUniform(int location, const std::string& name)
{
	UniformType type = this->GetUniformType(location);
	m_Uniforms[name] = Uniform(location, name, type);
}

UniformType ShaderProgram::GetUniformType(int location)
{
	GLint size;
	GLenum glType;
	const GLsizei sizeOfName = 16;
	GLchar name[sizeOfName];
	GLsizei nameLength;

	glGetActiveUniform(m_Id, location, sizeOfName, &nameLength, &size, &glType, name);
	switch (glType)
	{
	case GL_BOOL:			return UniformType::BOOL;
	case GL_BYTE:			return UniformType::BYTE;
	case GL_UNSIGNED_BYTE:	return UniformType::UNSIGNED_BYTE;
	case GL_INT:			return UniformType::INT; break;
	case GL_UNSIGNED_INT:	return UniformType::UNSIGNED_INT; break;
	case GL_FLOAT:			return UniformType::FLOAT; break;
	case GL_DOUBLE:			return UniformType::DOUBLE; break;
	case GL_FLOAT_VEC2:		return UniformType::VEC2; break;
	case GL_FLOAT_VEC3:		return UniformType::VEC3; break;
	case GL_FLOAT_VEC4:		return UniformType::VEC4; break;
	case GL_FLOAT_MAT3:		return UniformType::MAT3; break;
	case GL_FLOAT_MAT4:		return UniformType::MAT4; break;
	}
}