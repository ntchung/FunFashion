#include "stdafx.h"

static Resources* g_sharedResources = 0;

Resources* Resources::shared()
{
	if (!g_sharedResources)
	{
		g_sharedResources = new Resources();
		g_sharedResources->autorelease();
		g_sharedResources->retain();
	}

	return g_sharedResources;
}

Resources::Resources()
{
	m_cachedObjects = List::create(false);
}

Resources::~Resources()
{
	m_cachedObjects->release();
}

void Resources::destroy()
{
	delete this;
}

SharedObject* Resources::findInCache(const char* name)
{
	unsigned int hashName = String::makeHash(name);

	SharedObject* obj;
	for (int i = m_cachedObjects->count() - 1; i >= 0; --i)
	{
		obj = (SharedObject*)m_cachedObjects->get(i);
		if (obj->hashName() == hashName)
		{
			return obj;
		}
	}
	
	return NULL;
}
