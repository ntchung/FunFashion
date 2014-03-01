#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Transform.h"
#include "FairyTypes.h"

#include "utils/SharedObject.h"
#include "utils/List.h"

#include "maths/Matrix4x4.h"
#include "maths/Rectf.h"

class RenderBatch;

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

	enum ProjectType
	{
		Perspective = 0,
		Orthographic,
	};

	static Camera* create();
	virtual void destroy();

	virtual void present();

	const Matrix4x4& worldViewProjection() const { return m_worldviewprojection; }
	inline void setViewportRect(const Rectf& rect) { m_viewportRect = rect; m_isProjectionDirty = true; }

	inline Vector3f& rotateVertexByView(Vector3f& vert) const { vert = m_view.rotate(vert); return vert; }
	inline Vector3f& transformVertexByView(Vector3f& vert) const { vert = m_view * vert; return vert; }

	inline ProjectType projectType() const { return m_projectType;  }
	inline void setProjectType(ProjectType value) { m_projectType = value; m_isProjectionDirty = true; }

	RenderBatch* renderBatch(int queue);

protected:
	Camera();
	virtual ~Camera();

	Transform* m_transform;
	Color4F m_backgroundColor;
	ClearType m_clearType;

	List* m_renderBatches;

	Matrix4x4 m_view;
	Matrix4x4 m_projection;
	Matrix4x4 m_worldviewprojection;
	bool m_isProjectionDirty;

	Rectf m_viewportRect;	
	ProjectType m_projectType;
	float m_orthoSize;
	float m_zNear;
	float m_zFar;

	void buildOrthographicProjectionMatrix(Matrix4x4& mat, const Rectf& viewport, float size, float zNear, float zFar);
};

#endif // __CAMERA_H__
