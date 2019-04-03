#include "OpenGLApp.h"

#include "RenderTarget.h"

#include <iostream>
#include <iomanip>

namespace
{
	int WIDTH = 800;
	int HEIGHT = 600;

}

OpenGLApp::OpenGLApp() :
	m_Window("OpenGL app", WIDTH, HEIGHT, sf::Style::Titlebar | sf::Style::Close),
	m_Context()
{
	m_Timer.Reset();
}

int OpenGLApp::Start()
{
	int err = this->Initialize();

	if (err != 0)
		return err;

	this->MainLoop();

	return 0;
}

int OpenGLApp::Initialize()
{
	m_Timer.Start();
	return 0;
}

void OpenGLApp::MainLoop()
{
	bool running = true;
	int timer = 1;
	while (running)
	{
		// Poll events of window
		if (m_Window.EventLoop() == WindowEvent::CLOSED)
			running = false;

		m_Timer.Tick();

		this->OutputFrameStats();


		//RenderTarget renderTarget(WIDTH, HEIGHT);

		// Swap buffers
		m_Window.Display();
	}

	m_Window.Close();
}

void OpenGLApp::OutputFrameStats() const
{
	static int frameCount = 0;
	static float timeElapsed = 0.0f;

	frameCount++;

	if ((m_Timer.GetTotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCount;
		float mspf = 1000.0f / fps;

		std::cout << std::fixed;

		std::cout << "fps: " << fps << "\n";
		std::cout << "mspf: " << mspf << "\n";

		frameCount = 0;
		timeElapsed += 1.0f;
	}
}