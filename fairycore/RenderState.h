#ifndef __RENDERSTATE_H__
#define __RENDERSTATE_H__

#include "utils/SharedObject.h"

class Shader;

class RenderState : public SharedObject
{
public:
	static RenderState* shared();
	virtual void destroy();

	void init();

	void set(Shader* shader);
	void set(Material* material);

private:
	RenderState();
	~RenderState();

	bool m_isZWriting;
	GLenum m_faceCullingMode;

	bool m_isAlphaBlending;
	GLenum m_blendingSource;
	GLenum m_blendingDest;

	GLenum m_depthFunc;

	Material* m_currentMaterial;
};

#endif // __RENDERSTATE_H__
