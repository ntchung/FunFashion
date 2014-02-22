#include "stdafx.h"

static UIDGenerator* g_sharedUIDGenerator = 0;

UIDGenerator* UIDGenerator::shared()
{
	if (!g_sharedUIDGenerator)
	{
		g_sharedUIDGenerator = new UIDGenerator();
		g_sharedUIDGenerator->autorelease();
		g_sharedUIDGenerator->retain();
	}

	return g_sharedUIDGenerator;
}

void UIDGenerator::destroy()
{
	delete this;
}

int UIDGenerator::next()
{
	return ++m_loop;
}

UIDGenerator::UIDGenerator()
: m_loop(0)
{
}

UIDGenerator::~UIDGenerator()
{
}

