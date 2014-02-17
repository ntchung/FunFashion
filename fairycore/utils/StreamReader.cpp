#include "stdafx.h"
#include <stdio.h>

static MemoryPool* g_readerBufferPool = NULL;

StreamReader* StreamReader::create(Stream* input, bool isAutoRelease)
{
	StreamReader* ptr = new(true) StreamReader(input);
	if (isAutoRelease)
	{
		ptr->autorelease();
	}

	return ptr;
}

void StreamReader::destroy()
{
	this->~StreamReader();
	POOL(StreamReader)->deallocate(this);
}

bool StreamReader::endOfStream()
{
	return m_isEOF;
}

void StreamReader::close()
{
	memset(m_charBuffer, 0, STREAM__BUFFER_SIZE);

	m_streamReadPosition = 0;
	m_charPos = 0;
	m_charLength = 0;
	m_isEOF = true;
}

StreamReader::StreamReader(Stream* input)
: m_baseStream(input)
, m_streamReadPosition( 0 )
, m_charPos( 0 )
, m_charLength( 0 )
, m_isEOF( false )
{
	if (!g_readerBufferPool)
	{
		g_readerBufferPool = ObjectsPool::shared()->get(STREAM__BUFFER_SIZE);
	}
	m_charBuffer = (char*)g_readerBufferPool->allocate();
	memset(m_charBuffer, 0, STREAM__BUFFER_SIZE);

	readBuffer();
}

StreamReader::~StreamReader()
{
	g_readerBufferPool->deallocate(m_charBuffer);
}

int StreamReader::peek()
{
	if (m_charPos == m_charLength)
	{
		readBuffer();
	}

	if (m_charLength < 1)
	{
		return -1;
	}

	return m_charBuffer[m_charPos];
}

int StreamReader::read()
{
	if (m_charPos == m_charLength)
	{
		readBuffer();
	}

	if (m_charLength < 1)
	{
		return -1;
	}

	return m_charBuffer[m_charPos++];
}

String* StreamReader::readLine()
{
	if (m_charPos == m_charLength)
	{
		if(readBuffer() == 0) return NULL;
	}

	String* pstr = String::create();
	
	do 
	{
		int i = m_charPos;
		do 
		{
			int ch = m_charBuffer[i];

			// Note the following common line feed chars:
			// \n - UNIX   \r\n - DOS   \r - Mac
			if (ch == '\r' || ch == '\n') 
			{
				pstr->append(m_charBuffer, m_charPos, i - m_charPos);
				
				m_charPos = i + 1;
				if (ch == '\r' && (m_charPos < m_charLength || readBuffer() > 0))
				{
					if (m_charBuffer[m_charPos] == '\n') m_charPos++;
				}

				return pstr;
			}
			i++;
		} while (i < m_charLength);

		i = m_charLength - m_charPos;
		pstr->append(m_charBuffer, m_charPos, i);
	} while (readBuffer() > 0);
	
	return pstr;
}

String* StreamReader::readToEnd()
{
	String* pstr = String::create();

	do
	{
		pstr->append(m_charBuffer, m_charPos, m_charLength - m_charPos);
		m_charPos = m_charLength;
		readBuffer();
	} while (m_charLength > 0);

	return pstr;
}

int StreamReader::readBuffer()
{	
	if (m_charPos > 0)
	{
		// truncate current buffer by removing old characters
		char* copyPtr = m_charBuffer + m_charPos;
		char* copyPtrEnd = m_charBuffer + m_charLength;
		while (copyPtr < copyPtrEnd)
		{
			*m_charBuffer++ = *copyPtr++;
		}
		m_charLength -= m_charPos;

		// read new charaters
		m_baseStream->setPosition(m_streamReadPosition);
		int readSize = m_baseStream->read(m_charBuffer, m_charLength, STREAM__BUFFER_SIZE - m_charLength - 1);
		m_streamReadPosition += readSize;

		// set buffer
		m_charLength += readSize;
		m_charPos = 0;
	}

	if (m_charLength < STREAM__BUFFER_SIZE - 1)
	{
		// read more charaters
		m_baseStream->setPosition(m_streamReadPosition);
		int readSize = m_baseStream->read(m_charBuffer, m_charLength, STREAM__BUFFER_SIZE - m_charLength - 1);
		m_streamReadPosition += readSize;
		m_charLength += readSize;
	}

	if (m_charLength < 1)
	{
		m_isEOF = true;
	}

	m_charBuffer[m_charLength] = '\0';
	return m_charLength;
}
