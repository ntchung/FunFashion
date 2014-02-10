#include "stdafx.h"
#include <assert.h>
#include <string>

ObjectsPool* String::s_stringsPool = 0;

void String::setup()
{
	s_stringsPool = new ObjectsPool(MIN_STRING_LENGTH, MAX_STRING_LENGTH);
	s_stringsPool->autorelease();
	s_stringsPool->retain();
}

String* String::create()
{
	return new(true) String();
}

String* String::create(const char* value)
{
	return new(true) String(value);
}

String* String::create(const String& value)
{
	return new(true) String(value);
}

void String::destroy()
{
	this->~String();
	POOL(String)->deallocate(this);
}

String::String()
{
	InitString();
}

String::String(const char* value)
{
	InitString();
	SetString(value);
}

String::String(const String& value)
{
	InitString();
	SetString(value.Data);
}

String::~String()
{
	
}

unsigned int String::Length() const
{
	return StringLength;
}

void String::InitString() 
{
	Data = NULL;
	StringLength = 0;
	DataCapacity = 0;
}

void String::AppendString(const char *str) 
{
	int len = str ? strlen(str) : 0;
	if (len) {
		if (StringLength) 
		{
			requestMoreData(StringLength + len + 1);

			unsigned short* ptr = Data + StringLength;
			for (int i = 0; i < len; ++i)
			{
				ptr[i] = str[i];
			}
			StringLength += len;
			Data[StringLength] = 0;
		}
		else 
		{
			SetString(str);
		}
	}
}

void String::AppendString(const unsigned short *str)
{
	int len = str ? wstrlen(str) : 0;
	if (len) {
		if (StringLength)
		{
			requestMoreData(StringLength + len + 1);

			memcpy(Data + StringLength, str, len * sizeof(unsigned short));			
			StringLength += len;
			Data[StringLength] = 0;
		}
		else
		{
			SetString(str);
		}
	}
}

void String::SetString(const char *str) 
{
	StringLength = str ? strlen(str) : 0;

	if (StringLength)
	{	
		requestNewData(StringLength);

		for (int i = 0; i < StringLength; ++i)
		{
			Data[i] = str[i];
		}
	}
	else
	{
		Empty();
	}
}

void String::SetString(const unsigned short *str)
{
	StringLength = str ? wstrlen(str) : 0;
	if (StringLength)
	{		
		requestNewData(StringLength);

		memcpy(Data, str, StringLength * sizeof(unsigned short));
	}
	else
	{
		Empty();
	}
}

void String::Empty() 
{
	if (StringLength) 
	{
		s_stringsPool->get(DataCapacity)->deallocate(Data);
		InitString();
	}
}

void String::requestNewData(int len)
{
	Empty();

	DataCapacity = s_stringsPool->getMinimalCapacity((len + 1) * sizeof(unsigned short));
	Data = (unsigned short*)s_stringsPool->get(DataCapacity)->allocate();
	Data[len] = 0;
}

void String::requestMoreData(int newLen)
{
	if (newLen*sizeof(unsigned short) > DataCapacity)
	{
		int newDataCapacity = s_stringsPool->getMinimalCapacity(newLen * sizeof(unsigned short));
		unsigned short* newData = (unsigned short*)s_stringsPool->get(newDataCapacity)->allocate();

		memcpy(newData, Data, StringLength * sizeof(unsigned short));
		s_stringsPool->get(DataCapacity)->deallocate(Data);

		Data = newData;
		DataCapacity = newDataCapacity;
	}
}

int String::wstrlen(const unsigned short* str)
{
	int res = 0;
	while (*str++)
	{
		++res;
	}
	return res;
}
