#include "stdafx.h"

struct PVRHeader
{
	unsigned int HeaderLength;
	unsigned int Height;
	unsigned int Width;
	unsigned int NumMipmaps;
	unsigned int Flags;
	unsigned int DataLength;
	unsigned int BitsPerPixel;
	unsigned int BitmaskRed;
	unsigned int BitmaskGreen;
	unsigned int BitmaskBlue;
	unsigned int BitmaskAlpha;
	char PVRTag[4];
	unsigned int NumSurfs;
};

Texture* Texture::create()
{
	return new(true) Texture();
}

Texture* Texture::create(char* data, int length)
{
	return new(true) Texture(data, length);
}

void Texture::destroy()
{
	this->~Texture();
	POOL(Texture)->deallocate(this);
}

Texture::Texture()
: m_hashName(0)
, m_glName(0)
{
}

Texture::~Texture()
{
	if (m_glName)
	{
		glDeleteTextures(1, &m_glName);
	}
}

void Texture::setName(const char* name)
{
	m_hashName = String::makeHash(name);
}

Texture::Texture(char* data, int length)
{
	if (m_glName)
	{
		glDeleteTextures(1, &m_glName);
		m_glName = 0;
	}

	glGenTextures(1, &m_glName);

	MemoryStream* stream = MemoryStream::create(data, length);

	int texType;
	int _width, _height;

	PVRHeader header;
	stream->read((char*)&header, 0, sizeof(PVRHeader));
	
	stream->close();
}
