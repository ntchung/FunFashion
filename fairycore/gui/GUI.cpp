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
}

GUI::~GUI()
{

}

void GUI::present()
{

}
