#include "stdafx.h"

Material* Material::create(Shader* shader)
{
	return new(true) Material(shader);
}

void Material::destroy()
{
	this->~Material();
	POOL(Material)->deallocate(this);
}

Material::Material(Shader* shader)
{
	m_shader = shader;
	m_shader->retain();

	m_guid = UIDGenerator::shared()->next();
}

Material::~Material()
{
	m_shader->release();
}

int Material::guid() const
{
	return m_guid;
}

Shader* Material::shader() const
{
	return m_shader;
}
