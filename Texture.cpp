#include "Texture.h"
#include <SOIL\SOIL.h>

Texture::Texture(GLvoid* src, int width, int height, GLint minMagFilter, GLint wrapMode)
{
	glGenTextures(1,&_id);
	glBindTexture(GL_TEXTURE_2D, _id);
	//set parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	//Bind data
	glTexImage2D(GL_TEXTURE_2D,0 , GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, src);
	//Unbind
	glBindTexture(GL_TEXTURE_2D, 0);
	_w = width;
	_h = height;
}

Texture::Texture(const char * filename)
{
	const unsigned char * data = SOIL_load_image(filename, &_w, &_h,0, SOIL_LOAD_RGB);
	glGenTextures(1,&_id);
	glBindTexture(GL_TEXTURE_2D, _id);
	//Bind data
	glTexImage2D(GL_TEXTURE_2D,0 , GL_RGB, _w, _h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	//set parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//Unbind
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::BindTexture(int textureUnit)
{
	glActiveTexture(GL_TEXTURE0+textureUnit);
	glBindTexture(GL_TEXTURE_2D, _id);
}