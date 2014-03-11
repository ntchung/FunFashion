#include "stdafx.h"
#include "Camera.h"
#include "Renderer.h"
#include "Material.h"
#include "RenderBatch.h"
#include "VertexList.h"
#include "maths/Color32.h"

PictureRenderer* PictureRenderer::create()
{
	return new(true) PictureRenderer();
}

void PictureRenderer::destroy()
{
	this->~PictureRenderer();
	POOL(PictureRenderer)->deallocate(this);
}

PictureRenderer::PictureRenderer()
: m_isRotateRight(false)
{

}

PictureRenderer::~PictureRenderer()
{
}

void PictureRenderer::draw(Camera* camera, float x, float y, float width, float height)
{
	Rectf position(x-width*0.5f, y-height*0.5f, x+width, y+height);

	GLfloat uvs[8] =
	{
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
	};

	int count = m_vertexList->count();

	if (m_isRotateRight)
	{
		GLfloat vertices[12] =
		{
			position.xMin(), position.yMax(), 10,
			position.xMin(), position.yMin(), 10,
			position.xMax(), position.yMin(), 10,
			position.xMax(), position.yMax(), 10,
		};

		m_vertexList->addVerticesPU(vertices, uvs, 4);
	}
	else
	{
		GLfloat vertices[12] =
		{
			position.xMin(), position.yMin(), 0,
			position.xMax(), position.yMin(), 0,
			position.xMax(), position.yMax(), 0,
			position.xMin(), position.yMax(), 0,
		};

		m_vertexList->addVerticesPU(vertices, uvs, 4);
	}	

	RenderBatch* batch = camera->renderBatch(m_material->shader()->renderQueue());
	batch->addTriangle(m_vertexList, count, count + 1, count + 2);
	batch->addTriangle(m_vertexList, count + 3, count, count + 2);
}
