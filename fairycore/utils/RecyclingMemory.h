#ifndef __RECYCLINGMEMORY_H__
#define __RECYCLINGMEMORY_H__

#include "utils/SharedObject.h"

class RecyclingMemory : public SharedObject
{
public:
	static RecyclingMemory* shared();
	virtual void destroy();

	void recycle(void* data);
	void* allocate(int size);

	void clean();

private:
	RecyclingMemory();
	~RecyclingMemory();

	struct MemoryChunk
	{
		void* ptr;
		int capacity;
		MemoryChunk* next;
	};

	MemoryChunk* m_freeChunk;
	MemoryChunk* m_usedChunk;
};

#endif // __RECYCLINGMEMORY_H__
