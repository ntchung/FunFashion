#ifndef __RENDERBATCH_H__
#define __RENDERBATCH_H__

#include <GLES2/gl2.h>
#include "Material.h"

class RenderBatch : public SharedObject
{
public:
	static RenderBatch* create(Material* material);
	virtual void destroy();

	int verticesLeft() const;
	int indicesLeft() const;
	void draw();
	void clear();

	void requestCapacity(int verticesCount, int indicesCount);

	void addIndices(GLushort* indices, int count);
	void addVerticesP(GLfloat* positions, int count);
	void addVerticesPC(GLfloat* positions, GLubyte* vertexColors, int count);

private:
	RenderBatch(Material* material);
	~RenderBatch();

	Material* m_material;

	GLfloat* m_positions;
	GLfloat* m_uvs;	
	GLfloat* m_normals;
	GLfloat* m_tangents;
	GLfloat* m_binormals;

	GLubyte* m_vertexColors;
	GLubyte* m_boneIndices;
	GLubyte* m_boneWeights;

	int m_verticesCount;
	int m_verticesCapacity;

	GLushort* m_indices;
	int m_indicesCount;
	int m_indicesCapacity;

	static void resizeArray(void** old, int oldSize, int newSize, int elemSize, bool condition = true);
};

#endif // __RENDERBATCH_H__
