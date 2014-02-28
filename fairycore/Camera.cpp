#include "stdafx.h"

Camera* Camera::create()
{
	return new(true) Camera();
}

void Camera::destroy()
{
	this->~Camera();
	POOL(Camera)->deallocate(this);
}

Camera::Camera()
: m_backgroundColor(1.0f, 1.0f, 1.0f, 1.0f)
, m_clearType(DEPTH_AND_COLOR)
, m_isProjectionDirty(true)
, m_projectType(Orthographic)
, m_orthoSize(4)
, m_zNear(0.3f)
, m_zFar(1000.0f)
{
	m_renderBatches = List::create(false);
	m_renderBatches->retain();
}

Camera::~Camera()
{
	m_renderBatches->release();
}

void Camera::present()
{
	// Prepare matrices
	if (m_isProjectionDirty)
	{
		if (m_projectType == Orthographic)
		{
			buildOrthographicProjectionMatrix(m_projection, m_viewportRect, m_orthoSize, m_zNear, m_zFar);
		}
		m_isProjectionDirty = false;
	}	
	m_worldviewprojection = m_projection * m_view;

	// Clear
	if (m_clearType != NONE)
	{
		glClearColor(m_backgroundColor.red, m_backgroundColor.green, m_backgroundColor.blue, m_backgroundColor.alpha);
		glClear(m_clearType);		
	}
	
	for (int i = 0; i < m_renderBatches->count(); ++i)
	{
		RenderBatch* batch = (RenderBatch*)m_renderBatches->get(i);
		batch->draw();
		batch->clear();
	}
}

RenderBatch* Camera::renderBatch(int queue)
{
	for (int i = 0; i < m_renderBatches->count(); ++i)
	{
		RenderBatch* batch = (RenderBatch*)m_renderBatches->get(i);
		if (batch->getRenderQueue() == queue)
		{
			return batch;
		}
	}

	RenderBatch* batch = RenderBatch::create(this, queue);
	batch->autorelease();
	m_renderBatches->add(batch);
	return batch;
}

void Camera::buildOrthographicProjectionMatrix(Matrix4x4& mat, const Rectf& viewport, float size, float zNear, float zFar)
{
	const float wideSize = (size * viewport.width()) / viewport.height();
	const float left = -wideSize;
	const float right = wideSize;
	const float top = size;
	const float bottom = -size;
	const float far = -zFar;
	const float near = zNear;

	const float a = 2.0f / (right - left);
	const float b = 2.0f / (top - bottom);
	const float c = -2.0f / (far - near);

	const float tx = -(right + left) / (right - left);
	const float ty = -(top + bottom) / (top - bottom);
	const float tz = -(far + near) / (far - near);

	mat.set(
		a, 0, 0, 0,
		0, b, 0, 0,
		0, 0, c, 0,
		tx, ty, tz, 1,
		false);
}
