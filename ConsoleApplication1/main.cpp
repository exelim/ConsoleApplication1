
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "windows.h"
#include <vector>
#include <cstdlib>

#include "pipeline.h"
#include "camera.h"
#include "texture.h"
#include "Shaders.h"
#include "math_3d.h"
#include "Object.h"
#include "Pipe_Object.h"
#include "Bird_Object.h"
#include "PipeManager.h"
#include "ScoreObject.h"

#include "esUtil.h"

#pragma comment(lib, "libEGL.lib")
#pragma comment(lib, "libGLESv2.lib")
#pragma comment(lib, "Utilities.lib")

#define WINDOW_WIDTH  320
#define WINDOW_HEIGHT 320

Camera* pGameCamera = NULL;


Object bg;
Object fb_title;
Object btn_start;
Object btn_options;
BirdObject bird;
PipeManager pm;
std::vector<Object *> m_digits;
ScoreObject so;
Object UA, US;
Object score_board, game_over;

double asd = 0;

std::string language = "";


enum class GS {CHOOSE_LANGUAGE, TRAINING, MAIN_MENU, IN_GAME, SCORE};

GS current_state;

void Draw(ESContext *esContext)
{
	pGameCamera->OnRender();

	glClear(GL_COLOR_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	bg.Draw(asd);

	switch (current_state)
	{
	case GS::CHOOSE_LANGUAGE:
		UA.Draw(asd);
		US.Draw(asd);
		break;
	case GS::MAIN_MENU:
		fb_title.Draw(asd);
		btn_start.Draw(asd);
		btn_options.Draw(asd);
		break;

	case GS::IN_GAME:

		if (pm.CheckCollisionWithBird(bird))
			current_state = GS::SCORE;

		if (pm.CheckScore(bird))
			so.IncreaseScore();

		pm.DeletePipes();
		asd += 0.005;

		bird.Draw(asd);
		pm.DrawPipes(asd);
		so.Draw(asd);
		break;

	case GS::SCORE:
		score_board.Draw(asd);
		game_over.Draw(asd);
		break;
	}

	
	glDisable(GL_BLEND);


	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}


void Update(ESContext *esContext, float deltaTime)
{
}


static void SpecialKeyboardCB(int Key, int x, int y)
{
	pGameCamera->OnKeyboard(Key);
}

void InitLanguageButtons()
{
	Vertex btn_start_verticies[4] = {
		Vertex(Vector3f(-0.5f, -0.2f, 0.f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(-0.5f, 0.2f, 0.f),      Vector2f(0.f, 1.0f)),
		Vertex(Vector3f(0.5f, 0.2f, 0.f), Vector2f(1.f, 1.0f)),
		Vertex(Vector3f(0.5f, -0.2f, 0.f), Vector2f(1.f, 0.0f))
	};

	btn_start.Init("BgShader.vs", "BgShader.fs", btn_start_verticies, "start_btn_" + language + ".tga");

	Vertex btn_language_verticies[4] = {
		Vertex(Vector3f(-0.5f, -0.8f, 0.f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(-0.5f, -0.4f, 0.f),      Vector2f(0.f, 1.0f)),
		Vertex(Vector3f(0.5f, -0.4f, 0.f), Vector2f(1.f, 1.0f)),
		Vertex(Vector3f(0.5f, -0.8f, 0.f), Vector2f(1.f, 0.0f))
	};

	btn_options.Init("BgShader.vs", "BgShader.fs", btn_language_verticies, "language_" + language + ".tga");

	Vertex score_board_verticies[4] = {
		Vertex(Vector3f(-0.7f, -0.5f, 0.f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(-0.7f, 0.3f, 0.f),      Vector2f(0.f, 1.0f)),
		Vertex(Vector3f(0.7f, 0.3f, 0.f), Vector2f(1.f, 1.0f)),
		Vertex(Vector3f(0.7f, -0.5f, 0.f), Vector2f(1.f, 0.0f))
	};

	score_board.Init("BgShader.vs", "BgShader.fs", score_board_verticies, "score_board_" + language + ".tga");

	Vertex game_over_verticies[4] = {
		Vertex(Vector3f(-0.8f, 0.4f, 0.f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(-0.8f, 0.8f, 0.f),      Vector2f(0.f, 1.0f)),
		Vertex(Vector3f(0.8f, 0.8f, 0.f), Vector2f(1.f, 1.0f)),
		Vertex(Vector3f(0.8f, 0.4f, 0.f), Vector2f(1.f, 0.0f))
	};

	game_over.Init("BgShader.vs", "BgShader.fs", game_over_verticies, "game_over_" + language + ".tga");
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
		case 0x53:	// S
			if (current_state == GS::MAIN_MENU)
			{
				current_state = GS::IN_GAME;
			}
			break;
		case 0x55:	// U
			if (current_state == GS::CHOOSE_LANGUAGE)
			{
				current_state = GS::MAIN_MENU;
				language = "UA";
				InitLanguageButtons();
			}
			break;

		case 0x41:	// A
			if (current_state == GS::CHOOSE_LANGUAGE)
			{
				current_state = GS::MAIN_MENU;
				language = "US";
				InitLanguageButtons();
			}
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
	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, KeyboardCB);
}

int main(int argc, char** argv)
{
	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow(&esContext, "Hello Triangle", WINDOW_WIDTH, WINDOW_HEIGHT, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	InitializeGlutCallbacks(esContext);

	pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	current_state = GS::CHOOSE_LANGUAGE;

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

	Vertex fb_title_verticies[4] = {
		Vertex(Vector3f(-0.8f, 0.4f, 0.f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(-0.8f, 0.8f, 0.f),      Vector2f(0.f, 1.0f)),
		Vertex(Vector3f( 0.8f, 0.8f, 0.f), Vector2f(1.f, 1.0f)),
		Vertex(Vector3f( 0.8f, 0.4f, 0.f), Vector2f(1.f, 0.0f))
	};

	fb_title.Init("BgShader.vs", "BgShader.fs", fb_title_verticies, "fb_title.tga");

	Vertex US_verticies[4] = {
		Vertex(Vector3f(-0.4f, -0.7f, 0.f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(-0.4f, -0.2f, 0.f),      Vector2f(0.f, 1.0f)),
		Vertex(Vector3f(0.4f, -0.2f, 0.f), Vector2f(1.f, 1.0f)),
		Vertex(Vector3f(0.4f, -0.7f, 0.f), Vector2f(1.f, 0.0f))
	};

	UA.Init("BgShader.vs", "BgShader.fs", US_verticies, "US.tga");

	Vertex UA_verticies[4] = {
		Vertex(Vector3f(-0.4f, 0.0f, 0.f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(-0.4f, 0.5f, 0.f),      Vector2f(0.f, 1.0f)),
		Vertex(Vector3f(0.4f, 0.5f, 0.f), Vector2f(1.f, 1.0f)),
		Vertex(Vector3f(0.4f, 0.0f, 0.f), Vector2f(1.f, 0.0f))
	};

	US.Init("BgShader.vs", "BgShader.fs", UA_verticies, "UA.tga");

	for (int i = 0; i < 5; i++)
	{
		pm.AddPipe(true);
		pm.AddPipe(false);
	}

	so.Init("", "", nullptr, "");

	esMainLoop(&esContext);

	return 0;
}