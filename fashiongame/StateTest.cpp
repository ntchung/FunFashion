#include "stdafx.h"
#include "FashionGame.h"

static StateTest* g_stateTestInstance = 0;

StateTest* StateTest::instance()
{
	if (!g_stateTestInstance)
	{
		g_stateTestInstance = new StateTest();
	}

	return g_stateTestInstance;
}

StateTest::StateTest()
{
}

void StateTest::destroy()
{
	delete this;
}

void StateTest::begin()
{

}

void StateTest::end()
{

}

void StateTest::update()
{

}

void StateTest::render()
{
	gui()->fillRect(Rectf(0, 0, 100, 100), Color32(0, 255, 0, 0));
}

