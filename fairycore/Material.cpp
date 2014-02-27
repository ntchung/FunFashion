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
}

Material::~Material()
{
	m_shader->release();
}

Shader* Material::shader() const
{
	return m_shader;
}
