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

Texture* Texture::create(int width, int height, GLenum filteringMode, GLenum wrapMode, GLenum internalFormat, bool isAutoRelease)
{
	Texture* ptr = new(true) Texture(width, height, filteringMode, wrapMode, internalFormat);
	if (isAutoRelease)
	{
		ptr->autorelease();
	}

	return ptr;
}

Texture* Texture::create(char* data, int length, bool isAutoRelease)
{
	Texture* ptr = new(true) Texture(data, length);
	if (isAutoRelease)
	{
		ptr->autorelease();
	}

	return ptr;
}

void Texture::destroy()
{
	this->~Texture();
	POOL(Texture)->deallocate(this);
}

Texture::Texture()
: m_glName(0)
, m_width(0)
, m_height(0)
, m_dataType(NO_MIPMAP)
, m_wrapMode(GL_REPEAT)
, m_filteringMode(GL_LINEAR)
{
}

Texture::Texture(int width, int height, GLenum filteringMode, GLenum wrapMode, GLenum internalFormat)
: m_width(width)
, m_height(height)
, m_wrapMode(wrapMode)
, m_filteringMode(filteringMode)
{
	m_dataType = internalFormat == GL_RGBA ? MUTABLE_RGBA : MUTABLE_ALPHA;

	//int oldAlignment = 1;
	//glGetIntegerv( GL_UNPACK_ALIGNMENT, &oldAlignment );
	//glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	glGenTextures(1, &m_glName);
	glBindTexture(GL_TEXTURE_2D, m_glName);

	//unsigned char* textureData = new unsigned char[info.width * info.height];
	//memset(textureData, 0, info.width * info.height);

	GLenum format = m_dataType == MUTABLE_RGBA ? GL_RGBA : GL_ALPHA;
	glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, 0);	
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filteringMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filteringMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapMode);

	// delete[] textureData;

	//glPixelStorei( GL_UNPACK_ALIGNMENT, oldAlignment );	
}

Texture::~Texture()
{
	if (m_glName)
	{
		glDeleteTextures(1, &m_glName);
	}
}

void Texture::setData(int x, int y, int w, int h, void* data)
{
	GLenum format = m_dataType == MUTABLE_RGBA ? GL_RGBA : GL_ALPHA;

	GLint oldAlignment = 1;
	glGetIntegerv(GL_UNPACK_ALIGNMENT, &oldAlignment);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glBindTexture(GL_TEXTURE_2D, m_glName);
	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, format, GL_UNSIGNED_BYTE, data);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);	

	glPixelStorei(GL_UNPACK_ALIGNMENT, oldAlignment);
}

void Texture::setData(void* data)
{
	setData(0, 0, m_width, m_height, data);
}

Texture::Texture(char* data, int length)
{
	if (m_glName)
	{
		glDeleteTextures(1, &m_glName);
		m_glName = 0;
	}

	int _width, _height;

	data += 4; // Magik 'TEXT'	
	m_wrapMode = data[4] == 'C' ? GL_CLAMP_TO_EDGE : GL_REPEAT;
	m_filteringMode = data[5] == 'B' ? GL_LINEAR : GL_NEAREST;
	data += 2;

	PVRHeader header = *((PVRHeader*)data);

	GLenum internalFormat;
	GLenum pixelFormat;
	GLenum pixelType = GL_UNSIGNED_BYTE;
	bool isCompressed = false;

	unsigned int format = header.Flags & 0xff;
	unsigned int blockSizeX = 1;
	unsigned int blockSizeY = 1;
	unsigned int minBlocks = 1;

	_width = header.Width;
	_height = header.Height;

	long imageSize = (_width * _height) << 2;

	char* buffer = data + sizeof(PVRHeader);

	// Format values taken from PVRTexLib
	switch (format)
	{
		case 0x10: // OGL_RGBA_4444

			internalFormat = pixelFormat = GL_RGBA;
			pixelType = GL_UNSIGNED_SHORT_4_4_4_4;
			break;


		case 0x11: // OGL_RGBA_5551

			internalFormat = pixelFormat = GL_RGBA;
			pixelType = GL_UNSIGNED_SHORT_5_5_5_1;
			break;


		case 0x12: // OGL_RGBA_8888
			internalFormat = pixelFormat = GL_RGBA;
			break;

		case 0x13: // OGL_RGB_565
			internalFormat = pixelFormat = GL_RGB;
			pixelType = GL_UNSIGNED_SHORT_5_6_5;
			break;

		case 0x15: // OGL_RGB_888
			internalFormat = pixelFormat = GL_RGB;
			break;

		case 0x16: // OGL_I_8
			internalFormat = pixelFormat = GL_LUMINANCE;
			break;

		case 0x17: // OGL_AI_88
			internalFormat = pixelFormat = GL_LUMINANCE_ALPHA;
			break;

		case 0x36: // ETC

			isCompressed = true;
			internalFormat = pixelFormat = GL_ETC1_RGB8_OES;
			break;

		default:
			internalFormat = pixelFormat = GL_RGBA;
			break;
	}

	// Transfer data to video		
	m_width = _width;
	m_height = _height;
	m_dataType = (internalFormat == GL_RGBA && pixelType == GL_UNSIGNED_BYTE) ? MUTABLE_RGBA : NO_MIPMAP;

	glGenTextures(1, &m_glName);

	glBindTexture(GL_TEXTURE_2D, m_glName);

	if (!isCompressed)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, _width, _height, 0, pixelFormat, pixelType, buffer);
	}
	else
	{
		// Calculate mipmap byte size based on 4x4 blocks, 8 bytes each
		GLuint size = 8 * ((_width + 3) >> 2) * ((_height + 3) >> 2);
		glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_ETC1_RGB8_OES, _width, _height, 0, size, buffer);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filteringMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filteringMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapMode);
}
