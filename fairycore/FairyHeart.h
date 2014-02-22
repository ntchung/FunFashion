#ifndef __FAIRYHEART_H__
#define __FAIRYHEART_H__

#include "Camera.h"

#include "utils/List.h"

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
	List m_cameras;
};

#endif // __FAIRYHEART_H__
