#ifndef _PROGRAM_H
#define _PROGRAM_H

#include <GL\glew.h>
#include <string>
#include <fstream>
#include <vector>
#include "Shader.h"

class Program
{
public:
	Program(std::vector<GLuint> shaderIds);

	~Program();

	void use()
	{
		glUseProgram(_id);
	}

	GLuint AttribLoc(GLchar* name)
	{
		return glGetAttribLocation(_id, name);
	}

	GLuint UniformLoc(GLchar* name)
	{
		return glGetUniformLocation(_id, name);
	}

	GLuint getId()
	{
		return _id;
	}

	bool isInUse()
	{
		GLint currentProgram = 0;
		glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
		return (currentProgram == _id);
	}

	void stopUse()
	{
		glUseProgram(0);
	}

	void SetUniform(const char * name, int);
	void SetUniform(const char * name, GLfloat* mat4_value);
private:
	Program(const Program&);
	Program& operator=(const Program&);

	GLuint _id;
};
#endif //_PROGRAM_H