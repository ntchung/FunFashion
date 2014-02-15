#ifndef __MEMORYSTREAM_H__
#define __MEMORYSTREAM_H__

#include "utils/Stream.h"

class MemoryStream : public Stream
{
public:	
	static MemoryStream* create(char* data, int length, bool isAutoRelease = true);
	virtual void destroy();

	virtual void close();
	virtual int getPosition();
	virtual void setPosition(int value);
	virtual void flush();

	virtual int readByte();
	virtual int read(char* buffer, int index, int count);

	virtual int length();
	virtual void setLength(int value);	

protected:
	MemoryStream(char* data, int length);
	~MemoryStream();

	char* m_data;
	char* m_dataPtr;
	char* m_dataPtrEnd;

	int m_length;
};

#endif // __MEMORYSTREAM_H__
