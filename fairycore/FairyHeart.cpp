#include "stdafx.h"

FairyHeart::FairyHeart()
{
}

FairyHeart::~FairyHeart()
{
}

void FairyHeart::addCamera(Camera* camera)
{
	camera->setViewportRect(m_viewportRect);
	m_cameras.add(camera);	
}

void FairyHeart::reset()
{
	m_cameras.clear();
}

void FairyHeart::update()
{
}

void FairyHeart::render()
{
	RenderState::shared()->init();

	for (int i = 0; i < m_cameras.count(); ++i)
	{
		((Camera*)m_cameras[i])->present();
	}
}

void FairyHeart::setViewport(float x, float y, float width, float height)
{
	m_viewportRect.Set(x, y, width, height);	
	for (int i = 0; i < m_cameras.count(); ++i)
	{
		((Camera*)m_cameras[i])->setViewportRect(m_viewportRect);
	}
}
