#include "stdafx.h"
#include <malloc.h>

RecyclingMemory* g_sharedRecyclingMemory = 0;

RecyclingMemory* RecyclingMemory::shared()
{
	if (!g_sharedRecyclingMemory)
	{
		g_sharedRecyclingMemory = new RecyclingMemory();
		g_sharedRecyclingMemory->autorelease();
		g_sharedRecyclingMemory->retain();
	}

	return g_sharedRecyclingMemory;
}

void RecyclingMemory::destroy()
{
	this->~RecyclingMemory();
	delete this;
}

RecyclingMemory::RecyclingMemory()
: m_freeChunk(NULL)
, m_usedChunk(NULL)
{
}

RecyclingMemory::~RecyclingMemory()
{
	MemoryChunk* p = m_usedChunk;
	while (p)
	{
		MemoryChunk* current = p;
		p = p->next;

		free(current->ptr);		
		POOL(MemoryChunk)->deallocate(current);
	}
	m_usedChunk = NULL;

	clean();
}

void RecyclingMemory::recycle(void* data)
{
	if (!data)
	{
		return;
	}

	MemoryChunk* prev;
	MemoryChunk* p;

	// Search if this data is in the list allocated by this	
	prev = m_usedChunk;
	p = m_usedChunk;
	while (p)
	{
		if (p->ptr == data)
		{
			// remove from used list
			if (p == m_usedChunk)
			{
				m_usedChunk = p->next;
			}
			else
			{
				prev->next = p->next;
			}
			break;
		}

		prev = p;
		p = p->next;
	}

	// Not found ?
	if (!p)
	{
		free(data);
		return;
	}

	// Found. Add to free lists
	if (!m_freeChunk)
	{
		m_freeChunk = p;
		p->next = NULL;
	}
	else
	{
		p->next = m_freeChunk;
		m_freeChunk = p;
	}
}

void* RecyclingMemory::allocate(int size)
{
	if (size < 1)
	{
		return NULL;
	}

	int minCapacity;
	MemoryChunk* p;
	MemoryChunk* prev;
	MemoryChunk* foundPrev;
	MemoryChunk* found;

	// Find a good slot in free lists	
	prev = m_freeChunk;
	p = m_freeChunk;
	found = NULL;
	minCapacity = INT_MAX;
	while (p)
	{
		if (p->capacity >= size && p->capacity < minCapacity)
		{
			foundPrev = prev;
			found = p;
			minCapacity = p->capacity;
		}
		prev = p;
		p = p->next;
	}

	// Remove from free list
	if (found)
	{
		if (found == m_freeChunk)
		{
			m_freeChunk = found->next;
		}
		else
		{
			foundPrev->next = found->next;
		}
	}

	// Allocate new one if not found from recylce bin
	if (!found)
	{
		found = new(true) MemoryChunk();
		found->ptr = malloc(size);
		found->capacity = size;
	}

	// Add to used list
	if (!m_usedChunk)
	{
		m_usedChunk = found;
		found->next = NULL;
	}
	else
	{
		found->next = m_usedChunk;
		m_usedChunk = found;
	}

	return found->ptr;
}

void RecyclingMemory::clean()
{
	MemoryChunk* p;

	p = m_freeChunk;
	while (p)
	{
		MemoryChunk* current = p;
		p = p->next;

		free(current->ptr);
		POOL(MemoryChunk)->deallocate(current);
	}
	m_freeChunk = NULL;

	// We will not free pointers of used chunks
	p = m_usedChunk;
	while (p)
	{
		MemoryChunk* current = p;
		p = p->next;

		POOL(MemoryChunk)->deallocate(current);
	}
	m_usedChunk = NULL;
}

int RecyclingMemory::resizeArray(void** old, int oldSize, int newSize, int elemSize)
{
	if (newSize <= oldSize)
	{
		return oldSize;
	}

	void* newArray = allocate(newSize * elemSize);
	if (oldSize > 0)
	{
		memcpy(newArray, *old, oldSize * elemSize);
	}
	recycle(*old);
	*old = newArray;

	return newSize;
}
