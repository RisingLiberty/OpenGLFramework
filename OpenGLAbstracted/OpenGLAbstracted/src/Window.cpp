#include "Window.h"

Window::Window(const std::string& title, int width, int height, int style):
	m_Title(title),
	m_Width(width),
	m_Height(height)
{
	sf::ContextSettings settings;

	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.majorVersion = 3;
	settings.minorVersion = 2;

	m_Window = std::make_unique<sf::Window>(sf::VideoMode(width, height, 32), title, style, settings);
}

WindowEvent Window::EventLoop()
{
	sf::Event event;
	while (m_Window->pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				return WindowEvent::CLOSED;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					return WindowEvent::CLOSED;
		}
	}

	return WindowEvent::NO_EVENT;
}

void Window::Display()
{
	m_Window->display();
}

void Window::Close()
{
	m_Window->close();
}