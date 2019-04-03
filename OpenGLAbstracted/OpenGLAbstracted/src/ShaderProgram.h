#pragma once

#include <string>
#include <list>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();
	void Link();
	void Bind();
	void UnBind();
	void AttachShader(unsigned int shaderId);
	void Detachshader(unsigned int shaderId);
	void BindFragDataLocation(unsigned int colorNumber, const std::string& name);

	unsigned int GetUniformLocation(const std::string& name);
	
	template<typename T>
	void SetUniform(const std::string& name, const T& value)
	{
		static_assert(false, "");
	}

	template<>
	void SetUniform<unsigned int>(const std::string& name, const unsigned int& value)
	{
		glUniform1ui(GetUniformLocation(name), value);
	}

	template<>
	void SetUniform<int>(const std::string& name, const int& value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	template<>
	void SetUniform<float>(const std::string& name, const float& value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	template<>
	void SetUniform<glm::vec2>(const std::string& name, const glm::vec2& value)
	{
		glUniform2f(GetUniformLocation(name), value.x, value.y);
	}

	template<>
	void SetUniform<glm::vec3>(const std::string& name, const glm::vec3& value)
	{
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
	}

	template<>
	void SetUniform<glm::vec4>(const std::string& name, const glm::vec4& value)
	{
		glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	template<>
	void SetUniform<glm::mat3>(const std::string& name, const glm::mat3& value)
	{
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	template<>
	void SetUniform<glm::mat4>(const std::string& name, const glm::mat4& value)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

private:
	unsigned int m_Id;
	std::list<unsigned int> m_AttachedShaders;
};