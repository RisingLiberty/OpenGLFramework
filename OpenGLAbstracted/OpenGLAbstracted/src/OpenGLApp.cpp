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
#include "RenderBuffer.h"

#include <iostream>
#include <iomanip>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace
{
	int WIDTH = 800;
	int HEIGHT = 600;

	float quadVertices[] =
	{
		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f,  0.0f, 0.0f
	};

	float cubeVertices[] = {
		// 	Position	    		   Color			  UV
		//bottom
	-0.5f,  0.5f, -0.5f,	 0.0f, 0.0f, 0.0f,	 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,	 0.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,	 0.0f, 0.0f, 0.0f,	 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	 0.0f, 0.0f, 0.0f,	 1.0f, 1.0f,

	//top
	-0.5f,  0.5f,  0.5f,	 0.0f, 0.0f, 0.0f,	 1.0f, 0.0f, //red corner
	 0.5f,  0.5f,  0.5f,	 0.0f, 0.0f, 0.0f,	 0.0f, 0.0f, //middle
	 0.5f, -0.5f,  0.5f,	 0.0f, 0.0f, 0.0f,	 0.0f, 1.0f, //blue corner
	-0.5f, -0.5f,  0.5f,	 0.0f, 0.0f, 0.0f,	 1.0f, 1.0f, //middle

	//Left
	-0.5f, -0.5f, -0.5f,	 0.0f, 0.0f, 0.0f,	 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,	 0.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,	 0.0f, 0.0f, 0.0f,	 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,	 0.0f, 0.0f, 0.0f,	 1.0f, 1.0f,

	//right						
	 0.5f, -0.5f,  0.5f,	 0.0f, 0.0f, 0.0f,	 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,	 0.0f, 0.0f, 0.0f,	 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,	 0.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,	 0.0f, 0.0f, 0.0f,	 1.0f, 0.0f,

	 //back
	 -0.5f, -0.5f,  0.5f,	 0.0f, 0.0f, 0.0f,	 1.0f, 1.0f,
	  0.5f, -0.5f,  0.5f,	 0.0f, 0.0f, 0.0f,	 0.0f, 1.0f,
	  0.5f, -0.5f, -0.5f,	 0.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
	 -0.5f, -0.5f, -0.5f,	 0.0f, 0.0f, 0.0f,	 1.0f, 0.0f,

	 //front					 
	 -0.5f,  0.5f, -0.5f,	 0.0f, 0.0f, 0.0f,	 1.0f, 0.0f,
	  0.5f,  0.5f, -0.5f,	 0.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
	  0.5f,  0.5f,  0.5f,	 0.0f, 0.0f, 0.0f,	 0.0f, 1.0f,
	 -0.5f,  0.5f,  0.5f,	 0.0f, 0.0f, 0.0f,	 1.0f, 1.0f
	};

	GLuint cubeIndices[]
	{
		// Bottom
		0,1,2,
		2,3,0,

		// Top
		4,5,6,
		6,7,4,

		// Left
		8,9,10,
		10,11,8,

		// Right
		12,13,14,
		14,15,12,

		// Front
		16,17,18,
		18,19,16,

		// Back
		20,21,22,
		22,23,20
	};

	GLuint Quadindices[]
	{
		0,1,2,
		2,3,0
	};
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
	auto t_start = std::chrono::high_resolution_clock::now();

	VertexArray vaoCube, vaoQuad;

	VertexBuffer vboCube(cubeVertices, sizeof(cubeVertices));
	VertexBuffer vboQuad(quadVertices, sizeof(quadVertices));

	IndexBuffer iboCube(cubeIndices, sizeof(cubeIndices), IndexBufferFormat::UINT32);
	IndexBuffer iboQuad(Quadindices, sizeof(Quadindices), IndexBufferFormat::UINT32);

	// Create shader programs
	GLuint sceneVertexShader, sceneFragmentShader, sceneShaderProgram;

	VertexShader vs(FileReader::ReadFile("../data/shaders/src/defaultvertextextureshader.glsl"));
	FragmentShader fs(FileReader::ReadFile("../data/shaders/src/defaultfragmenttextureshader.glsl"));

	ShaderProgram program;
	program.AttachShader(vs.GetId());
	program.AttachShader(fs.GetId());
	program.Link();

	sceneVertexShader = vs.GetId();
	sceneFragmentShader = fs.GetId();
	sceneShaderProgram = program.GetId();

	GLuint screenVertexShader, screenFragmentShader, screenShaderProgram;

	VertexShader screenVs(FileReader::ReadFile("../data/shaders/src/defaultscreenvertexshader.glsl"));
	FragmentShader screenFs(FileReader::ReadFile("../data/shaders/src/defaultscreenfragmentshader.glsl"));

	ShaderProgram screenProgram;
	screenProgram.AttachShader(screenVs.GetId());
	screenProgram.AttachShader(screenFs.GetId());
	screenProgram.Link();
	
	screenVertexShader = screenVs.GetId();
	screenFragmentShader = screenFs.GetId();
	screenShaderProgram = screenProgram.GetId();

	// Specify the layout of the vertex data
	vaoCube.Bind();
	vboCube.Bind();
	iboCube.Bind();
	
	program.SpecifyAttribute(VertexAttribute("position", VertexAttributeType::VEC3), 8 * sizeof(float), 0);
	program.SpecifyAttribute(VertexAttribute("color", VertexAttributeType::VEC3), 8 * sizeof(float), 3 * sizeof(float));
	program.SpecifyAttribute(VertexAttribute("texcoord", VertexAttributeType::VEC2), 8 * sizeof(float), 6 * sizeof(float));
	
	vaoQuad.Bind();
	vboQuad.Bind();
	iboQuad.Bind();

	screenProgram.SpecifyAttribute(VertexAttribute("position", VertexAttributeType::VEC2), 4 * sizeof(float), 0);
	screenProgram.SpecifyAttribute(VertexAttribute("texcoord", VertexAttributeType::VEC2), 4 * sizeof(float), 2 * sizeof(float));

	// Load textures
	Texture texHalo("../Data/Textures/HaloInfinite.png");
	Texture texGoogle("../Data/Textures/img.png");

	program.Bind();
	program.SetUniform("texHalo", 0);
	program.SetUniform("texGoogle", 1);

	glm::mat4 view = glm::lookAt(glm::vec3(0, 3, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 1.0f, 10.0f);

	program.SetUniform("view", view);
	program.SetUniform("proj", proj);

	screenProgram.Bind();
	screenProgram.SetUniform("texFramebuffer", 0);

	GLint uniModel = program.GetUniformLocation("model");

	RenderTarget renderTarget(WIDTH, HEIGHT);

	bool running = true;

	//glPolygonMode(GL_FRONT, GL_LINE);
	//glPolygonMode(GL_BACK, GL_LINE);

	while (running)
	{
		if (m_Window.EventLoop() == WindowEvent::CLOSED)
			running = false;

		glEnable(GL_DEPTH_TEST);
		
		renderTarget.Bind();
		
		vaoCube.Bind();
		program.Bind();

		texHalo.Activate(0);
		texHalo.Bind();

		texGoogle.Activate(1);
		texGoogle.Bind();

		//Clear the screen to white
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Calculate transformation
		// The values of uniforms are changed with any of the glUnifromXY functions, where X is the number of
		// components and Y is the type. Common types are f(float), d(double) and i(integer)
		auto t_now = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

		glm::mat4 model = glm::rotate(glm::mat4(1.0f), time * 0.5f * glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::mat4(1.0f);
		program.SetUniform("model", model);

		// draw regular cube
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		renderTarget.Unbind();
		
		vaoQuad.Bind();
		glDisable(GL_DEPTH_TEST);
		screenProgram.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Swap buffers
		m_Window.Display();
	}
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