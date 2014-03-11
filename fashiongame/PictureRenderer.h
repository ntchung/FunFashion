#ifndef __PICTURERENDERER_H__
#define __PICTURERENDERER_H__

#include "Renderer.h"
#include "Transform.h"

class PictureRenderer : public Renderer
{
public:
	static PictureRenderer* create();
	virtual void destroy();

	void draw(Camera* camera, float x, float y, float width, float height);

	void setRotateRight(bool value) { m_isRotateRight = value; }

	inline Transform* transform() { return m_transform; }

private:
	PictureRenderer();
	~PictureRenderer();

	Transform* m_transform;
	bool m_isRotateRight;
};

#endif // __PICTURERENDERER_H__
