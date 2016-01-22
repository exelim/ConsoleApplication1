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

		tmp->Init("BgShader.vs", "BgShader.fs", btn_start_verticies, asd);

		m_digits.push_back(tmp);
	}
	m_isMultiDigit = false;
	m_value = 0;
}

void ScoreObject::Draw(double dr)
{
	if (m_value < 10)
	{
		m_digits[m_value]->Draw(dr);
	}
	else
	{

	}
}

void ScoreObject::IncreaseScore()
{
	m_value++;
}