#ifndef __MEMORYPOOL_H__
#define __MEMORYPOOL_H__

#include <stdlib.h>

class MemoryPool
{
public:
	MemoryPool( int nunitSize, int nblockSize );
	~MemoryPool();

	void* allocate();
	void deallocate( void* pVoid );

	void clear();

private:
	MemoryPool( MemoryPool* const pPrev );

	// New allocation pools are created and inserted into a doubly-linked list.
	MemoryPool* const	m_pPrev;
	MemoryPool*			m_pNext;

	const size_t	m_nPoolSize;	// Maximum number of items in the pool.
	const size_t	m_nItemSize;	// The size of the contained item.
	char*			m_pAvailable;	// Next available item.
	char*			m_pLast;		// End of the pool.
	size_t			m_nTOS;			// Top of the free stack.

	char*			m_pPool;		// The allocation pool of items.
	char**			m_pFreeStack;	// The stack of deleted items.

};

void* operator new( size_t sz, MemoryPool* pool );
void operator delete( void* p, MemoryPool* pool );

#endif // __MEMORYPOOL_H__
