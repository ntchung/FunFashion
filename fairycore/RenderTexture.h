#ifndef __RENDERTEXTURE_H__
#define __RENDERTEXTURE_H__

#include "Texture.h"

class RenderTexture : public Texture
{
public:
	static RenderTexture* create(int width, int height, GLenum depthType = 0, GLenum wrapMode = GL_REPEAT, GLenum filteringMode = GL_LINEAR, bool isAutoRelease = true);
	virtual void destroy();

	int width() const { return m_width;  }
	int height() const { return m_height;  }

	void begin();
	void end();

private:
	RenderTexture(int width, int height, GLenum depthType, GLenum wrapMode, GLenum filteringMode);
	~RenderTexture();

	GLuint m_frameBuffer;
	GLuint m_colorRenderBuffer;
	GLuint m_depthRenderBuffer;
	GLuint m_depthTexture;
	GLenum m_depthType;
};

#endif // __RENDERTEXTURE_H__
