#ifndef __BYTEARRAY_H__
#define __BYTEARRAY_H__

#include "utils/SharedObject.h"
#include "utils/ObjectsPool.h"
#include "utils/List.h"

class ByteArray : public SharedObject
{
public:
	static ByteArray* create(bool isAutoRelease = true);
	static ByteArray* create(const char* value, bool isAutoRelease = true);
	virtual void destroy();

	static void setup();

	void empty();
	char* cstr() const;
	int length() const;

	void append(const char* str, int index, int count);
	void append(const char *str);
	void trim();
	void toUpper();
	void toLower();
	void subString(int start);
	void subString(int start, int length);

	bool startsWith(char c);
	bool endsWith(char c);
	bool startsWith(const char* value);
	bool equals(const char* value);
	bool equalsIgnoreCase(const char* value);

	List* split(const char* separator, int separatorCount);

	int toInt() const;
	float toFloat() const;

	static bool isSpace(char c);
	static bool isNumeric(char c);
	static char upperCase(char c);
	static char lowerCase(char c);

private:
	ByteArray();
	ByteArray(const char* value);
	~ByteArray();

	char *m_data;
	int m_stringLength;
	int m_dataCapacity;

	void initString();	
	void setString(const char *str);
	
	void requestNewData(int len);
	void requestMoreData(int newLen);

	static ObjectsPool* s_memoryPool;
};

#endif // __BYTEARRAY_H__
