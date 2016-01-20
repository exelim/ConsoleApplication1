#pragma once
#include "Object.h"

#include <GLES2/gl2.h>
#include <EGL/egl.h>

class PipeObject;
class Texture;

class BirdObject : public Object
{
public:

	BirdObject();
	void Init(char* vShader, char* fShader, Vertex verticies[4], std::string texture, std::string texture2, std::string texture3);

	bool CheckInteractWithTube(PipeObject * ob);

	virtual void Draw(double dr) override;
	virtual ~BirdObject();

	Texture * m_texture2;
	Texture * m_texture3;
	double m_speed;
	bool m_shouldUpBird;
	double m_UpTime;
};