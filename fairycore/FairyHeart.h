#ifndef __FAIRYHEART_H__
#define __FAIRYHEART_H__

#include "Camera.h"

#include "utils/DynamicArray.h"

class FairyHeart
{
public:
	FairyHeart();
	~FairyHeart();

	void addCamera(Camera* camera);

	void reset();
	void update();
	void render();

private:
	DynamicArray<Camera*> m_cameras;
};

#endif // __FAIRYHEART_H__
