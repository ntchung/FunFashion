#include "stdafx.h"
#include <string>

ObjectsPool* String::m_stringsPool = 0;

void String::setup()
{
	m_stringsPool = new ObjectsPool(MIN_STRING_LENGTH, MAX_STRING_LENGTH);
	m_stringsPool->autorelease();
	m_stringsPool->retain();
}

String* String::create(const char* value)
{
	return new(true) String(value);
}

String* String::create(String* value)
{
	return new(true) String(value);
}

void String::destroy()
{
	this->~String();
	POOL(String)->deallocate(this);
}

String::String(const char* value)
{
	int len = strlen(value);
	m_value = (char*)m_stringsPool->get(len)->allocate();
	m_capacity = m_stringsPool->getMinimalCapacity(len);
	m_length = len;

	memset(m_value, 0, m_capacity);
	memcpy(m_value, value, m_length);
}

String::String(String* value)
{

}

String::~String()
{
	m_stringsPool->get(m_capacity)->deallocate(m_value);
}
