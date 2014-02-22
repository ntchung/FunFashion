#ifndef __LIST_H__
#define __LIST_H__

#include <string.h>
#include "utils/SharedObject.h"
#include "utils/ObjectsPool.h"
#include "utils/FairyMacros.h"

class List : public SharedObject
{
public:	
	static List* create(bool isAutoRelease = true);
	virtual void destroy();	

	List();
	~List();		
	
	void clear();
	void add(SharedObject* elem);
	
	bool contains(SharedObject* elem);
	SharedObject* get(int index);

	SharedObject* operator[](int index);
	
	inline int count()
	{
		return m_count;
	}

	void removeAt(int index);
	
private:
	SharedObject** m_array;
	int m_capacity;
	int m_count;

	MemoryPool* m_usingMemoryPool;	

	void expand(int num);
	void reset(int initCapacity);
};

#endif // __LIST_H__
