#ifndef __STREAMREADER_H__
#define __STREAMREADER_H__

#include "utils/SharedObject.h"
#include "utils/Stream.h"

class StreamReader : public SharedObject
{
public:	
	static StreamReader* create(Stream* input);
	virtual void destroy();

	bool endOfStream();
	void close();

	int peek();
	int read();
	int read(char* buffer, int index, int count);



private:
	StreamReader(Stream* input);
	~StreamReader();

	Stream* m_baseStream;
};

#endif // __STREAMREADER_H__
