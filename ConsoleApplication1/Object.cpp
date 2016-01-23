
#include "Object.h"

double Object::_dtp = 0.0;

Object::Object()
	:m_textures(nullptr),
	m_shaders(nullptr)
{}

void Object::Init(char* vShader, char* fShader, Vertex verticies[4], std::string texture)
{
	m_shaders = new Shaders();
	m_shaders->Init(vShader, fShader);
	m_vertices[0] = verticies[0];
	m_vertices[1] = verticies[1];
	m_vertices[2] = verticies[2];
	m_vertices[3] = verticies[3];
	m_textures = new Texture(GL_TEXTURE_2D, texture);
	m_textures->Load();

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

	unsigned int Indices[] = { 0, 1, 2, 
							   0, 2, 3
	};
	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

void Object::Draw(double dt, double offset)
{
	glUseProgram(m_shaders->program);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	m_textures->Bind(GL_TEXTURE0);

	u_time = glGetUniformLocation(m_shaders->program, "u_time");
	glUniform1f(u_time, dt);

	u_offset = glGetUniformLocation(m_shaders->program, "u_offset");
	glUniform1f(u_offset, offset);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glUseProgram(0);
}

const Vertex Object::GetVertexByIdx(int idx) const
{
	return m_vertices[idx];
}

void Object::Update()
{

}

Object::~Object()
{
	if (m_shaders)
		delete m_shaders;

	if (m_textures)
		delete m_textures;
}