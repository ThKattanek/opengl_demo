#include "vertex_buffer.h"

VertexBuffer::VertexBuffer(void *data, uint32_t numVertices)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof (Vertex), data, GL_STATIC_DRAW);

	glVertexAttribIPointer(0, 3, GL_FLOAT, sizeof (Vertex), (void*) offsetof(struct Vertex,x));
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1,&bufferID);
}

void VertexBuffer::Bind()
{
	glBindVertexArray(vao);
}

void VertexBuffer::UnBind()
{
	glBindVertexArray(0);
}
