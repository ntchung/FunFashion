#include "stdafx.h"
#include <assert.h>
#include <string>

ObjectsPool* ByteArray::s_memoryPool = 0;

void ByteArray::setup()
{
	s_memoryPool = new ObjectsPool(MIN_STRING_LENGTH, MAX_STRING_LENGTH);
	s_memoryPool->autorelease();
	s_memoryPool->retain();
}

ByteArray* ByteArray::create(bool isAutoRelease)
{
	ByteArray* ptr = new(true) ByteArray();
	if (isAutoRelease)
	{
		ptr->autorelease();
	}
	return ptr;
}

ByteArray* ByteArray::create(const char* value, bool isAutoRelease)
{
	ByteArray* ptr = new(true) ByteArray(value);
	if (isAutoRelease)
	{
		ptr->autorelease();
	}
	return ptr;
}

void ByteArray::destroy()
{
	this->~ByteArray();
	POOL(ByteArray)->deallocate(this);
}

ByteArray::ByteArray()
{
	initString();
}

ByteArray::ByteArray(const char* value)
{
	initString();
	setString(value);
}

ByteArray::~ByteArray()
{
	s_memoryPool->get(m_dataCapacity)->deallocate(m_data);
}

char* ByteArray::cstr() const
{
	return m_data;
}

int ByteArray::length() const
{
	return m_stringLength;
}

void ByteArray::initString() 
{
	m_stringLength = 0;
	m_dataCapacity = s_memoryPool->getMinimalCapacity(0);
	m_data = (char*)s_memoryPool->get(m_dataCapacity)->allocate();
	m_data[0] = 0;
}

void ByteArray::append(const char *str)
{
	int len = str ? (int)strlen(str) : 0;
	if (len) {
		if (m_stringLength)
		{
			requestMoreData(m_stringLength + len);

			memcpy(m_data + m_stringLength, str, len);			
			m_stringLength += len;
			m_data[m_stringLength] = 0;
		}
		else
		{
			setString(str);
		}
	}
}

void ByteArray::setString(const char *str)
{
	int len = str ? (int)strlen(str) : 0;
	if (len)
	{		
		requestNewData(len);

		memcpy(m_data, str, len);
		m_data[len] = '\0';
		m_stringLength = len;
	}
	else
	{
		empty();
	}
}

void ByteArray::empty() 
{
	if (m_stringLength) 
	{
		s_memoryPool->get(m_dataCapacity)->deallocate(m_data);
		initString();
	}
}

void ByteArray::requestNewData(int len)
{
	int newCapacity = s_memoryPool->getMinimalCapacity(len + 1);
	if (newCapacity != m_dataCapacity)
	{
		empty();

		m_dataCapacity = newCapacity;
		m_data = (char*)s_memoryPool->get(m_dataCapacity)->allocate();
		m_data[len] = 0;
	}
}

void ByteArray::requestMoreData(int newLen)
{
	++newLen;
	if (newLen > m_dataCapacity)
	{
		int newDataCapacity = s_memoryPool->getMinimalCapacity(newLen);
		char* newData = (char*)s_memoryPool->get(newDataCapacity)->allocate();

		memcpy(newData, m_data, m_stringLength);
		s_memoryPool->get(m_dataCapacity)->deallocate(m_data);
		newData[m_stringLength] = 0;

		m_data = newData;
		m_dataCapacity = newDataCapacity;
	}
}

void ByteArray::append(const char* str, int index, int count)
{
	if (count) 
	{
		if (m_stringLength)
		{
			requestMoreData(m_stringLength + count);
		}
		else
		{
			requestNewData(count);			
		}

		memcpy(m_data + m_stringLength, str + index, count);
		
		m_stringLength += count;
		m_data[m_stringLength] = 0;
	}
}

void ByteArray::trim()
{
	int i;
	int left = 0;
	for (i = 0; i < m_stringLength; ++i)
	{
		if (!isSpace(m_data[i]))
		{
			left = i;
			break;
		}
	}

	int right = m_stringLength;
	for (i = m_stringLength-1; i >= 0; --i)
	{
		if (!isSpace(m_data[i]))
		{
			right = i + 1;
			break;
		}
	}

	int len = right - left;
	if (len < m_stringLength)
	{
		subString(left, len);
	}
}

bool ByteArray::isNumeric(char c)
{
	return !(c < '0' || c > '9');
}

bool ByteArray::isSpace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}

void ByteArray::subString(int start)
{
	return subString(start, m_stringLength - start);
}

