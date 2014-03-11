#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "utils/SharedObject.h"

class Material;
class VertexList;
class Camera;

class Renderer : public SharedObject
{
public:
	void setMaterial(Material* value);
	inline Material* material() const { return m_material; }

	void reset();

protected:
	Renderer();
	virtual ~Renderer();

	Material* m_material;
	VertexList* m_vertexList;
};

#endif // __RENDERER_H__
