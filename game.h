#ifndef _GAME_H
#define _GAME_H

#include <GL\glew.h>
#include <SDL2\SDL.h>
#include <SDL2\SDL_opengl.h>
#include <SOIL\SOIL.h>
#include <iostream>
#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Program.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "SkyBox.h"
#include "ModelInstance.h"
#include "ModelAsset.h"
#include "Transform.h"


using namespace std;

class game
{
public:
	bool init();
	void run();
	bool loadContent();
	void eventHander(SDL_Event*);
	void onRender();
	void update();
	void clean();
private:

	GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
	void load_obj(const char* filename, vector<glm::vec4> &vertices, vector<glm::vec3> &normals, vector<GLushort> &elements);
	void loadOBJ2(const char* filename, vector<glm::vec3> &vertices,vector<glm::vec3> &NVs,vector<glm::vec2> &UVs,vector<GLuint> &elements);
	
	/*bool loadOBJ(const char * path,
	     std::vector < glm::vec3 > & out_vertices,
	     std::vector < glm::vec2 > & out_uvs,
	     std::vector < glm::vec3 > & out_normals);*/

	void loadOBJ(const char* filename, vector<glm::vec3> &vertices,vector<glm::vec3> &NVs,vector<GLuint> &elements);

	bool running;
	Uint32 time;

	vector<ModelInstance> instances;
	ModelInstance instance;

	SDL_Window* window;
	SDL_GLContext context;
	SDL_Event event;
	GLuint VaoId;
	GLuint shaderProgram;

	GLuint SkyBoxVaoId;
	GLuint SkyBoxVboId;
	GLuint SkyBoxTexture;
	//Program shadarProgram;
	Program* program;
	Shader *VertexShader;
	Shader *FragmentShader;
	Texture *texture;
	Camera camera;
	SkyBox* skybox;

	GLuint _testVaoId;
	int window_w;
	int window_h;
	vector<glm::vec3> vertices;
	vector<glm::vec3> NVs;
	vector<glm::vec2> UVs;
	vector<GLuint> elems;
	glm::vec3 viewVec;
};

#endif //_GAME_H