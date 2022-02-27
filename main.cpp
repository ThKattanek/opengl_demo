#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

bool exit_main_loop = false;

struct Vertex {
	float x;
	float y;
	float z;
};

int main()
{			
	/////////////////////// Initialize OpenGL and GLFW ///////////////////////

	// GLFW Init
	if(!glfwInit())
	{
		cout << "GLFW cannot initialize." << endl;
		return -1;
	}

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

	// Output glfw version
	int major, minor, rev;
	glfwGetVersion(&major, &minor, &rev);
	cout << "GLFW Version: " << major << "." << minor << "." << rev << endl;

	// Output gl version
	cout << "GL Version: " << glGetString(GL_VERSION) << endl;

	glfwSetKeyCallback(window, key_callback);

	/////////////////////// Create a triangle ///////////////////////

	// Create a buffer with vertex coordinates
	Vertex vertices[] = {
		Vertex{0.0f,  0.5f, 0.0f},
		Vertex{0.5f, -0.5f, 0.0f},
		Vertex{-0.5, -0.5f, 0.0f}
	};
	uint32_t numVertices = 3;

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof (Vertex), vertices, GL_STATIC_DRAW);

	glVertexAttribIPointer(0, 3, GL_FLOAT, sizeof (Vertex), (void*) offsetof(struct Vertex,x));
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window) && !exit_main_loop)
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, numVertices);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	   exit_main_loop = true;
}
