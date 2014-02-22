#include "stdafx.h"

GUI* GUI::create()
{
	return new(true) GUI();
}

void GUI::destroy()
{
	this->~GUI();
	POOL(GUI)->deallocate(this);
}

GUI::GUI()
{
	Shader* guiShader = Resources::shared()->load<Shader>("core_gui.shader");
	guiShader->autorelease();

	Material* guiMaterial = Material::create(guiShader);
	guiMaterial->autorelease();

	m_guiRenderBatch = RenderBatch::create(guiMaterial);
	m_guiRenderBatch->retain();
}

GUI::~GUI()
{
	m_guiRenderBatch->release();
}

void GUI::present()
{
	m_guiRenderBatch->draw();
}
