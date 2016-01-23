#include "ScoreObject.h"

ScoreObject::ScoreObject()
{}

void ScoreObject::Init(char* vShader, char* fShader, Vertex verticies[4], std::string texture)
{
	//Object::Init(vShader, fShader, verticies, texture);

	for (int i = 0; i < 10; i++)
	{
		Object* tmp = new Object();

		Vertex btn_start_verticies[4] = {
			Vertex(Vector3f(-0.1f, 0.7f, 0.f), Vector2f(0.0f, 0.0f)),
			Vertex(Vector3f(-0.1f, 0.9f, 0.f),      Vector2f(0.f, 1.0f)),
			Vertex(Vector3f(0.1f, 0.9f, 0.f), Vector2f(1.f, 1.0f)),
			Vertex(Vector3f(0.1f, 0.7f, 0.f), Vector2f(1.f, 0.0f))
		};
		char a[2];
		_itoa_s(i, a, 10);
		std::string q = a;
		std::string asd = "digit_" + q + ".tga";

		tmp->Init("digitShader.vs", "digitShader.fs", btn_start_verticies, asd);

		m_digits.push_back(tmp);
	}
	m_isMultiDigit = false;
	m_value = 0;
}

void ScoreObject::Draw(double dr, double offset)
{
	if (m_value < 10)
	{
		m_digits[m_value]->Draw(dr);
	}
	else if (m_value < 100)
	{
		int v1 = m_value / 10.0;
		int v2 = m_value % 10;
		m_digits[v1]->Draw(dr, -0.12);
		m_digits[v2]->Draw(dr, 0.12);
	}
	else
	{
		int v1 = m_value / 100.0;
		int v2 = (m_value % 100) / 10.0;
		int v3 = (m_value % 100) % 10;
		m_digits[v1]->Draw(dr, -0.30);
		m_digits[v2]->Draw(dr, -0.06);
		m_digits[v3]->Draw(dr, 0.18);
	}
}

void ScoreObject::IncreaseScore()
{
	m_value++;
}