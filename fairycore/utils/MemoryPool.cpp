#include "stdafx.h"

MemoryPool::MemoryPool( int nunitSize, int nblockSize )
	: m_pPrev(0)
	, m_pNext(0)
	, m_nPoolSize( nblockSize )
	, m_nItemSize( ( nunitSize + 3 ) & (~3) )
	, m_nTOS(0)
{
	m_pPool = new char[m_nItemSize * m_nPoolSize];
	m_pFreeStack = new char*[m_nPoolSize];
	m_pAvailable = m_pPool;
	m_pLast = m_pPool + m_nItemSize * m_nPoolSize;
}

MemoryPool::MemoryPool( MemoryPool* const pPrev )
	: m_pPrev(pPrev)
	, m_pNext(0)
	, m_nPoolSize(pPrev->m_nPoolSize)
	, m_nItemSize(pPrev->m_nItemSize)
	, m_nTOS(0)
{
	m_pPool = new char[m_nItemSize * m_nPoolSize];
	m_pFreeStack = new char*[m_nPoolSize];
	m_pAvailable = m_pPool;
	m_pLast = m_pPool + m_nItemSize * m_nPoolSize;
}

MemoryPool::~MemoryPool()
{
	delete m_pNext;
	delete[] m_pPool;
	delete [] m_pFreeStack;
}

void* MemoryPool::allocate()
{
	// If there are any holes in the free stack then fill them up.
	if (m_nTOS == 0)
	{
		// If there is any space left in this pool then use it, otherwise move
		// on to the next in the linked list.
		if (m_pAvailable < m_pLast)
		{
			char* pReturn = m_pAvailable;
			m_pAvailable += m_nItemSize;
			return (void*)(pReturn);
		}
		else
		{
			// If there is another pool in the list then pass the request on to
			// it, otherwise try to create a new pool.
			if (m_pNext)
			{
				return m_pNext->allocate();
			}
			else
			{
				m_pNext = new MemoryPool(this);
				if( m_pNext )
				{
					return m_pNext->allocate();
				}
			}
		}
	}
	else
	{
		m_nTOS--;
		return (void*)(m_pFreeStack[m_nTOS]);
	}

	return 0;
}

void MemoryPool::deallocate( void* pVoid )
{
	if (pVoid)
	{
		char* pItem = (char*)(pVoid);

		// Check if the item being deleted is within this pool's memory range.
		if (pItem < m_pPool || pItem >= m_pLast)
		{
			// If there is another pool in the list then try to delete from it,
			// otherwise call the generalised delete operator.
			if( m_pNext )
			{
				m_pNext->deallocate( pItem );
			}
			else
			{
				delete (char*)(pVoid);
			}
		}
		else
		{
			// Add a hole to the free stack.
			m_pFreeStack[m_nTOS] = pItem;
			m_nTOS++;
			ASSERT(m_nTOS <= m_nPoolSize);			

			// If this pool is empty and it is the last in the linked list
			// then delete it and set the previous pool to the last.
			if( m_pPrev && !m_pNext && (long)(m_nTOS * m_nItemSize) == m_pAvailable - m_pPool )
			{
				m_pPrev->m_pNext = 0;
				delete this;
			}
		}
	}
}

void MemoryPool::clear()
{
	m_nTOS = 0;
	m_pAvailable = m_pPool;
	if( m_pNext )
	{
		m_pNext->clear();
	}
}

void* operator new( size_t sz, MemoryPool* pool )
{
	return pool->allocate();
}

void operator delete( void* p, MemoryPool* pool )
{
	pool->deallocate( p );
}

