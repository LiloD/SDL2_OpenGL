#ifndef _MODELASSET_H
#define _MODELASSET_H
#include "Texture.h"
#include "Program.h"
#include "VertexBufferObject.h"
#include <cstddef>

class ModelAsset
{
public:
	ModelAsset(Program* programPtr = NULL, Texture* texturePtr = NULL,  GLuint vao = 0, VertexBufferObject* vbo = NULL, 
				GLenum type = GL_TRIANGLES, GLint start = 0, GLint count = 0) :
		_program(programPtr),
		_texture(texturePtr),
		_vaoId(vao),
		_vbo(vbo),
		_drawType(type),
		_drawStart(start),
		_drawCount(count)
	{}

	void LoadVertexData();

	void LoadTexture();

	void LoadShaders(Program* programPtr)
	{
		_program = programPtr;
	}

	Program* _program;
	Texture* _texture;
	GLuint _vaoId;
	
	//GLuint _vboId;
	VertexBufferObject* _vbo;
	
	GLenum _drawType;
	GLint _drawStart;
	GLint _drawCount;
};

#endif //_MODELASSET_H