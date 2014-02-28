#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "utils/SharedObject.h"

class Texture : public SharedObject
{
public:
	static Texture* create();
	static Texture* create(char* data, int length);
	virtual void destroy();

	void setName(const char* name);
	inline void setHashName(unsigned int value) { m_hashName = value; }
	inline unsigned int name() const { return m_hashName; }
	inline GLuint glName() const { return m_glName; }

private:
	Texture();
	Texture(char* data, int length);
	~Texture();

	unsigned int m_hashName;
	GLuint m_glName;
};

#endif // __TEXTURE_H__
