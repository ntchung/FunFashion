#include "stdafx.h"

MemoryStream* MemoryStream::create(const char* data)
{
	return new(true) MemoryStream(data);
}

void MemoryStream::destroy()
{
	this->~MemoryStream();
	POOL(MemoryStream)->deallocate(this);
}

MemoryStream::MemoryStream(const char* data)
{
}

MemoryStream::~MemoryStream()
{
}
