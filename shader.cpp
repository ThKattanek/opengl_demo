#include "shader.h"
#include <iostream>
#include <fstream>

Shader::Shader(const char *vertex_shader_filename, const char *fragment_shader_filename)
{
	shader_id = CreateShader(vertex_shader_filename, fragment_shader_filename);
}

Shader::~Shader()
{
	glDeleteProgram(shader_id);
}

GLuint Shader::GetId()
{
	return shader_id;
}

void Shader::Bind()
{
	glUseProgram(shader_id);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

GLuint Shader::Compile(string shader_source, GLenum type)
{
	GLuint id = glCreateShader(type);
	const char* src  = shader_source.c_str();
	glShaderSource(id, 1, &src, 0);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if(result != GL_TRUE)
	{
		int length = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);
		cout << "Shader compile error: " << message << endl;
		delete [] message;
		return 0;
	}
	return id;
}

string Shader::Parse(const char *filename)
{
	FILE* file;
	file = fopen(filename, "rb");
	if(file == nullptr)
	{
		cout << "File " << filename << " not found" << endl;
		return "";
	}

	string contents;
	fseek(file, 0, SEEK_END);
	size_t filesize = ftell(file);
	fseek(file, 0, SEEK_SET);
	contents.resize(filesize);

	fread(&contents[0], 1, filesize, file);
	fclose(file);

	return contents;
}

GLuint Shader::CreateShader(const char *vertex_shader_filename, const char *fragment_shader_filename)
{
	string vertex_shader_src = Parse(vertex_shader_filename);
	string fragment_shader_src = Parse(fragment_shader_filename);

	GLuint program = glCreateProgram();
	GLuint vs = Compile(vertex_shader_src, GL_VERTEX_SHADER);
	GLuint fs = Compile(fragment_shader_src, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	/*
	glDetachShader(program, vs);
	glDetachShader(program, fs);

	glDeleteShader(vs);
	glDeleteShader(fs);
	*/

	return program;
}
