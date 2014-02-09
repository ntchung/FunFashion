#include "stdafx.h"

FairyHeart::FairyHeart()
{
}

FairyHeart::~FairyHeart()
{
}

void FairyHeart::addCamera(Camera* camera)
{
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
	for (int i = 0; i < m_cameras.count(); ++i)
	{
		m_cameras[i]->present();
	}
}
