
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "windows.h"
//#include <GL/GL.h>

#include "pipeline.h"
#include "camera.h"
#include "texture.h"
#include "Shaders.h"
#include "math_3d.h"
#include "Object.h"
#include "Pipe_Object.h"
#include "Bird_Object.h"
#include "PipeManager.h"

#include "esUtil.h"

#pragma comment(lib, "libEGL.lib")
#pragma comment(lib, "libGLESv2.lib")
#pragma comment(lib, "Utilities.lib")

#define WINDOW_WIDTH  320
#define WINDOW_HEIGHT 320

Camera* pGameCamera = NULL;


Object bg;
BirdObject bird;
PipeManager pm;

double asd = 0;

void Draw(ESContext *esContext)
{
	if (!pm.CheckCollisionWithBird(bird))
	{
		pm.DeletePipes();
		asd += 0.005;
		pGameCamera->OnRender();

		glClear(GL_COLOR_BUFFER_BIT);
		bg.Draw(asd);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		bird.Draw(asd);
		pm.DrawPipes(asd);
		glDisable(GL_BLEND);


		eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
	}
}


void Update(ESContext *esContext, float deltaTime)
{

}


static void SpecialKeyboardCB(int Key, int x, int y)
{
	pGameCamera->OnKeyboard(Key);
}


static void KeyboardCB(ESContext *esContext, unsigned char key, bool bIsPressed)
{
	if (bIsPressed)
	{
		switch (key)
		{
		case 0x57:	// W
			bird.m_shouldUpBird = true;
			break;
		}
	}
}


static void PassiveMouseCB(int x, int y)
{
	pGameCamera->OnMouse(x, y);
}


static void InitializeGlutCallbacks(ESContext & esContext)
{
	/*glutDisplayFunc(Draw);
	glutIdleFunc(Draw);
	glutSpecialFunc(SpecialKeyboardCB);
	glutPassiveMotionFunc(PassiveMouseCB);
	glutKeyboardFunc(KeyboardCB);*/

	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, KeyboardCB);
}

int main(int argc, char** argv)
{
	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow(&esContext, "Hello Triangle", WINDOW_WIDTH, WINDOW_HEIGHT, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	/*glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tutorial 16");*/

	InitializeGlutCallbacks(esContext);

	pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Must be done after glut is initialized!
	/*GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}*/

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
		Vertex(Vector3f(-0.8f, 0.2f, 0.f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(-0.8f, 0.4f, 0.f),      Vector2f(0.f, 1.0f)),
		Vertex(Vector3f(-0.6f, 0.4f, 0.f), Vector2f(1.f, 1.0f)),
		Vertex(Vector3f(-0.6f, 0.2f, 0.f), Vector2f(1.f, 0.0f))
	};

	bird.Init("BirdShader.vs", "BirdShader.fs", Vertices1, "bird.tga", "bird_2.tga", "bird_3.tga");

	for (int i = 0; i < 5; i++)
	{
		pm.AddPipe();
	}

	/*Vertex Vertices2[4] = {
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

	tube2.Init("tubeShader.vs", "tubeShader.fs", Vertices3, "bot_tube.tga", PipeObject::TYPE::BOTTOM);*/

	//glutMainLoop();
	esMainLoop(&esContext);

	return 0;
}