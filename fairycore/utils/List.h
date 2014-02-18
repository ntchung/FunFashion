#ifndef __LIST_H__
#define __LIST_H__

#include <string.h>
#include "utils/SharedObject.h"
#include "utils/ObjectsPool.h"
#include "utils/FairyMacros.h"

template <class T, int initCapacity = 16> class List : public SharedObject
{
public:	
	static List* create(bool isAutoRelease = true)
	{
		List* ptr = new(true) List();
		if (isAutoRelease)
		{
			ptr->autorelease();
		}
		return ptr;
	}

	virtual void destroy()
	{
		this->~List();
		POOL(List)->deallocate(this);
	}

	List()
	{
		reset(initCapacity);
	}

	~List()
	{
		m_usingMemoryPool->deallocate(m_array);
	}
	
	void reset(int initCapacity)
	{
		initCapacity = max(initCapacity, 4);
		
		m_capacity = initCapacity;
		m_count = 0;

		m_usingMemoryPool = ObjectsPool::shared()->get(m_capacity * sizeof(T));
		m_array = (T*)m_usingMemoryPool->allocate();
	}

	inline void clear()
	{
		m_count = 0;
	}

	inline void add(const T& elem)
	{
		if (m_count == m_capacity)
		{
			expand(m_capacity + 1);
		}

		m_array[m_count++] = elem;
	}
	
	inline bool contains(T& elem)
	{
		for (int i = 0; i < m_count; ++i)
		{
			if (m_array[i] == elem)
			{
				return true;
			}
		}

		return false;
	}

	inline T& get(int index)
	{
		return m_array[index];
	}

	inline T& operator[](int index)
	{
		return m_array[index];
	}

	inline int count()
	{
		return m_count;
	}

	inline void removeAt(int index)
	{
		m_array[index] = m_array[--m_count];
	}

	inline T& pop()
	{
		return m_array[--m_count];
	}

private:
	T* m_array;
	int m_capacity;
	int m_count;

	MemoryPool* m_usingMemoryPool;	

	void expand(int num)
	{
		int newCapacity = ObjectsPool::shared()->getMinimalCapacity(m_capacity + num);
		if (newCapacity > m_capacity)
		{
			MemoryPool* newMemoryPool = ObjectsPool::shared()->get(newCapacity);
			T* newArray = (T*)newMemoryPool->allocate();

			memcpy(newArray, m_array, sizeof(T)* m_count);
			m_usingMemoryPool->deallocate(m_array);

			m_array = newArray;
			m_capacity = newCapacity;
			m_usingMemoryPool = newMemoryPool;
		}
	}
};

#endif // __LIST_H__
