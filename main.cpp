#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "./libs/stb_image.h"

#include "./vertex_buffer.h"
#include "./index_buffer.h"
#include "./shader.h"

using namespace std;
using namespace glm;

void WindowSizeCallback(GLFWwindow* window, int width, int height);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

void APIENTRY OpenGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum serverity, GLsizei length, const GLchar* message, const void* userParam);

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

	// Set OpenGL Debug Callback
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
	// glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

	// Window
	// glfwSetWindowMonitor(window, nullptr, 0, 0, 800, 600, 0);

	/////////////////////// Create a rectangle ///////////////////////

	// Load texture with stb_image
	int texture_width = 0;
	int texture_height = 0;
	int texture_bitsperpixel = 0;

	stbi_set_flip_vertically_on_load(true);
	auto texture_buffer = stbi_load(DATA_PATH"graphics/logo.png", &texture_width, &texture_height, &texture_bitsperpixel, 4);

	GLuint texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_buffer);

	glBindTexture(GL_TEXTURE_2D, 0);

	if(texture_buffer)
	{
		stbi_image_free(texture_buffer);
	}

	// Create a buffer with vertex coordinates
	Vertex vertices[] = {
		Vertex{-0.5f,  -0.5f, 0.0f,
		0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 1.0f},
		Vertex{0.5f, -0.5f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f},
		Vertex{-0.5, 0.5f, 0.0f,
		0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f},
		Vertex{0.5f, 0.5f, 0.0f,
		1.0f, 1.0f,
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

	int texture_uniform_location = glGetUniformLocation(shader.GetId(), "u_texture");
	glUniform1i(texture_uniform_location, 0);


	mat4 model_matrix = mat4(1.0f);
	int model_matrix_uniform_location = glGetUniformLocation(shader.GetId(), "u_model_matrix");

	// Scale
	model_matrix = scale(model_matrix, vec3(1.2f,1.5f,1.5f));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSwapInterval(1);

	double current_frame, last_frame, delta_time;

	while (!glfwWindowShouldClose(window) && !exit_main_loop)
	{
		current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		last_frame = current_frame;

		// cout << "Frames Per Second: "  << 1.0f / delta_time << endl;

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if(wire_frame_mode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		vertexBuffer.Bind();
		indexBuffer.Bind();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_id);

		// Rotation
		model_matrix = glm::rotate(model_matrix, float(5.0f * delta_time), glm::vec3(0,0,1));

		glUniformMatrix4fv(model_matrix_uniform_location, 1, GL_FALSE, &model_matrix[0][0]);

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
