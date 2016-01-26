
#include "Bird_Object.h"
#include "Pipe_Object.h"
#include "texture.h"



int text = 1;

BirdObject::BirdObject()
{
}

void BirdObject::Init(char* vShader, char* fShader, Vertex verticies[4], std::string texture, std::string texture2, std::string texture3)
{
	Object::Init(vShader, fShader, verticies, texture);
	m_texture2 = new Texture(GL_TEXTURE_2D, texture2);
	m_texture2->Load();
	m_texture3 = new Texture(GL_TEXTURE_2D, texture3);
	m_texture3->Load();
	m_speed = 0.01;
	m_shouldUpBird = false;
	m_UpTime = 1.0;
	m_score = 0;
}

void BirdObject::Draw(double dt, double offset)
{
	glUseProgram(m_shaders->program);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	if (text <= 8)
	{
		m_textures->Bind(GL_TEXTURE0);
		text++;
	}
	else if (text <= 16)
	{
		m_texture2->Bind(GL_TEXTURE0);
		text++;
	}
	else if (text <= 24)
	{
		m_texture3->Bind(GL_TEXTURE0);
		text++;
	}
	else
	{
		m_texture3->Bind(GL_TEXTURE0);
		text = 1;
	}

	u_time = glGetUniformLocation(m_shaders->program, "u_time");
	glUniform1f(u_time, m_speed);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glUseProgram(0);

	if (m_shouldUpBird && m_UpTime > 0.0)
	{
		m_speed -= 0.02;
		m_UpTime -= 0.1;

		m_vertices[2].m_pos.y += 0.02;
		m_vertices[3].m_pos.y += 0.02;
	}
	else
	{
		m_UpTime = 1.0;
		m_shouldUpBird = false;
		m_speed += 0.01;

		m_vertices[2].m_pos.y -= 0.01;
		m_vertices[3].m_pos.y -= 0.01;
	}

	_dtp += 0.005;

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glUseProgram(0);
}

bool BirdObject::CheckInteractWithTube(PipeObject * ob)
{
	switch (ob->GetType())
	{
	case PipeObject::TYPE::TOP:
		if (m_vertices[2].m_pos.y >= ob->GetVertexByIdx(0).m_pos.y && m_vertices[2].m_pos.x >= ob->GetVertexByIdx(0).m_pos.x - _dtp &&
			m_vertices[1].m_pos.x <= ob->GetVertexByIdx(3).m_pos.x - _dtp
			)
			return true;
		break;
	case PipeObject::TYPE::BOTTOM:
		if (m_vertices[3].m_pos.y <= ob->GetVertexByIdx(1).m_pos.y && m_vertices[2].m_pos.x >= ob->GetVertexByIdx(0).m_pos.x - _dtp
			&&
			m_vertices[1].m_pos.x <= ob->GetVertexByIdx(3).m_pos.x - _dtp
			)
			return true;
		break;
	default:
		break;
	}

	return false;
}

bool BirdObject::ChechScore(PipeObject * ob)
{
	if (m_vertices[2].m_pos.x >= ((ob->GetVertexByIdx(0).m_pos.x + ob->GetVertexByIdx(3).m_pos.x) / 2.0 - _dtp))
	{
		m_score++;
		return true;
	}

	return false;
}

bool BirdObject::IsDead() const
{
	return m_isDead;
}

BirdObject::~BirdObject()
{
}