#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <GL\glew.h>

class Texture
{
public:
	//glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,texture_w,texture_h,0,GL_RGB,GL_UNSIGNED_BYTE,data);
	Texture(GLvoid* src, int width, int height, GLint minMagFilter, GLint wrapMode);

	Texture(const char * filename);

	void BindTexture(int textureUnit);

	~Texture()
	{
		glDeleteTextures(1,&_id);
	}

	GLuint getId()
	{
		return _id;
	}

	int getWidth()
	{
		return _w;
	}

	int getHeight()
	{
		return _h;
	}
private:
	GLuint _id;
	int _w;
	int _h;
	Texture(Texture&);
	Texture& operator=(Texture&);
};

#endif