#include "stdafx.h"
#include "FashionGame.h"
#include "Resources.h"
#include "Shader.h"
#include "Material.h"
#include "TestRenderer.h"
#include "gui/GUI.h"

static StateTest* g_stateTestInstance = 0;

static TestRenderer* g_testRenderer;

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
	Shader* shader = Resources::shared()->load<Shader>("core_gui_fillrect.shader");
	shader->autorelease();

	Material* material = Material::create(0, shader);
	material->autorelease();

	g_testRenderer = TestRenderer::create();
	g_testRenderer->setMaterial(material);
}

void StateTest::destroy()
{
	g_testRenderer->release();
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
	g_testRenderer->reset();
	g_testRenderer->draw(camera());
}

void StateTest::onGUI()
{
	//gui()->fillRect(Rectf(0, 0, 100, 100), Color32(0, 255, 0, 255));

	//gui()->fillRect(Rectf(200, 100, 100, 100), Color32(0, 255, 0, 255));
}
