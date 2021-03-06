#include "vertex_buffer.h"

VertexBuffer::VertexBuffer(void *data, uint32_t num_vertices)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
	glBufferData(GL_ARRAY_BUFFER, num_vertices * sizeof (Vertex), data, GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof (Vertex), (void*) offsetof(struct Vertex,x));
	glEnableVertexAttribArray(0);

	// UV
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof (Vertex), (void*) offsetof(struct Vertex,u));
	glEnableVertexAttribArray(1);

	// Color
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof (Vertex), (void*) offsetof(struct Vertex,r));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1,&buffer_id);
}

void VertexBuffer::Bind()
{
	glBindVertexArray(vao);
}

void VertexBuffer::UnBind()
{
	glBindVertexArray(0);
}
