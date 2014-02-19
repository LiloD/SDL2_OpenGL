#include "ModelAsset.h"

void ModelAsset::LoadVertexData()
{
	GLfloat vertexData[] = {
		//  X     Y     Z       U     V
		// bottom
		-1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
		1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
		-1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
		1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
		1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,   0.0f, 1.0f,

		// top
		-1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
		-1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
		1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
		1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
		-1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,   1.0f, 1.0f,

		// front
		-1.0f,-1.0f, 1.0f,   1.0f, 0.0f,
		1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
		-1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,   1.0f, 1.0f,

		// back
		-1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
		-1.0f, 1.0f,-1.0f,   0.0f, 1.0f,
		1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
		1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
		-1.0f, 1.0f,-1.0f,   0.0f, 1.0f,
		1.0f, 1.0f,-1.0f,   1.0f, 1.0f,

		// left
		-1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
		-1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
		-1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,   1.0f, 0.0f,

		// right
		1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
		1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
		1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,   0.0f, 1.0f
	};

	glGenVertexArrays(1,&_vaoId);
	glBindVertexArray(_vaoId);

	/*glGenBuffers(1,&_vboId);
	glBindBuffer(GL_ARRAY_BUFFER,_vboId);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertexData),vertexData,GL_STATIC_DRAW);*/

	_vbo = new VertexBufferObject();
	_vbo->CreateVBO();
	_vbo->addData(vertexData,sizeof(vertexData));
	_vbo->bindVBO(GL_ARRAY_BUFFER);
	_vbo->uploadDataToGPU(GL_STATIC_DRAW);
	
	// connect the xyz to the "vert" attribute of the vertex shader
	glEnableVertexAttribArray(_program->AttribLoc("in_position"));
	int i = _program->AttribLoc("in_position");
	glVertexAttribPointer(_program->AttribLoc("in_position"), 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void *)(0));

	 //connect the uv coords to the "vertTexCoord" attribute of the vertex shader
	glEnableVertexAttribArray(_program->AttribLoc("texcoord"));
	i = _program->AttribLoc("texcoord");
	glVertexAttribPointer(_program->AttribLoc("texcoord"), 2, GL_FLOAT, GL_TRUE,  5*sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		
	_drawStart = 0;
	_drawCount = 6*2*3;

	glBindVertexArray(0);
}

void ModelAsset::LoadTexture()
{
	_texture = new Texture("resource/wooden-crate.jpg");
}