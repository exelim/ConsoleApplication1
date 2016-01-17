#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>

#include "pipeline.h"
#include "camera.h"
#include "texture.h"
#include "Shaders.h"

#pragma comment(lib, "glew32.lib")

#define WINDOW_WIDTH  320
#define WINDOW_HEIGHT 320

struct Vertex
{
	Vector3f m_pos;
	Vector2f m_tex;

	Vertex() {}

	Vertex(Vector3f pos, Vector2f tex)
	{
		m_pos = pos;
		m_tex = tex;
	}
};


GLuint VBO;
GLuint IBO;
GLuint gWVPLocation;
GLuint gSampler;
Texture* pTexture = NULL;
Camera* pGameCamera = NULL;

static void RenderSceneCB()
{
	pGameCamera->OnRender();

	glClear(GL_COLOR_BUFFER_BIT);

	static float Scale = 0.0f;

	Scale += 0.1f;

	Pipeline p;
	//p.Rotate(0.0f, Scale, 0.0f);
	p.WorldPos(0.0f, 0.0f, 3.0f);
	p.SetCamera(pGameCamera->GetPos(), pGameCamera->GetTarget(), pGameCamera->GetUp());
	p.SetPerspectiveProj(60.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 100.0f);

	glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, (const GLfloat*)p.GetTrans());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	pTexture->Bind(GL_TEXTURE0);
	glDrawElements(GL_QUADS, 12, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glutSwapBuffers();
}


static void SpecialKeyboardCB(int Key, int x, int y)
{
	pGameCamera->OnKeyboard(Key);
}


static void KeyboardCB(unsigned char Key, int x, int y)
{
	switch (Key) {
	case 'q':
		glutLeaveMainLoop();
	}
}


static void PassiveMouseCB(int x, int y)
{
	pGameCamera->OnMouse(x, y);
}


static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderSceneCB);
	glutIdleFunc(RenderSceneCB);
	glutSpecialFunc(SpecialKeyboardCB);
	glutPassiveMotionFunc(PassiveMouseCB);
	glutKeyboardFunc(KeyboardCB);
}


static void CreateVertexBuffer()
{
	Vertex Vertices[4] = { 
		Vertex(Vector3f(-1.0f, -1.0f, 0.f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(-1.0f, 1.0f, 0.f),      Vector2f(0.f, 1.0f)),
		Vertex(Vector3f(1.0f, 1.0f, 0.f), Vector2f(1.f, 1.0f)),
		Vertex(Vector3f(1.0f, -1.0f, 0.f), Vector2f(1.f, 0.0f))
	};

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}


static void CreateIndexBuffer()
{
	unsigned int Indices[] = { 0, 1, 2, 3};

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tutorial 16");

	InitializeGlutCallbacks();

	pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	CreateVertexBuffer();
	CreateIndexBuffer();

	//CompileShaders();

	Shaders sd;
	sd.Init("BgShader.vs", "BgShader.fs");

	glUseProgram(sd.program);

	glUniform1i(gSampler, 0);

	pTexture = new Texture(GL_TEXTURE_2D, "bg.tga");

	if (!pTexture->Load()) {
		return 1;
	}

	glutMainLoop();

	return 0;
}