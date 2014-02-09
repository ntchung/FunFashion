#include "stdafx.h"

StreamReader* StreamReader::create(Stream* input)
{
	return new(true) StreamReader(input);
}

void StreamReader::destroy()
{
	POOL(StreamReader)->deallocate(this);
}

bool StreamReader::endOfStream()
{
	return false;
}

void StreamReader::close()
{

}

StreamReader::StreamReader(Stream* input)
: m_baseStream(input)
{

}

StreamReader::~StreamReader()
{

}

