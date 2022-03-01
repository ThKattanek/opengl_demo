#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <GL/glew.h>

#include "./defines.h"

class VertexBuffer
{
public:
	VertexBuffer(void* data, uint32_t num_vertices);
	virtual ~VertexBuffer();

	void Bind();
	void UnBind();

private:
	GLuint buffer_id;
	GLuint vao;
};

#endif // VERTEXBUFFER_H