void ByteArray::subString(int start, int length)
{
	int i;
	for (i = 0; i < length; ++i)
	{
		m_data[i] = m_data[i + start];
	}
	m_data[i] = '\0';

	m_stringLength = length;
}

int ByteArray::indexOf(char c)
{
	for (int i = 0; i < m_stringLength; ++i)
	{
		if (m_data[i] == c)
		{
			return i;
		}
	}

	return -1;
}

bool ByteArray::startsWith(char c)
{
	return m_data[0] == c;
}

bool ByteArray::endsWith(char c)
{
	return m_data[m_stringLength - 1] == c;
}

void ByteArray::toUpper()
{
	for (int i = 0; i < m_stringLength; ++i)
	{
		unsigned short c = m_data[i];
		m_data[i] = (c < 'a' || c > 'z') ? c : (c - 'a') + 'A';
	}
}

void ByteArray::toLower()
{
	for (int i = 0; i < m_stringLength; ++i)
	{
		char c = m_data[i];
		m_data[i] = (c < 'A' || c > 'Z') ? c : (c - 'A') + 'a';
	}
}

bool ByteArray::startsWith(const char* value)
{
	int len = (int)strlen(value);
	if (m_stringLength < len)
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

bool ByteArray::startsWithIgnoreCase(const char* value)
{
	int len = (int)strlen(value);
	if (m_stringLength < len)
	{
		return false;
	}

	for (int i = 0; i < len; ++i)
	{
		if (tolower(m_data[i]) != tolower(value[i]))
		{
			return false;
		}
	}

	return true;
}

bool ByteArray::equals(const char* value)
{
	int len = (int)strlen(value);
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

bool ByteArray::equalsIgnoreCase(const char* value)
{
	int len = (int)strlen(value);
	if (m_stringLength != len)
	{
		return false;
	}

	for (int i = 0; i < len; ++i)
	{
		if (lowerCase(m_data[i]) != lowerCase(value[i]))
		{
			return false;
		}
	}

	return true;
}

List* ByteArray::split(const char* separator, int separatorCount)
{
	List* res = List::create();

	Array<int> split_points;

	if (separator == NULL)
	{
		char* src_ptr = m_data;
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
		char* src_ptr = m_data;
		char* sep_src = (char*)separator;				
		char* sep_ptr_end = sep_src + separatorCount;

		int len = m_stringLength;
		while (len > 0) 
		{
			char* sep_ptr = sep_src;
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
		res->add(this);
		return res;
	}
	
	int prev_index = 0;
	int i = 0;
	for (; i < split_points.count(); ++i)
	{
		int start = split_points[i];

		ByteArray* str = ByteArray::create(m_data);
		str->subString(prev_index, start - prev_index);
		str->trim();
		if (str->length() > 0)
		{
			res->add(str);
		}

		prev_index = start + 1;
	}

	ByteArray* str = ByteArray::create(m_data);
	str->subString(prev_index, m_stringLength - prev_index);
	str->trim();
	if (str->length() > 0)
	{
		res->add(str);
	}

	return res;
}

int ByteArray::toInt() const
{
	int mul = 1;
	char c;
	int number = 0;

	for (int i = m_stringLength - 1; i >= 0; --i) 
	{
		c = m_data[i];
		if ((c >= '0') && (c <= '9')) 
		{
			number += (c - '0') * mul;
			mul *= 10;
		}
		else 
		{
			if (c == '.') 
			{
				number = 0;
				mul = 1;
			}
			else 
			{
				if ((c == '-') && (i == 0)) 
				{
					number = -number;
				}
				else 
				{
					return 0;
				}
			}
		}
	}

	return number;
}

float ByteArray::toFloat() const 
{
	int mul = 1;
	char c;
	int int_part = 0;
	float prec_part = 0;

	for (int i = m_stringLength - 1; i >= 0; --i) 
	{
		c = m_data[i];
		if ((c >= '0') && (c <= '9')) 
		{
			int_part += (c - '0') * mul;
			mul *= 10;
		}
		else 
		{
			if (c == '.') 
			{
				prec_part = (float)int_part / (float)mul;
				int_part = 0;
				mul = 1;
			}
			else 
			{
				if ((c == '-') && (i == 0)) 
				{
					int_part = -int_part;
					prec_part = -prec_part;
				}
				else 
				{
					return 0;
				}
			}
		}
	}
	return int_part + prec_part;
}

char ByteArray::upperCase(char c)
{
	return (c < 'a' || c > 'z') ? c : (c - 'a') + 'A';
}

char ByteArray::lowerCase(char c)
{
	return (c < 'A' || c > 'Z') ? c : (c - 'A') + 'a';
}
