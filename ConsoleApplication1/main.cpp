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
#include "math_3d.h"
#include "Object.h"
#include "Pipe_Object.h"
#include "Bird_Object.h"

#pragma comment(lib, "glew32.lib")

#define WINDOW_WIDTH  320
#define WINDOW_HEIGHT 320

Camera* pGameCamera = NULL;


Object bg;
BirdObject bird;
PipeObject tube;
PipeObject tube2;

double asd = 0;

void Draw()
{
	bird.CheckInteractWithTube(&tube2);
	asd += 0.005;
	pGameCamera->OnRender();

	glClear(GL_COLOR_BUFFER_BIT);
	bg.Draw(asd);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
		bird.Draw(asd);
		tube.Draw(asd);
		tube2.Draw(asd);
	glDisable(GL_BLEND);
	

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
	glutDisplayFunc(Draw);
	glutIdleFunc(Draw);
	glutSpecialFunc(SpecialKeyboardCB);
	glutPassiveMotionFunc(PassiveMouseCB);
	glutKeyboardFunc(KeyboardCB);
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

	Vertex Vertices[4] = {
		Vertex(Vector3f(-1.0f, -1.0f, 0.f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(-1.0f, 1.0f, 0.f),      Vector2f(0.f, 1.0f)),
		Vertex(Vector3f(1.0f, 1.0f, 0.f), Vector2f(1.f, 1.0f)),
		Vertex(Vector3f(1.0f, -1.0f, 0.f), Vector2f(1.f, 0.0f))
	};

	bg.Init("BgShader.vs", "BgShader.fs", Vertices, "bg.tga");

	Vertex Vertices1[4] = {
		Vertex(Vector3f(-0.8f, -0.8f, 0.f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(-0.8f, -0.6f, 0.f),      Vector2f(0.f, 1.0f)),
		Vertex(Vector3f(-0.6f, -0.6f, 0.f), Vector2f(1.f, 1.0f)),
		Vertex(Vector3f(-0.6f, -0.8f, 0.f), Vector2f(1.f, 0.0f))
	};

	bird.Init("BgShader.vs", "BgShader.fs", Vertices1, "bird.tga", "bird_2.tga", "bird_3.tga");

	Vertex Vertices2[4] = {
		Vertex(Vector3f(0.f, 0.4f, 0.f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(0.f, 1.0f, 0.f),      Vector2f(0.f, 1.0f)),
		Vertex(Vector3f(0.2f, 1.f, 0.f), Vector2f(1.f, 1.0f)),
		Vertex(Vector3f(0.2f, 0.4f, 0.f), Vector2f(1.f, 0.0f))
	};

	tube.Init("tubeShader.vs", "tubeShader.fs", Vertices2, "top_tube.tga", PipeObject::TYPE::TOP);

	Vertex Vertices3[4] = {
		Vertex(Vector3f(0.f, -1.f, 0.f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(0.f, -0.4f, 0.f),      Vector2f(0.f, 1.0f)),
		Vertex(Vector3f(0.2f, -0.4f, 0.f), Vector2f(1.f, 1.0f)),
		Vertex(Vector3f(0.2f, -1.f, 0.f), Vector2f(1.f, 0.0f))
	};

	tube2.Init("tubeShader.vs", "tubeShader.fs", Vertices3, "bot_tube.tga", PipeObject::TYPE::BOTTOM);

	glutMainLoop();

	return 0;
}