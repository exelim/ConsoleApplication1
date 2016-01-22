
#include "Pipe_Object.h"

PipeObject::PipeObject()
{
}

void PipeObject::Init(char* vShader, char* fShader, Vertex verticies[4], std::string texture, TYPE _type)
{
	Object::Init(vShader, fShader, verticies, texture);
	m_type = _type;
	m_isScored = false;
}

void PipeObject::Draw(double dt)
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

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

bool PipeObject::ShouldBeDeleted()
{
	if (m_vertices[3].m_pos.x - _dtp < -1.0)
		return true;

	return false;
}

bool PipeObject::IsScored() const
{
	return m_isScored;
}

void PipeObject::SetIsScored(bool value)
{
	m_isScored = value;
}

PipeObject::TYPE PipeObject::GetType() const
{
	return m_type;
}

PipeObject::~PipeObject()
{

}