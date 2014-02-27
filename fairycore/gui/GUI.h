#ifndef __GUI_H__
#define __GUI_H__

#include "maths/Maths.h"

#include "Camera.h"
#include "VertexList.h"
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

	VertexList* m_fillRectVertices;

	RenderBatch* m_renderBatch;

	static void build2DProjectionMatrix(Matrix4x4& mat, float viewWidth, float viewHeight);
};

#endif // __GUI_H__
