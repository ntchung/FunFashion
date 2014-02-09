#include "stdafx.h"

static ObjectsPool* g_sharedObjectsPool = NULL;

ObjectsPool::ObjectsPool(int min, int max)
	: m_min( min )
	, m_max( max )
{
	m_poolsCount = m_max / m_min;
	m_memoryPools = new MemoryPool*[m_poolsCount];

	int sz = m_min;
	for( int i=0; i<m_poolsCount; i++ )
	{
		m_memoryPools[i] = new MemoryPool( sz, m_min );
		sz += m_min;
	}
}

ObjectsPool::~ObjectsPool()
{
	for( int i=0; i<m_poolsCount; i++ )
	{
		SAFE_DELETE( m_memoryPools[i] );
	}

	SAFE_DELETE_ARRAY( m_memoryPools );
}

void ObjectsPool::destroy()
{
	delete this;
}

ObjectsPool* ObjectsPool::shared()
{
	if( !g_sharedObjectsPool )
	{
		g_sharedObjectsPool = new ObjectsPool();
		g_sharedObjectsPool->autorelease();
		g_sharedObjectsPool->retain();
	}

	return g_sharedObjectsPool;
}

MemoryPool* ObjectsPool::get(int size)
{
	int sz = m_min;
	for( int i=0; i<m_poolsCount; ++i )
	{
		if( size <= sz )
		{
			return m_memoryPools[i];
		}

		sz += m_min;
	}

	return NULL;
}

int ObjectsPool::getMinimalCapacity(int size) const
{
	int sz = m_min;
	for (int i = 0; i<m_poolsCount; ++i)
	{
		if (size <= sz)
		{
			return sz;
		}

		sz += m_min;
	}

	return 0;
}

void* operator new(size_t sz, bool usePool)
{
	return ObjectsPool::shared()->get(sz)->allocate();
}
