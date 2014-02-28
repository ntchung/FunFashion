#include "stdafx.h"

Renderer* Renderer::create()
{
	return new(true) Renderer();
}

void Renderer::destroy()
{
	this->~Renderer();
	POOL(Renderer)->deallocate(this);
}

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

