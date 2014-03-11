#ifndef __SHAREDOBJECT_H__
#define __SHAREDOBJECT_H__

#include "utils/DynamicArray.h"

class List;

class SharedObject
{
public:
	SharedObject();
	virtual void destroy() = 0;

	void autorelease();
	void retain();
	void release();

	static void setup();
	static void autoReleaseGC();
	static void autoReleasePurge();	

	void setHashName(const char* name);
	inline void setHashName(unsigned int value) { m_hashName = value; }
	inline unsigned int hashName() const { return m_hashName; }

private:
	unsigned int m_hashName;
	int m_referenceCount;
	bool m_isAutoRelease;

	static DynamicArray<SharedObject*>* s_autoReleasePool;
	static DynamicArray<SharedObject*>* s_deletingPool;
	static bool s_isPurgingAutoReleasePool;
	bool commenceDestroy();
};

#endif // __SHAREDOBJECT_H__
