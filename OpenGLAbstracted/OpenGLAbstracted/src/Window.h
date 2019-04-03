#pragma once

#include <string>
#include <SFML/Window.hpp>
#include <memory>

enum class WindowEvent
{
	NO_EVENT,

	CLOSED
};

class Window
{
public:
	Window(const std::string& title, int width, int height, int style);

	WindowEvent EventLoop();
	void Display();
	void Close();
	
private:
	std::string m_Title;
	int m_Width;
	int m_Height;
	
	std::unique_ptr<sf::Window> m_Window;

};