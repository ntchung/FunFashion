#include "stdafx.h"

Texture* Texture::create()
{
	return new(true) Texture();
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

void Texture::loadPVR(const char* fileName)
{
	if (m_glName)
	{
		glDeleteTextures(1, &m_glName);
		m_glName = 0;
	}

	m_hashName = String::makeHash(fileName);

	glGenTextures(1, &m_glName);
}
