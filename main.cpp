#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

bool exit_main_loop = false;

int main()
{			
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

	// Output gl version number
	int major, minor, rev;
	glfwGetVersion(&major, &minor, &rev);
	cout << "OpenGL Version: " << major << "." << minor << "." << rev << endl;

	glfwSetKeyCallback(window, key_callback);


	const GLfloat vertices[] = {
		0.0f,  0.5f,
		0.5f, -0.5f,
		-0.5, -0.5f
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	const GLuint indices[] = {
		0,1,2
	};

	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (indices), indices, GL_STATIC_DRAW);

	char const* vertexShaderSrc =
			"#version 300 es\n"
			"precision mediump float;\n"
			"in vec2 position;\n"
			"void main()\n"
			"{\n"
			"	gl_Position = vec4(position, 0.0, 1.0);\n"
			"}";

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShader);

	char const* fragmentShaderSrc =
			"#version 300 es\n"
			"precision mediump float;\n"
			"out vec4 outColor;\n"
			"void main()\n"
			"{\n"
			"	outColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
			"}";

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShader);


	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	GLint positionAttribute = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(positionAttribute);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	while (!glfwWindowShouldClose(window) && !exit_main_loop)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(1, &vbo);

	glfwTerminate();

	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	   exit_main_loop = true;
}
