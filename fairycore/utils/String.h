#ifndef __STRING_H__
#define __STRING_H__

#include "utils/SharedObject.h"
#include "utils/ObjectsPool.h"

class String : public SharedObject
{
public:
	static String* create();
	static String* create(const char* value);
	static String* create(const String& value);
	virtual void destroy();

	static void setup();

	void Empty();

	const char* ToConstCharPtr() const;

	unsigned int Length() const;

private:
	String();
	String(const char* value);
	String(const String& value);
	~String();

	unsigned short *Data;
	unsigned int StringLength;
	unsigned int DataCapacity;

	void InitString();
	void AppendString(const unsigned short *str);
	void SetString(const unsigned short *str);
	void AppendString(const char *str);
	void SetString(const char *str);
	
	void requestNewData(int len);
	void requestMoreData(int newLen);

	static ObjectsPool* s_stringsPool;
	static int wstrlen(const unsigned short* str);
};

#endif // __STRING_H__
