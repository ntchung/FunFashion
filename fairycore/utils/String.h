#ifndef __STRING_H__
#define __STRING_H__

#include "utils/SharedObject.h"
#include "utils/ObjectsPool.h"
#include "utils/List.h"

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
	int length() const;

	char* toCharArray(char* str) const;

	String* clone();

	void append(const char* str, int index, int count);
	void append(const unsigned short *str);
	void append(const char *str);
	void trim();
	void toUpper();
	void toLower();
	void subString(int start);
	void subString(int start, int length);

	bool startsWith(unsigned short c);
	bool endsWith(unsigned short c);
	bool startsWith(const char* value);
	bool equals(const char* value);
	bool equalsIgnoreCase(const char* value);

	List* split(const unsigned short* separator, int separatorCount);

	int toInt() const;
	float toFloat() const;

	static bool isSpace(unsigned short c);
	static bool isNumeric(unsigned short c);
	static unsigned short upperCase(unsigned short c);
	static unsigned short lowerCase(unsigned short c);

	static unsigned int makeHash(const char* str);

private:
	String();
	String(const char* value);
	String(const String& value);
	~String();

	unsigned short *m_data;
	int m_stringLength;
	int m_dataCapacity;

	void initString();	
	void setString(const unsigned short *str);	
	void setString(const char *str);
	
	void requestNewData(int len);
	void requestMoreData(int newLen);

	static ObjectsPool* s_stringsPool;
	static int wstrlen(const unsigned short* str);
};

#endif // __STRING_H__
