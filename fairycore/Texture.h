#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "utils/SharedObject.h"

class Texture : public SharedObject
{
public:
	static Texture* create();
	virtual void destroy();

	void loadPVR(const char* fileName);

	unsigned int name() const { return m_hashName;  }

private:
	Texture();
	~Texture();

	unsigned int m_hashName;
};

#endif // __TEXTURE_H__
