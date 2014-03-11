#include "stdafx.h"

Material* Material::create(int name, Shader* shader, bool isAutoRelease)
{
	Material* ptr = new(true) Material(name, shader);
	if (isAutoRelease)
	{
		ptr->autorelease();
	}
	return ptr;
}

void Material::destroy()
{
	this->~Material();
	POOL(Material)->deallocate(this);
}

Material::Material(int name, Shader* shader)
: m_name(name)
{
	m_shader = shader;
	m_shader->retain();

	const int queue = shader->renderQueue();
	m_sortingType = queue < RENDER_QUEUE_TRANSPARENT ? TRIANGLES_SORT_MATERIAL : queue < RENDER_QUEUE_OVERLAY ? TRIANGLES_SORT_BACK_TO_FRONT : TRIANGLES_SORT_NONE;

	for( int i=0; i<MAX_TEXTURE_UNITS; ++i )
	{
		m_textures[i] = NULL;
	}
}

Material::~Material()
{
	m_shader->release();
	for (int i = 0; i<MAX_TEXTURE_UNITS; ++i)
	{
		if (m_textures[i])
		{
			m_textures[i]->release();
		}
	}
}

void Material::begin()
{	
	RenderState::shared()->set(this);		
}

void Material::endShader()
{
	// Attributes
	for (int i = 0; i < m_shader->uniforms().count(); ++i)
	{
		SPVRTPFXUniform& uniform = m_shader->uniforms().get(i);
		switch (uniform.nSemantic)
		{
		case ePVRTPFX_UsPOSITION:
		case ePVRTPFX_UsNORMAL:
		case ePVRTPFX_UsTANGENT:
		case ePVRTPFX_UsBINORMAL:
		case ePVRTPFX_UsUV:
		case ePVRTPFX_UsVERTEXCOLOR:
		case ePVRTPFX_UsBONEINDEX:
		case ePVRTPFX_UsBONEWEIGHT:
			glDisableVertexAttribArray(uniform.nLocation);
			break;
		}
	}
}

void Material::endTexturing()
{
	for (int i = 0; i < MAX_TEXTURE_UNITS; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (m_textures[i])
		{
			glDisable(GL_TEXTURE_2D);
		}		
	}
}

void Material::setTexture(int idx, Texture* tex)
{
	if (m_textures[idx])
	{
		m_textures[idx]->release();
	}

	m_textures[idx] = tex; 
	tex->retain();
}
