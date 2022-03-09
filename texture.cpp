#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "./libs/stb_image.h"

Texture::Texture(const char *filename)
{
	LoadTexture(filename);
}

Texture::~Texture()
{

}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::LoadTexture(const char *filename)
{
	texture_width = 0;
	texture_height = 0;
	texture_bitsperpixel = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* texture_buffer = stbi_load(filename, &texture_width, &texture_height, &texture_bitsperpixel, 4);

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

	return 0;
}
