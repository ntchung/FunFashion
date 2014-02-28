#include "stdafx.h"
#include "Camera.h"
#include "Renderer.h"
#include "Material.h"
#include "RenderBatch.h"
#include "VertexList.h"
#include "maths/Color32.h"

TestRenderer* TestRenderer::create()
{
	return new(true) TestRenderer();
}

void TestRenderer::destroy()
{
	this->~TestRenderer();
	POOL(TestRenderer)->deallocate(this);
}

TestRenderer::~TestRenderer()
{
}

void TestRenderer::draw(Camera* camera)
{
	Rectf position(0.0f, 0.0f, 1.0f, 1.0f);
	Color32 color(255, 0, 0, 255);

	GLfloat vertices[12] =
	{
		position.xMin(), position.yMin(), 0,
		position.xMax(), position.yMin(), 0,
		position.xMax(), position.yMax(), 0,
		position.xMin(), position.yMax(), 0,
	};

	GLubyte vertexColors[16] =
	{
		color.r, color.g, color.b, color.a,
		color.r, color.g, color.b, color.a,
		color.r, color.g, color.b, color.a,
		color.r, color.g, color.b, color.a,
	};

	int count = m_vertexList->count();
	m_vertexList->addVerticesPC(vertices, vertexColors, 4);

	RenderBatch* batch = camera->renderBatch(m_material->shader()->getRenderQueue());
	batch->addTriangle(m_vertexList, count, count + 1, count + 2);
	batch->addTriangle(m_vertexList, count + 3, count, count + 2);
}
