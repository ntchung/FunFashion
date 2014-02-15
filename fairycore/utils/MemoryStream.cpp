#include "stdafx.h"

MemoryStream* MemoryStream::create(char* data, int length, bool isAutoRelease)
{
	MemoryStream* ptr = new(true) MemoryStream(data, length);
	if (isAutoRelease)
	{
		ptr->autorelease();
	}

	return ptr;
}

void MemoryStream::destroy()
{
	this->~MemoryStream();
	POOL(MemoryStream)->deallocate(this);
}

MemoryStream::MemoryStream(char* data, int length)
: m_data(data)
, m_dataPtr(data)
{
	setLength(length);
}

MemoryStream::~MemoryStream()
{
}

void MemoryStream::close()
{
}

int MemoryStream::getPosition()
{
	return (int)( m_dataPtr - m_data );
}

void MemoryStream::setPosition(int value)
{
	m_dataPtr = (char*)( m_data + value );
}

void MemoryStream::flush()
{
}

int MemoryStream::readByte()
{
	return (m_dataPtr < m_dataPtrEnd) ? *(m_dataPtr++) : -1;
}

int MemoryStream::read(char* buffer, int index, int count)
{
	if ((char*)(m_dataPtr + count) >= m_dataPtrEnd)
	{
		count = (int)(m_dataPtrEnd - m_dataPtr);
	}

	if (count > 0)
	{
		memcpy((char*)(buffer + index), m_dataPtr, count);
		m_dataPtr += count;
	}
	return count;
}

int MemoryStream::length()
{
	return m_length;
}

void MemoryStream::setLength(int value)
{
	m_length = value;
	m_dataPtrEnd = (char*)(m_data + m_length);
}
