#pragma once
#include "Object.h"

class PipeObject : public Object
{
public:
	enum class TYPE { NONE, TOP, BOTTOM };

	PipeObject();
	void Init(char* vShader, char* fShader, Vertex verticies[4], std::string texture, TYPE _type);

	bool ShouldBeDeleted();

	TYPE GetType() const;
	bool IsScored() const;
	void SetIsScored(bool value);

	virtual void Draw(double dr, double offset = 0) override;
	virtual ~PipeObject();

private:
	TYPE m_type;
	bool m_isScored;
};