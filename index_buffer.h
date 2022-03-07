#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <GL/glew.h>

class IndexBuffer
{
public:
	IndexBuffer(void* data, uint32_t num_indices, uint8_t element_size);
	virtual ~IndexBuffer();

	void Bind();
	void UnBind();

private:
	GLuint buffer_id;
};

#endif // INDEXBUFFER_H
