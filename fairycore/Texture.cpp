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
{

}

Texture::~Texture()
{

}

void Texture::loadPVR(const char* fileName)
{
	m_hashName = String::makeHash(fileName);
}
