#include "stdafx.h"
#include "FairyCore.h"
#include "FairyHeart.h"
#include "utils/GameState.h"
#include "gui/GUI.h"

static FairyHeart* g_fairyHeart;
static GUI* g_gui;

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

	g_currentState = StateTest::instance();
	g_nextState = g_currentState;
	g_currentState->begin();	
	g_fairyHeart->addCamera(g_gui);
}

void gameDestroy()
{
	g_gui->destroy();
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
}

GUI* gui()
{
	return g_gui;
}
