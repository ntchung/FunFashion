#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "utils/SharedObject.h"

class List;

class Texture : public SharedObject
{
public:
	static Texture* create(int width, int height, GLenum filteringMode = GL_LINEAR, GLenum wrapMode = GL_CLAMP_TO_EDGE, GLenum internalFormat = GL_RGBA, bool isAutoRelease = true);
	static Texture* create(char* data, int length, bool isAutoRelease = true);
	virtual void destroy();
	
	inline GLuint glName() const { return m_glName; }

	void setData(int x, int y, int w, int h, void* data);
	void setData(void* data);

protected:
	Texture();
	Texture(int width, int height, GLenum filteringMode, GLenum wrapMode, GLenum internalFormat);
	Texture(char* data, int length);
	virtual ~Texture();

	enum DataType
	{
		MUTABLE_RGBA = 0,
		MUTABLE_ALPHA,
		NO_MIPMAP,
		HAS_MIPMAP,
	};

	GLuint m_glName;

	int m_width;
	int m_height;
	DataType m_dataType;

	GLenum m_wrapMode;
	GLenum m_filteringMode;
};

#endif // __TEXTURE_H__
