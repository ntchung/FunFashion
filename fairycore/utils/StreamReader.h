#ifndef __STREAMREADER_H__
#define __STREAMREADER_H__

#include "utils/SharedObject.h"
#include "utils/Stream.h"
#include "utils/String.h"
#include "utils/ByteArray.h"

class StreamReader : public SharedObject
{
public:	
	static StreamReader* create(Stream* input, bool isAutoRelease = true);
	virtual void destroy();

	bool endOfStream();
	void close();

	int read();

	int peek();
	String* readLine();
	String* readToEnd();

	ByteArray* readLineToBytes();

private:
	StreamReader(Stream* input);
	~StreamReader();

	Stream* m_baseStream;
	int m_streamReadPosition;

	char* m_charBuffer;
	int m_charPos;
	int m_charLength;
	bool m_isEOF;

	int readBuffer();
};

#endif // __STREAMREADER_H__
