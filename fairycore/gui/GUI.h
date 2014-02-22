#ifndef __GUI_H__
#define __GUI_H__

#include "maths/Maths.h"

#include "Camera.h"
#include "RenderBatch.h"

class GUI : public Camera
{
public:
	static GUI* create();
	virtual void destroy();

	virtual void present();

	void fillRect(const Rectf& position, const Color32& color);

protected:
	GUI();
	virtual ~GUI();

	RenderBatch* m_guiFillRectRenderBatch;

	int m_fillRectCount;
};

#endif // __GUI_H__
