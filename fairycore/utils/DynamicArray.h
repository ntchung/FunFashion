#ifndef __DYNAMICARRAY_H__
#define __DYNAMICARRAY_H__

#include <string.h>
#include "utils/FairyMacros.h"

template <class T, int initialCapacity = 32> class DynamicArray
{
public:
	DynamicArray()		
	{		
		reset(initialCapacity);
	}

	~DynamicArray()
	{
		delete[] m_array;
	}
	
	void reset(int initCapacity)
	{
		initCapacity = max(initCapacity, 32);
		
		m_size = initCapacity;
		m_count = 0;
		m_step = m_size;
		m_array = new T[m_size];
	}

	inline void clear()
	{
		m_count = 0;
	}

	inline void add(const T& elem)
	{
		if (m_count == m_size)
		{
			T* newArray = new T[m_size + m_step];
			memcpy(newArray, m_array, sizeof(T)* m_size);
			delete[] m_array;

			m_array = newArray;
			m_size += m_step;
		}

		m_array[m_count++] = elem;
	}
	
	inline bool contains(const T& elem)
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

	inline void removeTail()
	{
		--m_count;
	}

	inline T& pop()
	{
		return m_array[--m_count];
	}

private:
	T* m_array;
	int m_size;
	int m_count;
	int m_step;
};

#endif // __DYNAMICARRAY_H__
