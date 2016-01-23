#pragma once
#include "Object.h"
#include <vector>

class ScoreObject : public Object
{
public:

	ScoreObject();

	void Init(char* vShader, char* fShader, Vertex verticies[4], std::string texture);

	virtual void Draw(double dr, double offset = 0) override;

	void IncreaseScore();

private:
	std::vector<Object* > m_digits;
	int m_value;
	bool m_isMultiDigit;
};