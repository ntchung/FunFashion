#ifndef __STRING_H__
#define __STRING_H__

#include "utils/SharedObject.h"
#include "utils/ObjectsPool.h"

class String : public SharedObject
{
public:
	static String* create(const char* value);
	static String* create(String* value);
	virtual void destroy();

	static void setup();

private:
	String(const char* value);
	String(String* value);
	~String();

	char* m_value;
	int m_length;
	int m_capacity;

	static ObjectsPool* m_stringsPool;
};

#endif // __STRING_H__
