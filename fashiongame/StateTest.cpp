#include "stdafx.h"
#include "FashionGame.h"
#include "Resources.h"
#include "Shader.h"
#include "Material.h"
#include "PictureRenderer.h"
#include "gui/GUI.h"

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
}

void StateTest::onGUI()
{
}
