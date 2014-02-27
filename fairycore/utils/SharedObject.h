#ifndef __SHAREDOBJECT_H__
#define __SHAREDOBJECT_H__

#include "utils/DynamicArray.h"

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

private:
	int m_referenceCount;
	bool m_isAutoRelease;

	static DynamicArray<SharedObject*>* s_autoReleasePool;
	static DynamicArray<SharedObject*>* s_deletingPool;
	static bool s_isPurgingAutoReleasePool;
	bool commenceDestroy();
};

#endif // __SHAREDOBJECT_H__
