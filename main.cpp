#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "./vertex_buffer.h"
#include "./shader.h"

using namespace std;

void WindowSizeCallback(GLFWwindow* window, int width, int height);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

bool exit_main_loop = false;

int main()
{			
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
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
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

	/////////////////////// Create a triangle ///////////////////////

	// Create a buffer with vertex coordinates
	Vertex vertices[] = {
		Vertex{-0.5f,  -0.5f, 0.0f},
		Vertex{0.5f, -0.5f, 0.0f},
		Vertex{0.0, 0.5f, 0.0f}
	};
	uint32_t num_vertices = 3;

	VertexBuffer vertexBuffer(vertices, num_vertices);
	vertexBuffer.Bind();

	Shader shader("./shader/basic.vs", "./shader/basic.fs");
	shader.Bind();

	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(window) && !exit_main_loop)
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	   exit_main_loop = true;
}

void WindowSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	cout << "Resize: width=" << width << ", height=" << height << endl;
}
