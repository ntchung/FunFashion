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
{

}

Camera::~Camera()
{

}

void Camera::present()
{
	if (m_clearType != NONE)
	{
		glClearColor(m_backgroundColor.red, m_backgroundColor.green, m_backgroundColor.blue, m_backgroundColor.alpha);
		glClear(m_clearType);
	}
}

