#include "stdafx.h"

void fairyCoreInit()
{
	SharedObject::setup();

	ObjectsPool::shared();
	Resources::shared();
	RenderState::shared();

	RenderBatch::setup();
	ByteArray::setup();
	String::setup();
}

void fairyCoreUpdate()
{
	SharedObject::autoReleaseGC();
}

void fairyCoreDestroy()
{		
	SharedObject::autoReleasePurge();
	RenderBatch::cleanUp();
}

