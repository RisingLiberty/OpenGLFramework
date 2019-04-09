#pragma once

#include "Context.h"
#include "Window.h"
#include "GlobalTimer.h"

class OpenGLApp
{
public:
	OpenGLApp();

	int Start();

private:

	int Initialize();
	void MainLoop();

	void OutputFrameStats() const;
private:
	Window m_Window;
	Context m_Context;
	GlobalTimer m_Timer;
};