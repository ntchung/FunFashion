#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "utils/SharedObject.h"

class Renderer : public SharedObject
{
public:
	static Renderer* create();
	virtual void destroy();

private:
	Renderer();
	~Renderer();
};

#endif // __RENDERER_H__
