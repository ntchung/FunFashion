#include "stdafx.h"

static RenderState* g_sharedRenderState = 0;

RenderState* RenderState::shared()
{
	if (!g_sharedRenderState)
	{
		g_sharedRenderState = new RenderState();
		g_sharedRenderState->autorelease();
		g_sharedRenderState->retain();
	}

	return g_sharedRenderState;
}

void RenderState::destroy()
{
	delete this;
}

RenderState::RenderState()
: m_currentMaterial(NULL)
{

}

RenderState::~RenderState()
{

}

void RenderState::init()
{
	m_currentMaterial = NULL;

	glDepthMask(GL_FALSE);
	m_isZWriting = false;

	glFrontFace(GL_CW);
	glCullFace(GL_FRONT_AND_BACK);
	glDisable(GL_CULL_FACE);	
	m_faceCullingMode = GL_FRONT_AND_BACK;

	glDepthFunc(GL_ALWAYS);
	glDisable(GL_DEPTH_TEST);
	m_depthFunc = GL_ALWAYS;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);
	m_isAlphaBlending = false;
	m_blendingSource = GL_SRC_ALPHA;
	m_blendingDest = GL_ONE_MINUS_SRC_ALPHA;

	// TODO
	glDisable(GL_STENCIL_TEST);
	glStencilMask(GL_FALSE);
}

void RenderState::set(Shader* shader)
{
	if (m_isZWriting != shader->m_isZWriting)
	{
		m_isZWriting = shader->m_isZWriting;
		glDepthMask(m_isZWriting ? GL_TRUE : GL_FALSE);
	}

	if (m_faceCullingMode != shader->m_faceCullingMode)
	{
		m_faceCullingMode = shader->m_faceCullingMode;
		if (m_faceCullingMode == GL_FRONT_AND_BACK)
		{
			glDisable(GL_CULL_FACE);
		}
		else
		{
			glEnable(GL_CULL_FACE);
			glCullFace(m_faceCullingMode);
		}		
	}

	if (m_depthFunc != shader->m_depthFunc)
	{
		m_depthFunc = shader->m_depthFunc;
		if (m_depthFunc == GL_ALWAYS)
		{
			glDisable(GL_DEPTH_TEST);
		}
		else
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(m_depthFunc);
		}
	}

	if (m_isAlphaBlending != shader->m_isAlphaBlending)
	{
		m_isAlphaBlending = shader->m_isAlphaBlending;
		if (m_isAlphaBlending)
		{
			glEnable(GL_BLEND);
		}
		else
		{
			glDisable(GL_BLEND);
		}
	}

	if (m_blendingSource != shader->m_blendingSource || m_blendingDest != shader->m_blendingDest)
	{
		m_blendingSource = shader->m_blendingSource;
		m_blendingDest = shader->m_blendingDest;
		glBlendFunc(m_blendingSource, m_blendingDest);
	}
}

void RenderState::set(Material* mat)
{
	if (m_currentMaterial != mat)
	{
		if (m_currentMaterial != NULL)
		{
			m_currentMaterial->endTexturing();
		}

		m_currentMaterial = mat;
		if (m_currentMaterial != NULL)
		{
			for (int i = 0; i < MAX_TEXTURE_UNITS; ++i)
			{
				glActiveTexture(GL_TEXTURE0 + i);

				if (!mat->m_textures[i])
				{
					glDisable(GL_TEXTURE_2D);
				}
				else
				{
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, mat->m_textures[i]->glName());
				}
			}

			glUseProgram(mat->m_shader->shaderProgram());
			this->set(mat->m_shader);			
		}
	}
}
