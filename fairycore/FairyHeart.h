#ifndef __FAIRYHEART_H__
#define __FAIRYHEART_H__

#include "Camera.h"

#include "utils/List.h"
#include "maths/Rectf.h"

class FairyHeart
{
public:
	FairyHeart();
	~FairyHeart();

	void addCamera(Camera* camera);

	void reset();
	void update();
	void render();

	void setViewport(float x, float y, float width, float height);

private:
	List m_cameras;
	Rectf m_viewportRect;
};

#endif // __FAIRYHEART_H__
