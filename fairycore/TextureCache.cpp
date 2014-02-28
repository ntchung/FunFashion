#include "stdafx.h"

static TextureCache* g_sharedTextureCache = 0;

TextureCache* TextureCache::shared()
{
	if (!g_sharedTextureCache)
	{
		g_sharedTextureCache = new TextureCache();
		g_sharedTextureCache->autorelease();
		g_sharedTextureCache->retain();
	}

	return g_sharedTextureCache;
}

void TextureCache::destroy()
{
	delete g_sharedTextureCache;
}

TextureCache::TextureCache()
{
	m_textures = List::create(false);
}

TextureCache::~TextureCache()
{
	m_textures->release();
}

Texture* TextureCache::get(const char* name)
{
	Texture* tex;
	unsigned int hashName = String::makeHash(name);

	for (int i = m_textures->count() - 1; i >= 0; --i)
	{
		tex = (Texture*)m_textures->get(i);
		if (tex->name() == hashName)
		{
			return tex;
		}
	}

	tex = Resources::shared()->load<Texture>(name);
	tex->autorelease();

	m_textures->add(tex);
}

void TextureCache::clear()
{
	m_textures->clear();
}
