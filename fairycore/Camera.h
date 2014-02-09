#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Transform.h"
#include "FairyTypes.h"

#include "utils/SharedObject.h"

class Camera : public SharedObject
{
public:
	enum ClearType
	{
		NONE = 0,
		DEPTH_ONLY = GL_DEPTH_BUFFER_BIT,
		COLOR_ONLY = GL_COLOR_BUFFER_BIT,
		DEPTH_AND_COLOR = (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT),
	};	

	static Camera* create();
	virtual void destroy();

	virtual void present();

protected:
	Camera();
	virtual ~Camera();

	//Transform* m_transform;
	Color4F m_backgroundColor;
	ClearType m_clearType;
};

#endif // __CAMERA_H__
