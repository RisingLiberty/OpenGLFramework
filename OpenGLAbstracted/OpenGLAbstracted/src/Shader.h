#pragma once

#include <string>

class Shader
{
public:
	Shader(const std::string& source);
	~Shader();

	unsigned int GetId() const;
	const std::string& GetSource() const;
	bool IsMarkedForDeletion() const;
protected:
	bool Compile();

protected:
	unsigned int m_Id;
	std::string m_Source;
	int m_CompileStatus;
};