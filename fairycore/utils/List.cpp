#include "stdafx.h"

List* List::create(bool isAutoRelease)
{
	List* ptr = new(true) List();
	if (isAutoRelease)
	{
		ptr->autorelease();
	}
	return ptr;
}

void List::destroy()
{
	this->~List();
	POOL(List)->deallocate(this);
}

List::List()
{
	reset(16);
}

List::~List()
{
	clear();
	m_usingMemoryPool->deallocate(m_array);
}

void List::reset(int initCapacity)
{
	initCapacity = max(initCapacity, 4);

	m_capacity = 128;
	m_count = 0;

	m_usingMemoryPool = ObjectsPool::shared()->get(m_capacity * sizeof(SharedObject*));
	m_array = (SharedObject**)m_usingMemoryPool->allocate();
}

void List::clear()
{
	for (int i = 0; i < m_count; ++i)
	{
		m_array[i]->release();		
	}
	m_count = 0;
}

void List::add(SharedObject* elem)
{
	if (m_count == m_capacity)
	{
		expand(m_capacity + 1);
	}

	elem->retain();
	m_array[m_count++] = elem;
}

bool List::contains(SharedObject* elem)
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

SharedObject* List::get(int index)
{
	return m_array[index];
}

SharedObject* List::operator[](int index)
{
	return m_array[index];
}

void List::removeAt(int index)
{
	m_array[index]->release();
	m_array[index] = m_array[--m_count];
}

void List::expand(int num)
{
	int newSize = ObjectsPool::shared()->getMinimalCapacity((m_capacity + num) * sizeof(SharedObject*));
	if (newSize > m_capacity * sizeof(SharedObject*))
	{
		MemoryPool* newMemoryPool = ObjectsPool::shared()->get(newSize);
		SharedObject** newArray = (SharedObject**)newMemoryPool->allocate();

		memcpy(newArray, m_array, sizeof(SharedObject*) * m_count);
		m_usingMemoryPool->deallocate(m_array);

		m_array = newArray;
		m_capacity = newSize / sizeof(SharedObject*);
		m_usingMemoryPool = newMemoryPool;
	}
}
