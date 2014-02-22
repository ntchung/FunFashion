#include "stdafx.h"

void fairyCoreInit()
{
	ObjectsPool::shared();
	Resources::shared();

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
}

