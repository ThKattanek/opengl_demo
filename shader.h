#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include "./defines.h"

using namespace std;

class Shader
{
public:
	Shader(const char* vertex_shader_filename, const char* fragment_shader_filename);
	virtual ~Shader();

	void Bind();
	void Unbind();

private:
	GLuint Compile(string shader_source, GLenum type);
	string Parse(const char* filename);
	GLuint CreateShader(const char* vertex_shader_filename, const char* fragment_shader_filename);

	GLuint shader_id;
};

#endif // SHADER_H
