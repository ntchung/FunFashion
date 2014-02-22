#include "stdafx.h"

DynamicArray<SharedObject*> SharedObject::s_autoReleasePool;
bool SharedObject::s_isPurgingAutoReleasePool = false;

SharedObject::SharedObject()
: m_referenceCount(1)
, m_isAutoRelease(false)
{

}

void SharedObject::autorelease()
{
	ASSERT(!s_autoReleasePool.contains(this));
	s_autoReleasePool.add(this);
	m_isAutoRelease = true;
}

void SharedObject::retain()
{
	++m_referenceCount;
}

void SharedObject::release()
{
	if (s_isPurgingAutoReleasePool && m_isAutoRelease)
	{
		return;
	}

	--m_referenceCount;
	if (m_referenceCount == 0)
	{
		this->destroy();
	}
}

void SharedObject::autoReleaseGC()
{
	int count = s_autoReleasePool.count();
	for (int i = count - 1; i >= 0; --i)
	{
		if (s_autoReleasePool[i]->commenceDestroy())
		{
			s_autoReleasePool.removeAt(i);
		}
	}
}

void SharedObject::autoReleasePurge()
{
	s_isPurgingAutoReleasePool = true;

	int count = s_autoReleasePool.count();
	for (int i = count - 1; i >= 0; --i)
	{			
		s_autoReleasePool[i]->destroy();			
	}
	
	s_autoReleasePool.clear();
}

bool SharedObject::commenceDestroy()
{
	if (m_referenceCount == 1)
	{
		this->destroy();
		return true;
	}

	return false;
}
