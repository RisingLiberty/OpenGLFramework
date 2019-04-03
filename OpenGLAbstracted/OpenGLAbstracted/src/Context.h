#pragma once

class Context
{
public:
	Context();

	Context(const Context& other) = delete;
	Context(const Context&& other) = delete;
	Context& operator=(const Context& other) = delete;
	Context& operator=(const Context&& other) = delete;
};