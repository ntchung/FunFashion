#ifndef __TESTRENDERER_H__
#define __TESTRENDERER_H__

#include "Renderer.h"

class TestRenderer : public Renderer
{
public:
	static TestRenderer* create();
	virtual void destroy();

	virtual void draw(Camera* camera);

private:
	~TestRenderer();
};

#endif // __TESTRENDERER_H__
