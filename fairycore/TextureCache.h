#ifndef __TEXTURECACHE_H__
#define __TEXTURECACHE_H__

#include "utils/SharedObject.h"
#include "utils/List.h"

class TextureCache : public SharedObject
{
public:
	static TextureCache* shared();
	virtual void destroy();

	Texture* get(const char* name);
	void clear();

private:
	TextureCache();
	~TextureCache();

	List* m_textures;
};

#endif // __TEXTURECACHE_H__
