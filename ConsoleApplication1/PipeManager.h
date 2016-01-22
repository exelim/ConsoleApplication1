#pragma once
#include<vector>
#include "math_3d.h"

class PipeObject;
class BirdObject;

class PipeManager
{
public:
	PipeManager();
	~PipeManager();

	std::vector<PipeObject*> GetPipes() const;

	void AddPipe();
	void DeletePipes();
	void DrawPipes(double dt);
	bool CheckCollisionWithBird(BirdObject& bird);
	bool CheckScore(BirdObject& bird);

private:

	int m_pipesCount;
	std::vector<PipeObject*> m_pipes;

	Vertex initial_top_position[4] = {
		Vertex(Vector3f(0.f, 0.3f, 0.f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(0.f, 1.0f, 0.f),      Vector2f(0.f, 1.0f)),
		Vertex(Vector3f(0.2f, 1.f, 0.f), Vector2f(1.f, 1.0f)),
		Vertex(Vector3f(0.2f, 0.3f, 0.f), Vector2f(1.f, 0.0f))
	};

	Vertex initial_bot_position[4] = {
		Vertex(Vector3f(0.f, -1.f, 0.f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(0.f, 0.0f, 0.f),      Vector2f(0.f, 1.0f)),
		Vertex(Vector3f(0.2f, 0.0f, 0.f), Vector2f(1.f, 1.0f)),
		Vertex(Vector3f(0.2f, -1.f, 0.f), Vector2f(1.f, 0.0f))
	};
};