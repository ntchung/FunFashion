#ifndef __GUI_H__
#define __GUI_H__

#include "Camera.h"
#include "RenderBatch.h"

class GUI : public Camera
{
public:
	static GUI* create();
	virtual void destroy();

	virtual void present();

	//void fillRect(

protected:
	GUI();
	virtual ~GUI();

	Material* m_guiMaterial;
	RenderBatch* m_guiRenderBatch;
};

#endif // __GUI_H__
