#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

class Texture
{
public:
	Texture(const char* filename);
	virtual ~Texture();

	void Bind();
	void Unbind();

private:

	int LoadTexture(const char* filename);

	int texture_width;
	int texture_height;
	int texture_bitsperpixel;

	GLuint texture_id;
};

#endif // TEXTURE_H
