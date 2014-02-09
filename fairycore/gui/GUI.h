#ifndef __GUI_H__
#define __GUI_H__

#include "Camera.h"

class GUI : public Camera
{
public:
	static GUI* create();
	virtual void destroy();

	virtual void present();

protected:
	GUI();
	virtual ~GUI();
};

#endif // __GUI_H__
