#ifndef _SKYBOX_H
#define _SKYBOX_H

#include <GL\glew.h>
#include "Texture.h"


class SkyBox
{
public:
	void loadSkyBox(const char* Front, const char* Back, const char* Left, const char* Right, const char* Top, const char* Bottom);

	void Render();

	~SkyBox()
	{
		glDeleteVertexArrays(1,&_VaoId);
		glDeleteBuffers(1,&_VboId);
		delete[] _skyboxTextures;
	}


	GLuint getVaoId()
	{
		return _VaoId;
	}

	Texture* getTextures(int i)
	{
		return _skyboxTextures[i];
	}

private:
	GLuint _VaoId;
	GLuint _VboId;
	Texture* _skyboxTextures[6];
};


#endif //_SKYBOX_H