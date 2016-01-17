#pragma once
#include <GL/glew.h>

class Shaders
{
public:
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint positionAttribute;
	GLuint colorAttribute;

	int m_ID;

	int Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();

	GLuint  esLoadShader(GLenum type, char * filename);
	GLuint  esLoadProgram(GLuint vertexShader, GLuint fragmentShader);
};