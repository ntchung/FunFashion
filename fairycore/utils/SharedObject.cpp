#include "stdafx.h"

DynamicArray<SharedObject*> SharedObject::s_autoReleasePool;

SharedObject::SharedObject()
: m_referenceCount(1)
{

}

void SharedObject::autorelease()
{
	s_autoReleasePool.add(this);
}

void SharedObject::retain()
{
	++m_referenceCount;
}

void SharedObject::release()
{
	--m_referenceCount;
	if (m_referenceCount <= 0)
	{
		this->destroy();
	}
}

void SharedObject::autoReleaseGC()
{
	for (int i = 0; i < s_autoReleasePool.count();)
	{
		if (s_autoReleasePool[i]->autoRelease())
		{
			s_autoReleasePool.removeAt(i);
		}
		else
		{
			++i;
		}
	}
}

void SharedObject::autoReleasePurge()
{
	for (int i = 0; i < s_autoReleasePool.count(); ++i)
	{
		s_autoReleasePool[i]->destroy();
	}
	s_autoReleasePool.clear();
}

bool SharedObject::autoRelease()
{
	if (m_referenceCount <= 1)
	{
		this->destroy();
		return true;
	}

	return false;
}
