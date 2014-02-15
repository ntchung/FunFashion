#ifndef __STRING_H__
#define __STRING_H__

#include "utils/SharedObject.h"
#include "utils/ObjectsPool.h"

class String : public SharedObject
{
public:
	static String* create(bool isAutoRelease = true);
	static String* create(const char* value, bool isAutoRelease = true);
	static String* create(const String& value, bool isAutoRelease = true);
	virtual void destroy();

	static void setup();

	void empty();
	unsigned short* getData() const;
	unsigned int length() const;

	void append(const char* str, int index, int count);
	void trim();
	void toUpper();
	void toLower();
	void subString(int start);
	void subString(int start, int length);

	bool startsWith(unsigned short c);
	bool endsWith(unsigned short c);
	bool equals(const char* value);

	static bool isSpace(unsigned short c);

private:
	String();
	String(const char* value);
	String(const String& value);
	~String();

	unsigned short *m_data;
	unsigned int m_stringLength;
	unsigned int m_dataCapacity;

	void initString();
	void appendString(const unsigned short *str);
	void setString(const unsigned short *str);
	void appendString(const char *str);
	void setString(const char *str);
	
	void requestNewData(int len);
	void requestMoreData(int newLen);

	static ObjectsPool* s_stringsPool;
	static int wstrlen(const unsigned short* str);
};

#endif // __STRING_H__
