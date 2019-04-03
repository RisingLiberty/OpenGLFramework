#include "Context.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

Context::Context()
{
	glewExperimental = true;
	glewInit();
}