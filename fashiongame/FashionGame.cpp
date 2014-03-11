#include "stdafx.h"
#include "FairyCore.h"
#include "FairyHeart.h"
#include "RenderTexture.h"
#include "utils/GameState.h"
#include "gui/GUI.h"

static FairyHeart* g_fairyHeart;
static GUI* g_gui;
static Camera* g_camera;
static Camera* g_rtCamera;

static GameState* g_currentState;
static GameState* g_nextState;

static bool g_requestTakeScreenshot = false;
static char g_screenShotFilePath[512];

void gameTakeScreenshot();
void gameWriteScreenShotTGA(const char* path);

void gameSetup()
{
}

void gameInit()
{
	fairyCoreInit();

	g_fairyHeart = new FairyHeart();
	g_gui = GUI::create();
	g_camera = Camera::create();
	g_rtCamera = Camera::create();

	g_rtCamera->setRenderTexture(RenderTexture::create(1024, 1024));

	g_currentState = StatePlay::instance();
	g_nextState = g_currentState;
	g_currentState->begin();	
}

void gameDestroy()
{
	g_gui->release();
	g_camera->release();
	g_rtCamera->release();
	delete g_fairyHeart;

	fairyCoreDestroy();
}

void gameUpdate()
{
	if (g_currentState != g_nextState)
	{
		g_fairyHeart->reset();
		g_currentState->end();

		g_currentState = g_nextState;
		g_currentState->begin();

		g_fairyHeart->addCamera(g_gui);
	}

	g_currentState->update();
	g_fairyHeart->update();
	fairyCoreUpdate();
}

void gameRender()
{
	g_currentState->render();
	g_fairyHeart->render();

	g_rtCamera->present();
	g_camera->present();

	g_currentState->onGUI();
	g_gui->present();

	if (g_requestTakeScreenshot)
	{
		g_requestTakeScreenshot = false;
		gameTakeScreenshot();
		gameWriteScreenShotTGA(g_screenShotFilePath);
	}
}

GUI* gui()
{
	return g_gui;
}

Camera* camera()
{
	return g_camera;
}

Camera* rtCamera()
{
	return g_rtCamera;
}

void gameSetScreenSize(int width, int height)
{
	g_fairyHeart->setViewport(0, 0, (float)width, (float)height);
	g_gui->setViewportRect(Rectf(0, 0, (float)width, (float)height));
	g_camera->setViewportRect(Rectf(0, 0, (float)width, (float)height));
	g_rtCamera->setViewportRect(Rectf(0, 0, (float)width, (float)height));
}

void gameRequestScreenshot(const char* filePath)
{
	g_screenShotFilePath[0] = '\0';
	strcpy(g_screenShotFilePath, filePath);

	g_requestTakeScreenshot = true;
}
