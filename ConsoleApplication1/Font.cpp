#include "Font.h"

Font::Font()
{}

Font::~Font()
{
	glDeleteLists(m_base, 256);
}

bool Font::Init(std::string fontname)
{
	std::string mes("Generated Font  ");
	mes += fontname.c_str();
	m_engine->GetConsole()->Print(mes);

	m_base = glGenLists(256);
	m_font = CreateFont(
		-12
		, 0
		, 0
		, 0
		, FW_NORMAL
		, FALSE
		, FALSE
		, FALSE
		, ANSI_CHARSET
		, OUT_TT_PRECIS
		, CLIP_DEFAULT_PRECIS
		, ANTIALIASED_QUALITY
		, FF_DONTCARE | DEFAULT_PITCH
		, LPCSTR(fontname.c_str())
		);
	SelectObject(m_engine->m_hDC, m_font);

	wglUseFontOutlines(
		m_engine->m_hDC
		, 0
		, 255
		, m_base
		, 0.0f
		, 0.0f
		, WGL_FONT_POLYGONS
		, glyfs
		);


	return true;
}

void Font::DrawString(int x, int y, char* str, ...)
{
	m_engine->SetGUIWindow();
	double kx = 1.344827;
	char buf[1024];
	va_list msg;

	float vPort[4];
	glGetFloatv(GL_VIEWPORT, vPort);

	float stepX = kx*10.0f / vPort[2];
	float actualX = (float(x)* stepX) - (stepX * vPort[2] / 2);


	float stepY = 10.0f / vPort[3];
	float actualY = (stepY * vPort[3] / 2) - (float(y)* stepY);

	va_start(msg, str);
	vsprintf(buf, str, msg);
	va_end(msg);

	//	glPushMatrix();
	//	glLoadIdentity();
	glDisable(GL_TEXTURE_2D);

	//	glTranslatef(-5.0*kx,0,0.0);

	glTranslatef(actualX, actualY, 0);
	glScalef(0.3f, 0.3f, 0.3f);

	glColor3f(0.0f, 1.0f, 0.0f);

	glPushAttrib(GL_LIST_BIT);
	glListBase(m_base);
	glCallLists(strlen(buf), GL_UNSIGNED_BYTE, buf);
	glPopAttrib();

	//	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 1.0f);
	//	glPopMatrix();

	m_engine->SetRenderWindow();
}