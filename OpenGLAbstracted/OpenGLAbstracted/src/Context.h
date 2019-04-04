#pragma once

#include <string>

class Context
{
public:
	Context();

	Context(const Context& other) = delete;
	Context(const Context&& other) = delete;
	Context& operator=(const Context& other) = delete;
	Context& operator=(const Context&& other) = delete;

	std::string GetVersion() const;
	std::string GetRenderer() const;
	std::string GetVendor() const;
	std::string GetShadingLanguageVersion() const;
};