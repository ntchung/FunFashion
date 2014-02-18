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

String* String::create(bool isAutoRelease)
{
	String* ptr = new(true) String();
	if (isAutoRelease)
	{
		ptr->autorelease();
	}
	return ptr;
}

String* String::create(const char* value, bool isAutoRelease)
{
	String* ptr = new(true) String(value);
	if (isAutoRelease)
	{
		ptr->autorelease();
	}
	return ptr;
}

String* String::create(const String& value, bool isAutoRelease)
{
	String* ptr = new(true) String(value);
	if (isAutoRelease)
	{
		ptr->autorelease();
	}
	return ptr;
}

void String::destroy()
{
	this->~String();
	POOL(String)->deallocate(this);
}

String::String()
{
	initString();
}

String::String(const char* value)
{
	initString();
	setString(value);
}

String::String(const String& value)
{
	initString();
	setString(value.m_data);
}

String::~String()
{
	s_stringsPool->get(m_dataCapacity)->deallocate(m_data);
}

unsigned short* String::getData() const
{
	return m_data;
}

unsigned int String::length() const
{
	return m_stringLength;
}

void String::initString() 
{
	m_stringLength = 0;
	m_dataCapacity = s_stringsPool->getMinimalCapacity(0);
	m_data = (unsigned short*)s_stringsPool->get(m_dataCapacity)->allocate();
}

void String::appendString(const char *str) 
{
	int len = str ? strlen(str) : 0;
	if (len) {
		if (m_stringLength) 
		{
			requestMoreData(m_stringLength + len + 1);

			unsigned short* ptr = m_data + m_stringLength;
			for (int i = 0; i < len; ++i)
			{
				ptr[i] = str[i];
			}
			m_stringLength += len;
			m_data[m_stringLength] = 0;
		}
		else 
		{
			setString(str);
		}
	}
}

void String::appendString(const unsigned short *str)
{
	int len = str ? wstrlen(str) : 0;
	if (len) {
		if (m_stringLength)
		{
			requestMoreData(m_stringLength + len + 1);

			memcpy(m_data + m_stringLength, str, len * sizeof(unsigned short));			
			m_stringLength += len;
			m_data[m_stringLength] = 0;
		}
		else
		{
			setString(str);
		}
	}
}

void String::setString(const char *str) 
{
	int len = str ? strlen(str) : 0;

	if (len)
	{
		requestNewData(len);

		for (int i = 0; i < len; ++i)
		{
			m_data[i] = str[i];
		}
		m_stringLength = len;
	}
	else
	{
		empty();
	}
}

void String::setString(const unsigned short *str)
{
	int len = str ? wstrlen(str) : 0;
	if (len)
	{		
		requestNewData(len);

		memcpy(m_data, str, len * sizeof(unsigned short));
		m_stringLength = len;
	}
	else
	{
		empty();
	}
}

void String::empty() 
{
	if (m_stringLength) 
	{
		s_stringsPool->get(m_dataCapacity)->deallocate(m_data);
		initString();
	}
}

void String::requestNewData(int len)
{
	empty();

	m_dataCapacity = s_stringsPool->getMinimalCapacity((len + 1) * sizeof(unsigned short));
	m_data = (unsigned short*)s_stringsPool->get(m_dataCapacity)->allocate();
	m_data[len] = 0;
}

void String::requestMoreData(int newLen)
{
	if (newLen*sizeof(unsigned short) > m_dataCapacity)
	{
		int newDataCapacity = s_stringsPool->getMinimalCapacity(newLen * sizeof(unsigned short));
		unsigned short* newData = (unsigned short*)s_stringsPool->get(newDataCapacity)->allocate();

		memcpy(newData, m_data, m_stringLength * sizeof(unsigned short));
		s_stringsPool->get(m_dataCapacity)->deallocate(m_data);

		m_data = newData;
		m_dataCapacity = newDataCapacity;
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

void String::append(const char* str, int index, int count)
{
	if (count) 
	{
		if (m_stringLength)
		{
			requestMoreData(m_stringLength + count + 1);
		}
		else
		{
			requestNewData(count);			
		}

		unsigned short* ptr = m_data + m_stringLength;
		for (int i = 0; i < count; ++i)
		{
			ptr[i] = str[index + i];
		}

		m_stringLength += count;
		m_data[m_stringLength] = 0;
	}
}

void String::trim()
{
	int i;
	int left = 0;
	for (i = 0; i < m_stringLength; ++i)
	{
		if (isSpace(m_data[i]))
		{
			left = i + 1;
			break;
		}
	}

	int right = m_stringLength;
	for (i = m_stringLength-1; i >= 0; --i)
	{
		if (isSpace(m_data[i]))
		{
			right = i;
			break;
		}
	}

	int len = right - left;
	if (len < m_stringLength)
	{
		subString(left, right - left);
	}
}

bool String::isSpace(unsigned short c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == 'v' || c == '\f');
}

void String::subString(int start)
{
	return subString(start, m_stringLength - start);
}

void String::subString(int start, int length)
{
	int i;
	for (i = 0; i < length; ++i)
	{
		m_data[i] = m_data[i + start];
	}

	m_stringLength = length;
}

bool String::startsWith(unsigned short c)
{
	return m_data[0] == c;
}

bool String::endsWith(unsigned short c)
{
	return m_data[m_stringLength - 1] == c;
}

void String::toUpper()
{
	for (int i = 0; i < m_stringLength; ++i)
	{
		unsigned short c = m_data[i];
		m_data[i] = (c < 'a' || c > 'z') ? c : (c - 'a') + 'A';
	}
}

void String::toLower()
{
	for (int i = 0; i < m_stringLength; ++i)
	{
		unsigned short c = m_data[i];
		m_data[i] = (c < 'A' || c > 'Z') ? c : (c - 'A') + 'a';
	}
}

bool String::equals(const char* value)
{
	int len = strlen(value);
	if (m_stringLength != len)
	{
		return false;
	}

	for (int i = 0; i < len; ++i)
	{
		if (m_data[i] != value[i])
		{
			return false;
		}
	}

	return true;
}

List<String>* String::split(const unsigned short* separator, int separatorCount)
{
	List<String>* res = List<String>::create();

	List<int> split_points;

	if (separator == NULL)
	{
		unsigned short* src_ptr = m_data;
		int len = m_stringLength;

		while (len > 0) 
		{
			if (isspace(*src_ptr++)) 
			{
				split_points.add(m_stringLength - len);
			}
			--len;
		}		
	}
	else 
	{
		unsigned short* src_ptr = m_data;
		unsigned short* sep_src = (unsigned short*)separator;				
		unsigned short* sep_ptr_end = sep_src + separatorCount;

		int len = m_stringLength;
		while (len > 0) 
		{
			unsigned short* sep_ptr = sep_src;
			do 
			{
				if (*sep_ptr++ == *src_ptr) 
				{					
					split_points.add(m_stringLength - len);					
				}
			} 
			while (sep_ptr != sep_ptr_end);

			++src_ptr;
			--len;
		}			
	}

	if (split_points.count() == 0)
	{
		res->add(*this);
		return res;
	}
	
	int prev_index = 0;
	int i = 0;
	for (; i < split_points.count(); ++i)
	{
		int start = split_points[i];

		String str(*this);
		str.subString(prev_index, start - prev_index);
		res->add(str);

		prev_index = start + 1;
	}

	String str(*this);
	str.subString(prev_index, m_stringLength - prev_index);
	res->add(str);

	return res;
}
