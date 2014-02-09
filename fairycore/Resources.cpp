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

}

Resources::~Resources()
{

}

void Resources::destroy()
{
	delete this;
}
