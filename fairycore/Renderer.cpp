#include "stdafx.h"

Renderer::Renderer()
: m_material(NULL)
, m_vertexList(NULL)
{

}

Renderer::~Renderer()
{
	SAFE_RELEASE(m_material);
	SAFE_RELEASE(m_vertexList);
}

void Renderer::setMaterial(Material* value)
{
	SAFE_RELEASE(m_material);
	SAFE_RELEASE(m_vertexList);

	m_material = value;
	m_material->retain();

	m_vertexList = VertexList::create(m_material);
}

void Renderer::reset()
{
	if (m_vertexList)
	{
		m_vertexList->clear();
	}
}
