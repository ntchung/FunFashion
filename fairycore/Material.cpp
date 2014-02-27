#include "stdafx.h"

Material* Material::create(int name, Shader* shader)
{
	return new(true) Material(name, shader);
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

	const int queue = shader->getRenderQueue();
	m_sortingType = queue < RENDER_QUEUE_TRANSPARENT ? TRIANGLES_SORT_MATERIAL : queue < RENDER_QUEUE_OVERLAY ? TRIANGLES_SORT_BACK_TO_FRONT : TRIANGLES_SORT_NONE;
}

Material::~Material()
{
	m_shader->release();
}

Shader* Material::shader() const
{
	return m_shader;
}
