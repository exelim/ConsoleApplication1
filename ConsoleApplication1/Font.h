#pragma once
#ifndef FONT_H
#define FONT_H

#include <string>

#include <GLES2/gl2.h>
#include <EGL/egl.h>

class Font
{
public:
	Font();
	~Font();

	bool Init(std::string fontname);

	void DrawString(int x, int y, char* str, ...);

private:
	GLint m_base;
	GLfloat glyfs[256];

};

#endif