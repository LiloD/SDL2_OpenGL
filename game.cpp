#include "game.h"

#define FRONT "resource/jajlands1_ft.jpg"
#define BACK "resource/jajlands1_bk.jpg"
#define TOP "resource/jajlands1_up.jpg"
#define BOTTOM "resource/jajlands1_dn.jpg"
#define LEFT "resource/jajlands1_lf.jpg"
#define RIGHT "resource/jajlands1_rt.jpg"


void game::clean()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}


void game::eventHander(SDL_Event* event)
{
	if(event->type == SDL_QUIT)
	{
		running = false;
	}

	if(event->type == SDL_MOUSEMOTION)
	{
		int mouse_x,mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);
		SDL_WarpMouseInWindow(window,window_w/2, window_h/2);

		camera.setHorizontalAngle(camera.getHorizontalAngle()+float(window_w/2-mouse_x)*0.005f);
		camera.setVerticalAngle(camera.getVerticalAngle()+float(window_h/2-mouse_y)*0.005f);
	
	}

	if(event->type == SDL_KEYDOWN)
	{

		if(event->key.keysym.sym == SDLK_a)
		{
			camera.setPosition(camera.getPosition()+(-camera.right())*0.1f);
		}
		if(event->key.keysym.sym == SDLK_d)
		{
			camera.setPosition(camera.getPosition()+(camera.right())*0.1f);
		}
		if(event->key.keysym.sym == SDLK_w)
		{
			camera.setPosition(camera.getPosition()+(camera.forward())*0.1f);
		}
		if(event->key.keysym.sym == SDLK_s)
		{
			camera.setPosition(camera.getPosition()+(-camera.forward())*0.1f);
		}
	}
}


bool game::init()
{
	window_w = 800;
	window_h = 600;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Textured Rotating Cube",100,100,window_w,window_h,SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
	
	SDL_ShowCursor(0);
	
	if(window == NULL)
	{
		cout<<"Can't create window "<<SDL_GetError()<<endl;
		return false;
	}
	context = SDL_GL_CreateContext(window);
	// Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum rec = glewInit();
	
	if(rec != GLEW_OK)
	{
		cout<<"Can't initialize glew "<<endl;
		return false;
	}

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	running = true;
	return true;
}


bool game::loadContent()
{

	VertexShader = new Shader("shaders/vshader.txt",GL_VERTEX_SHADER);
	FragmentShader = new Shader("shaders/fshader.txt",GL_FRAGMENT_SHADER);
	vector<GLuint> ShaderIds;
	ShaderIds.push_back(VertexShader->getId());
	ShaderIds.push_back(FragmentShader->getId());
	program = new Program(ShaderIds);
	program->use();
	
	skybox = new SkyBox();
	skybox->loadSkyBox(FRONT,BACK,LEFT,RIGHT,TOP,BOTTOM);

	ModelAsset* ma = new ModelAsset();
	ma->LoadShaders(program);
	ma->LoadVertexData();
	ma->LoadTexture();

	ModelInstance instance1;

	instance1.setAsset(ma);
	instance1.setTrans(Transform::scale(1.0f,2.0f,1.0f));
	instances.push_back(instance1);

	ModelInstance instance2;

	instance2.setAsset(ma);
	instance2.setTrans(Transform::translate(0.0f,4.0f,0.0f));
	instances.push_back(instance2);
	
	
	program->use();
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view;
	view = camera.ViewMatrix();
	glm::mat4 proj;
	proj = glm::perspective(45.0f,800.0f/600.0f,0.1f,100.0f);

	program->SetUniform("model", glm::value_ptr(model));
	program->SetUniform("proj", glm::value_ptr(proj));
	program->SetUniform("view", glm::value_ptr(view));


	//skybox = new SkyBox();
	//skybox->loadSkyBox(FRONT,BACK,LEFT,RIGHT,TOP,BOTTOM);

	return true;
}


void game::onRender()
{
	// Clear the screen to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//glBindVertexArray(_testVaoId);
	//glDrawArrays(GL_QUADS,0,4);

	//instance.render();
	for(int i = 0; i!=instances.size();++i)
	{
		glm::mat4 model = instances[i].getTrans();
		program->SetUniform("model", glm::value_ptr(model));
		instances[i].render();
	}

	skybox->Render();

	//glBindVertexArray(VaoId);
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture->getId());
	//program->SetUniform("texKitten", 0);
	//glDrawArrays(GL_TRIANGLES, 0, 6*2*3);

	SDL_GL_SwapWindow(window);
}


void game::run()
{
	init();
	loadContent();

	while(running)
	{
		time = SDL_GetTicks();
		while(SDL_PollEvent(&event))
		{
			eventHander(&event);
		}
		update();
		onRender();

		time = SDL_GetTicks() - time;
		if(time<1000/60)
		{
			SDL_Delay(1000/60 - time);
		}
	}
	clean();
}

void game::update()
{
	//glm::mat4 trans;
	//trans = glm::rotate(trans,(float)clock()/(float)CLOCKS_PER_SEC*180.0f,glm::vec3(0.0f,1.0f,0.0f));
	//glUniformMatrix4fv(shaderProgram->UniformLoc("model"),1,GL_FALSE,glm::value_ptr(trans));


	//trans = glm::rotate(trans,(float)clock()/(float)CLOCKS_PER_SEC*180.0f,glm::vec3(0.0f,1.0f,0.0f));
	//glm::mat4 view = glm::lookAt(glm::vec3(3.0f,3.0f,3.0f), viewVec, glm::vec3(0.0f,1.0f,0.0f));
	//glUniformMatrix4fv(shaderProgram->UniformLoc("view"),1,GL_FALSE,glm::value_ptr(view));

	glm::mat4 view;
	view = camera.ViewMatrix();
	program->SetUniform("view", glm::value_ptr(view));
}