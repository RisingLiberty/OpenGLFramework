#include "OpenGLApp.h"

#include "RenderTarget.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "ShaderProgram.h"
#include "FileReader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "InputLayout.h"
#include "VertexArray.h"
#include "VertexAttribute.h"
#include "InputAssembler.h"
#include "Vertex.h"

#include <iostream>
#include <iomanip>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	
	std::cout << "OpenGL version: " << m_Context.GetVersion() << "\n";
	std::cout << "Renderer: " << m_Context.GetRenderer() << "\n";
	std::cout << "Vender: " << m_Context.GetVendor() << "\n";
	std::cout << "Shading language version: " << m_Context.GetShadingLanguageVersion() << "\n";

	return 0;
}

void OpenGLApp::MainLoop()
{
	bool running = true;
	int timer = 1;

	std::string vs = FileReader::ReadFile("../data/shaders/src/defaultvertexshader.glsl");
	std::string fs = FileReader::ReadFile("../data/shaders/src/defaultfragmentshader.glsl");

	// Create Vertex Array Object
	VertexBuffer va;

	GLfloat vertices[] = {
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,// Top-left
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// Top-right
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,// Bottom-right
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f// Bottom-left
	};

	VertexBuffer vb(vertices, sizeof(vertices));

	GLushort indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	IndexBuffer ib(indices, sizeof(indices), IndexBufferFormat::UINT16);

	VertexShader vertexShader(vs);
	FragmentShader fragmentShader(fs);

	ShaderProgram program;
	program.AttachShader(vertexShader.GetId());
	program.AttachShader(fragmentShader.GetId());
	program.Link();
	program.Bind();

	InputLayout inputLayout;
	inputLayout.AddAttribute(VertexAttribute("position", VertexAttributeType::VEC2));
	inputLayout.AddAttribute(VertexAttribute("color", VertexAttributeType::VEC3));
	inputLayout.AddAttribute(VertexAttribute("texcoord", VertexAttributeType::VEC2));

	size_t vertexSize = inputLayout.GetSize();
	const std::vector<VertexAttribute> attributes = inputLayout.GetAttributes();

	GLint count;
	glGetProgramiv(program.GetId(), GL_ACTIVE_ATTRIBUTES, &count);

	GLint size; // size of the variable
	GLenum type; // type of the variable (float, vec3 or mat4, etc)

	const GLsizei bufSize = 16; // maximum name length
	GLchar name[bufSize]; // variable name in GLSL
	GLsizei length; // name length

	for (int i = 0; i < count; ++i)
	{
		glGetActiveAttrib(program.GetId(), i, bufSize, &length, &size, &type, name);
		std::cout << "attribute: " << i << " type: " << type << " name: " << name << std::endl;
	}

	size_t offset = 0;
	for (VertexAttribute attribute : attributes)
	{
		program.SpecifyAttribute(attribute, vertexSize, offset);
		offset += attribute.GetSize();
	}

	InputAssembler ia;
	ia.VertexBuffer = &vb;
	ia.IndexBuffer = &ib;
	ia.Topology = PrimitiveTopology::TRIANGLE_LIST;
	ia.InputLayout = inputLayout;

	while (running)
	{
		// Poll events of window
		if (m_Window.EventLoop() == WindowEvent::CLOSED)
			running = false;

		m_Timer.Tick();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// this->OutputFrameStats();

		//program.Bind();

		glDrawElements(ia.ToOpenGLTopology(), ib.GetCount(), ib.ToOpenGLFormat(), 0);

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