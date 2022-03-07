#include "index_buffer.h"

IndexBuffer::IndexBuffer(void *data, uint32_t num_indices, uint8_t element_size)
{
	glGenBuffers(1, &buffer_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * element_size, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &buffer_id);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
}

void IndexBuffer::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
