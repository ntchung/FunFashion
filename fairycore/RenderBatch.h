#ifndef __RENDERBATCH_H__
#define __RENDERBATCH_H__

#include <GLES2/gl2.h>
#include "utils/SharedObject.h"
#include "utils/MemoryPool.h"

class Material;
class Camera;
class VertexList;

class RenderBatch : public SharedObject
{
public:
	static RenderBatch* create(Camera* camera, int queue = 0);
	virtual void destroy();

	static void setup();
	static void cleanUp();
	
	void addTriangle(VertexList* vertexList, int i0, int i1, int i2);

	void draw();	
	void clear();

	inline int renderQueue() const { return m_queue; }
	
private:
	RenderBatch(Camera* camera, int queue);
	~RenderBatch();

	Camera* m_camera;
	int m_queue;

	struct Triangle
	{
		VertexList* vertexList;
		GLushort idx[3];
		GLfloat maxZ;
		Triangle* next;
	};
	
	Triangle* m_triangles[TRIANGLES_SORT_TYPES_COUNT];
	int m_trianglesCount[TRIANGLES_SORT_TYPES_COUNT];

	GLushort* m_indices;
	int m_indicesCapacity;

	void draw(Triangle* head, int count);
	static void draw(Camera* camera, VertexList* vertexList, const GLushort* indices, int count);

	static MemoryPool* s_trianglesPool;
	static void sortList(Triangle** first);
};

#endif // __RENDERBATCH_H__
