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
: m_fillRectCount(0)
{
	Shader* guiFillRectShader = Resources::shared()->load<Shader>("core_gui_fillrect.shader");
	guiFillRectShader->autorelease();

	Material* guiFillRectMaterial = Material::create(guiFillRectShader);
	guiFillRectMaterial->autorelease();

	m_guiFillRectRenderBatch = RenderBatch::create(guiFillRectMaterial);
	m_guiFillRectRenderBatch->retain();
}

GUI::~GUI()
{
	m_guiFillRectRenderBatch->release();
}

void GUI::present()
{
	m_guiFillRectRenderBatch->draw();

	m_guiFillRectRenderBatch->clear();
	m_fillRectCount = 0;
}

void GUI::fillRect(const Rectf& position, const Color32& color)
{
	++m_fillRectCount;
	int expectedRectsCapacity = ((m_fillRectCount >> 4) + 1) << 4;
	m_guiFillRectRenderBatch->requestCapacity(expectedRectsCapacity * 4, expectedRectsCapacity * 6);

	GLfloat vertices[12] = 
	{
		position.xMin(), position.yMin(), 0,
		position.xMin(), position.yMax(), 0,
		position.xMax(), position.yMin(), 0,
		position.xMax(), position.yMax(), 0,
	};

	GLubyte vertexColors[16] =
	{
		color.r, color.g, color.b, color.a,
		color.r, color.g, color.b, color.a,
		color.r, color.g, color.b, color.a,
		color.r, color.g, color.b, color.a,
	};

	m_guiFillRectRenderBatch->addVerticesPC(vertices, vertexColors, 4);

	GLushort indices[6] =
	{
		0, 1, 2,
		3, 0, 2,
	};
	m_guiFillRectRenderBatch->addIndices(indices, 6);
}
