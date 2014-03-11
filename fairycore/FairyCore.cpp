#include "stdafx.h"

static long long m_engineTime = 0;

void fairyCoreInit()
{
	SharedObject::setup();

	ObjectsPool::shared();
	Resources::shared();
	RenderState::shared();

	Transform::setup();
	RenderBatch::setup();
	ByteArray::setup();
	String::setup();

	m_engineTime = Timer::getRealTime();
	Timer::shared();
}

void fairyCoreUpdate()
{
	long long time = Timer::getRealTime();
	Timer::shared()->update((unsigned int)(time - m_engineTime));
	m_engineTime = time;

	Transform::update();
	SharedObject::autoReleaseGC();
}

void fairyCoreDestroy()
{		
	SharedObject::autoReleasePurge();
	RenderBatch::cleanUp();
}

