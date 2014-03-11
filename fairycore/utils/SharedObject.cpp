#include "stdafx.h"

DynamicArray<SharedObject*>* SharedObject::s_autoReleasePool;
DynamicArray<SharedObject*>* SharedObject::s_deletingPool;
bool SharedObject::s_isPurgingAutoReleasePool = false;

void SharedObject::setup()
{
	s_autoReleasePool = new DynamicArray<SharedObject*>();
	s_deletingPool = new DynamicArray<SharedObject*>();
}

SharedObject::SharedObject()
: m_referenceCount(1)
, m_isAutoRelease(false)
, m_hashName(0)
{

}

void SharedObject::autorelease()
{
	ASSERT(!s_autoReleasePool->contains(this));
	s_autoReleasePool->add(this);
	m_isAutoRelease = true;
}

void SharedObject::retain()
{
	++m_referenceCount;
}

void SharedObject::release()
{
	if( (s_isPurgingAutoReleasePool && m_isAutoRelease)
		|| m_referenceCount <= 0 )
	{
		return;
	}

	--m_referenceCount;
	if (m_referenceCount == 0)
	{
		s_deletingPool->add(this);		
	}
}

void SharedObject::autoReleaseGC()
{
	int i;
	int count = s_autoReleasePool->count();
	for (i = count - 1; i >= 0; --i)
	{
		if (s_autoReleasePool->get(i)->commenceDestroy())
		{
			s_autoReleasePool->removeAt(i);
		}
	}

	count = s_deletingPool->count();
	for (i = 0; i < count; ++i)
	{
		s_deletingPool->get(i)->destroy();
	}
	s_deletingPool->clear();
}

void SharedObject::autoReleasePurge()
{
	autoReleaseGC();

	s_isPurgingAutoReleasePool = true;

	int count = s_autoReleasePool->count();
	for (int i = count - 1; i >= 0; --i)
	{			
		s_autoReleasePool->get(i)->destroy();			
	}
	
	s_autoReleasePool->clear();

	delete s_autoReleasePool;
	delete s_deletingPool;
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

void SharedObject::setHashName(const char* name)
{
	m_hashName = String::makeHash(name);
}
