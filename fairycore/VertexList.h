#ifndef __VERTEXLIST_H__
#define __VERTEXLIST_H__

#include <GLES2/gl2.h>
#include "maths/Vector3f.h"
#include "utils/SharedObject.h"

class Material;
class RenderBatch;

class VertexList : public SharedObject
{
	friend class RenderBatch;

public:
	static VertexList* create(Material* material);
	virtual void destroy();

	int remaining() const;
	void clear();

	void requestCapacity(int count);

	void addVerticesP(GLfloat* positions, int count);
	void addVerticesPU(GLfloat* positions, GLfloat* uvs, int count);
	void addVerticesPC(GLfloat* positions, GLubyte* vertexColors, int count);

	Material* material() const { return m_material;  }
	int count() const { return m_count; }

	inline Vector3f getPos(int idx) const
	{ 
		idx *= 3;
		return Vector3f(m_positions[idx], m_positions[idx + 1], m_positions[idx + 2]);
	}

	inline float getPosZ(int idx) { return m_positions[idx * 3 + 2]; }

private:
	VertexList(Material* material);
	~VertexList();

	Material* m_material;

	GLfloat* m_positions;
	GLfloat* m_uvs;	
	GLfloat* m_normals;
	GLfloat* m_tangents;
	GLfloat* m_binormals;

	GLubyte* m_vertexColors;
	GLubyte* m_boneIndices;
	GLubyte* m_boneWeights;

	int m_count;
	int m_capacity;

	static void resizeArray(void** old, int oldSize, int newSize, int elemSize, bool condition);

	void autoGrow(int count);
};

#endif // __RENDERBATCH_H__
