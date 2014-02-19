#include "SkyBox.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void SkyBox::loadSkyBox(const char* Front, const char* Back, const char* Left, const char* Right, const char* Top, const char* Bottom)
{
	_skyboxTextures[0] = new Texture(Front);
	_skyboxTextures[1] = new Texture(Back);
	_skyboxTextures[2] = new Texture(Left);
	_skyboxTextures[3] = new Texture(Right);
	_skyboxTextures[4] = new Texture(Top);
	_skyboxTextures[5] = new Texture(Bottom);


	float vSkyBoxVertices[5*6*4] = 
	{
		// Front face	   //UV
		50.0f, 50.0f, 50.0f,0.0f, 0.0f,
		50.0f, -50.0f, 50.0f, 0.0f, 1.0f,
		-50.0f, 50.0f, 50.0f, 1.0f, 0.0f,
		-50.0f, -50.0f, 50.0f,1.0f, 1.0f,
		// Back face
		-50.0f, 50.0f, -50.0f, 0.0f, 0.0f,
		-50.0f, -50.0f, -50.0f,0.0f, 1.0f,
		50.0f, 50.0f, -50.0f, 1.0f, 0.0f,
		50.0f, -50.0f, -50.0f,1.0f, 1.0f,
		// Left face
		-50.0f, 50.0f, 50.0f, 0.0f, 0.0f,
		-50.0f, -50.0f, 50.0f, 0.0f, 1.0f,
		-50.0f, 50.0f, -50.0f, 1.0f, 0.0f,
		-50.0f, -50.0f, -50.0f,1.0f, 1.0f,
		// Right face
		50.0f, 50.0f, -50.0f,0.0f, 0.0f,
		50.0f, -50.0f, -50.0f,0.0f, 1.0f,
		50.0f, 50.0f, 50.0f, 1.0f, 0.0f,
		50.0f, -50.0f, 50.0f,1.0f, 1.0f,
		// Top face
		-50.0f, 50.0f, -50.0f, 0.0f, 0.0f,
		50.0f, 50.0f, -50.0f,0.0f, 1.0f,
		-50.0f, 50.0f, 50.0f,1.0f, 0.0f,
		50.0f, 50.0f, 50.0f,1.0f, 1.0f,
		// Bottom face
		50.0f, -50.0f, -50.0f, 0.0f, 0.0f,
		-50.0f, -50.0f, -50.0f, 0.0f, 1.0f,
		50.0f, -50.0f, 50.0f, 1.0f, 0.0f,
		-50.0f, -50.0f, 50.0f,1.0f, 1.0f,
	};

	glGenVertexArrays(1,&_VaoId);
	glBindVertexArray(_VaoId);
	
	glGenBuffers(1,&_VboId);
	glBindBuffer(GL_ARRAY_BUFFER,_VboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vSkyBoxVertices), vSkyBoxVertices,GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,5*sizeof(float), (void*)(3*sizeof(float)));
}

void SkyBox::Render()
{

	glDepthMask(0);
	glBindVertexArray(_VaoId);
	for(int i = 0; i != 6 ; ++i)
	{
		//glActiveTexture(GL_TEXTURE0);
		//program->SetUniform("texKitten", 0);
		//glBindTexture(GL_TEXTURE_2D,_skyboxTextures[i]->getId());
		_skyboxTextures[i]->BindTexture(0);
		glDrawArrays(GL_TRIANGLE_STRIP, i*4, 4);
	}

	glDepthMask(1);
}