#include "stdafx.h"

Shader* Shader::create(const char* data)
{
	return new(true) Shader(data);
}

void Shader::destroy()
{
	this->~Shader();
	POOL(Shader)->deallocate(this);
}

Shader::Shader(const char* data)
{
	
}

Shader::~Shader()
{

}

