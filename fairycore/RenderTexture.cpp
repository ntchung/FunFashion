#include "stdafx.h"

RenderTexture* RenderTexture::create(int width, int height, GLenum depthType, GLenum wrapMode, GLenum filteringMode, bool isAutoRelease)
{
	RenderTexture* ptr = new(true) RenderTexture(width, height, depthType, wrapMode, filteringMode);
	if (isAutoRelease)
	{
		ptr->autorelease();
	}
	return ptr;
}

void RenderTexture::destroy()
{
	this->~RenderTexture();
	POOL(RenderTexture)->deallocate(this);
}

RenderTexture::RenderTexture(int width, int height, GLenum depthType, GLenum wrapMode, GLenum filteringMode)
: m_depthType(depthType)
, m_depthRenderBuffer(0)
, m_colorRenderBuffer(0)
, m_depthTexture(0)
{
	m_width = width;
	m_height = height;
	m_wrapMode = wrapMode;
	m_filteringMode = filteringMode;

	// Frame buffer
	glGenFramebuffers(1, &m_frameBuffer);
	//glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);

	// Color
	/*glGenRenderbuffers(1, &m_colorRenderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_colorRenderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB8_OES, m_width, m_height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_colorRenderBuffer);*/

	// Depth
	if (m_depthType)
	{
		glGenRenderbuffers(1, &m_depthRenderBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, m_depthRenderBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, m_depthType, m_width, m_height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthRenderBuffer);
	}

	/*GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		DebugLog::print("Failed to make complete framebuffer object %x\n", status);
	}*/

	// create the texture	
	glGenTextures(1, &m_glName);
	glBindTexture(GL_TEXTURE_2D, m_glName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filteringMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filteringMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapMode);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,  m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_glName, 0);

	// create the depth texture
	if (m_depthType)
	{
		glGenTextures(1, &m_depthTexture);
		glBindTexture(GL_TEXTURE_2D, m_depthTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filteringMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filteringMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapMode);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,  m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);
	}	
}

RenderTexture::~RenderTexture()
{
	glDeleteTextures(1, &m_glName);
	if (m_depthTexture)
	{
		glDeleteTextures(1, &m_depthTexture);
	}

	if (m_depthRenderBuffer)
	{
		glDeleteRenderbuffers(1, &m_depthRenderBuffer);
	}	
	if (m_colorRenderBuffer)
	{
		glDeleteRenderbuffers(1, &m_colorRenderBuffer);
	}	
	glDeleteFramebuffers(1, &m_frameBuffer);
}

void RenderTexture::begin()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_glName, 0);

	// check status
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		DebugLog::print("Failed to make complete framebuffer object %x\n", status);
	}
}

void RenderTexture::end()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
