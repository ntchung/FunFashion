#ifndef __STREAM_H__
#define __STREAM_H__

#include "utils/SharedObject.h"

class Stream : public SharedObject
{
public:
	virtual void close() = 0;

	virtual int getPosition() = 0;
	virtual void setPosition(int value) = 0;
	virtual void flush() = 0;

	virtual int readByte() = 0;
	virtual int read(char* buffer, int index, int count) = 0;

	virtual int length() = 0;
	virtual void setLength(int value) = 0;
};

#endif // __STREAM_H__
