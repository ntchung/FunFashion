#ifndef __MEMORYSTREAM_H__
#define __MEMORYSTREAM_H__

#include "utils/Stream.h"

class MemoryStream : public Stream
{
public:	
	static MemoryStream* create(const char* data);
	virtual void destroy();

private:
	MemoryStream(const char* data);
	~MemoryStream();
};

#endif // __MEMORYSTREAM_H__
