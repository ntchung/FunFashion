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
	// Matrices
	m_view = Matrix4x4::identity;
	
	// Materials
	Shader* guiFillRectShader = Resources::shared()->load<Shader>("core_gui_fillrect.shader");
	Material* guiFillRectMaterial = Material::create(0, guiFillRectShader);	
	m_fillRectVertices = VertexList::create(guiFillRectMaterial);

	// Unlike others, GUI drawing only needs one single queue
	m_renderBatch = RenderBatch::create(this);
}

GUI::~GUI()
{
	m_fillRectVertices->release();
	m_renderBatch->release();
}

void GUI::present()
{
	if (m_isProjectionDirty)
	{
		build2DProjectionMatrix(m_projection, m_viewportRect.width(), m_viewportRect.height());
		m_worldviewprojection = m_projection;

		m_isProjectionDirty = false;
	}

	m_renderBatch->draw();
	
	m_renderBatch->clear();
	m_fillRectVertices->clear();
}

void GUI::fillRect(const Rectf& position, const Color32& color)
{	
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

	int count = m_fillRectVertices->count();
	m_fillRectVertices->addVerticesPC(vertices, vertexColors, 4);

	m_renderBatch->addTriangle(m_fillRectVertices, count, count + 1, count + 2);
	m_renderBatch->addTriangle(m_fillRectVertices, count + 3, count, count + 2);
}

void GUI::build2DProjectionMatrix(Matrix4x4& mat, float viewWidth, float viewHeight)
{
	const float left = 0.0f;
	const float right = viewWidth;
	const float top = 0;
	const float bottom = viewHeight;
	const float far = -1000.0f;
	const float near = 0.0f;

	const float a = 2.0f / (right - left);
	const float b = 2.0f / (top - bottom);
	const float c = -2.0f / (far - near);

	const float tx = -(right + left) / (right - left);
	const float ty = -(top + bottom) / (top - bottom);
	const float tz = -(far + near) / (far - near);

	mat.set(
		a,  0,  0,  0,
		0,  b,  0,  0,
		0,  0,  c,  0,
		tx, ty, tz, 1,		
		false );	
}
