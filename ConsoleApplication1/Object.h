#pragma once
#include "Texture.h"
#include "math_3d.h"
#include "Shaders.h"

class Object
{
public:
	Object();
	void Update();
	virtual void Draw(double dt, double offset = 0);
	void Init(char* vShader, char* fShader, Vertex coords[4], std::string texture);	// Maeby should return int ?

	const Vertex GetVertexByIdx(int idx) const;

	virtual ~Object();

protected:
	Shaders * m_shaders;
	Texture * m_textures;
	Vertex m_vertices[4];

	GLuint m_VBO;
	GLuint m_IBO;
	GLfloat u_time;
	GLfloat u_offset;

	static double _dtp;
};
