#ifndef __OBJECTSPOOL_H__
#define __OBJECTSPOOL_H__

#include "utils/SharedObject.h"
#include "MemoryPool.h"

class ObjectsPool : public SharedObject
{
public:
	ObjectsPool(int min = 16, int max = 1024);
	~ObjectsPool();
	virtual void destroy();

	static ObjectsPool* shared();

	MemoryPool* get(int size);
	int getMinimalCapacity(int size) const;

private:
	MemoryPool** m_memoryPools;

	int m_min;
	int m_max;
	int m_poolsCount;
};

#define POOL(_type) ObjectsPool::shared()->get(sizeof(_type))
#define POOL_ALLOC(_type) (_type*)ObjectsPool::shared()->get(sizeof(_type))->allocate();
#define POOL_FREE(_type, _obj) ObjectsPool::shared()->get(sizeof(_type))->deallocate(_obj);

void* operator new(size_t sz, bool usePool);

#endif // __OBJECTSPOOL_H__
