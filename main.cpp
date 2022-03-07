#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "./vertex_buffer.h"
#include "./index_buffer.h"
#include "./shader.h"

using namespace std;

void WindowSizeCallback(GLFWwindow* window, int width, int height);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

void OpenGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum serverity, GLsizei length, const GLchar* message, const void* userParam);

bool exit_main_loop = false;
bool wire_frame_mode = false;

int main()
{			
	cout << "Data Path: " << DATA_PATH << endl;

	/////////////////////// Initialize OpenGL and GLFW ///////////////////////
	// GLFW Init
	if(!glfwInit())
	{
		cout << "GLFW cannot initialize." << endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create a window
	char window_title[100];

	sprintf(window_title, "OpenGL Demo -- Version: %s (%s)", VERSION_STRING, ARCHITECTURE_STRING);

	GLFWwindow* window = glfwCreateWindow(800, 600, window_title, NULL, NULL);
	if(!window)
	{
		cout << "GLFW Window cannot create.";
		glfwTerminate();
		return -1;
	}

	// Set Context for gl
	glfwMakeContextCurrent(window);

	// Init GLEW
	if(glewInit() != GLEW_OK)
	{
		cout << "GLEW cannot initialize." << endl;
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(OpenGLDebugCallback, 0);

	// Set Vieport and set frambuffer size callback
	glViewport(0,0,800,600);
	glfwSetFramebufferSizeCallback(window, WindowSizeCallback);

	// Output glfw version
	int major, minor, rev;
	glfwGetVersion(&major, &minor, &rev);
	cout << "GLFW Version: " << major << "." << minor << "." << rev << endl;

	// Output gl version
	cout << "GL Version: " << glGetString(GL_VERSION) << endl;

	glfwSetKeyCallback(window, KeyCallback);

	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode *mode = glfwGetVideoMode(monitor);


	// Fullscreen
	//glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

	// Window
	//glfwSetWindowMonitor(window, nullptr, 0, 0, 800, 600, 0);

	/////////////////////// Create a triangle ///////////////////////

	// Create a buffer with vertex coordinates
	Vertex vertices[] = {
		Vertex{-0.5f,  -0.5f, 0.0f,
		1.0f, 0.0f, 0.0f, 1.0f},
		Vertex{0.5f, -0.5f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f},
		Vertex{-0.5, 0.5f, 0.0f,
		0.0f, 0.0f, 1.0f, 1.0f},
		Vertex{0.5f,  0.5f, 0.0f,
		1.0f, 0.0f, 0.0f, 1.0f},
	};
	uint32_t num_vertices = 4;

	VertexBuffer vertexBuffer(vertices, num_vertices);
	vertexBuffer.Bind();

	uint32_t indices[] = {
		0,1,2,
		3,1,2
	};
	uint32_t num_indices = 6;

	IndexBuffer indexBuffer(indices, num_indices, sizeof (uint32_t));

	Shader shader(DATA_PATH"shaders/basic.vs", DATA_PATH"shaders/basic.fs");
	shader.Bind();

	glfwSwapInterval(1);

	double current_frame, last_frame, delta_time;

	while (!glfwWindowShouldClose(window) && !exit_main_loop)
	{
		current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		last_frame = current_frame;

		// cout << "Frames Per Second: "  << 1.0f / delta_time << endl;

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if(wire_frame_mode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		vertexBuffer.Bind();
		indexBuffer.Bind();
		glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);
		indexBuffer.UnBind();
		vertexBuffer.UnBind();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

void OpenGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum serverity, GLsizei length, const GLchar* message, const void *userParam)
{
	cout << "[OpenGL Debug:] " << message << endl;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	   exit_main_loop = true;

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		wire_frame_mode = true;

	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		wire_frame_mode = false;
}

void WindowSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	cout << "Resize: width=" << width << ", height=" << height << endl;
}
