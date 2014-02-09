#include "stdafx.h"
#include "utils/String.h"

void fairyCoreInit()
{
	ObjectsPool::shared();
	Resources::shared();

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

