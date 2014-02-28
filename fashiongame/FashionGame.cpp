#include "stdafx.h"
#include "FairyCore.h"
#include "FairyHeart.h"
#include "utils/GameState.h"
#include "gui/GUI.h"

static FairyHeart* g_fairyHeart;
static GUI* g_gui;
static Camera* g_camera;

static GameState* g_currentState;
static GameState* g_nextState;

void gameSetup()
{
}

void gameInit()
{
	fairyCoreInit();

	g_fairyHeart = new FairyHeart();
	g_gui = GUI::create();
	g_camera = Camera::create();

	g_currentState = StateTest::instance();
	g_nextState = g_currentState;
	g_currentState->begin();	
}

void gameDestroy()
{
	g_gui->release();
	g_camera->release();
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

	g_camera->present();

	g_currentState->onGUI();
	g_gui->present();
}

GUI* gui()
{
	return g_gui;
}

Camera* camera()
{
	return g_camera;
}

void gameSetScreenSize(int width, int height)
{
	g_fairyHeart->setViewport(0, 0, (float)width, (float)height);
	g_gui->setViewportRect(Rectf(0, 0, (float)width, (float)height));
	g_camera->setViewportRect(Rectf(0, 0, (float)width, (float)height));
}
