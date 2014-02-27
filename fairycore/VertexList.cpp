#include "stdafx.h"

VertexList* VertexList::create(Material* material)
{
	return new(true) VertexList(material);
}

void VertexList::destroy()
{
	this->~VertexList();
	POOL(VertexList)->deallocate(this);
}

VertexList::VertexList(Material* material)
{
	m_material = material;
	m_material->retain();

	m_positions = NULL;
	m_uvs = NULL;
	m_normals = NULL;
	m_tangents = NULL;
	m_binormals = NULL;
	m_vertexColors = NULL;
	m_boneIndices = NULL;
	m_boneWeights = NULL;
	m_count = 0;
	m_capacity = 0;
}

VertexList::~VertexList()
{
	RecyclingMemory* rmem = RecyclingMemory::shared();
	rmem->recycle(m_positions);
	rmem->recycle(m_uvs);
	rmem->recycle(m_normals);
	rmem->recycle(m_tangents);
	rmem->recycle(m_binormals);
	rmem->recycle(m_vertexColors);
	rmem->recycle(m_boneIndices);
	rmem->recycle(m_boneWeights);

	m_material->release();
}

int VertexList::remaining() const
{
	return m_capacity - m_count;
}

void VertexList::clear()
{
	m_count = 0;
}

void VertexList::requestCapacity(int count)
{
	if (m_capacity < count)
	{
		m_capacity = count;

		const Shader* shader = m_material->shader();
		resizeArray((void**)&m_positions, m_count * 3, m_capacity * 3, sizeof(GLfloat), shader->isAttributeRequired(ePVRTPFX_UsPOSITION));
		resizeArray((void**)&m_normals, m_count * 3, m_capacity * 3, sizeof(GLfloat), shader->isAttributeRequired(ePVRTPFX_UsNORMAL));
		resizeArray((void**)&m_tangents, m_count * 3, m_capacity * 3, sizeof(GLfloat), shader->isAttributeRequired(ePVRTPFX_UsTANGENT));
		resizeArray((void**)&m_binormals, m_count * 3, m_capacity * 3, sizeof(GLfloat), shader->isAttributeRequired(ePVRTPFX_UsBINORMAL));
		resizeArray((void**)&m_uvs, m_count * 2, m_capacity * 2, sizeof(GLfloat), shader->isAttributeRequired(ePVRTPFX_UsUV));

		resizeArray((void**)&m_vertexColors, m_count * 4, m_capacity * 4, sizeof(GLubyte), shader->isAttributeRequired(ePVRTPFX_UsVERTEXCOLOR));
		resizeArray((void**)&m_boneIndices, m_count, m_capacity, sizeof(GLubyte), shader->isAttributeRequired(ePVRTPFX_UsBONEINDEX));
		resizeArray((void**)&m_boneWeights, m_count, m_capacity, sizeof(GLubyte), shader->isAttributeRequired(ePVRTPFX_UsBONEWEIGHT));
	}
}

void VertexList::resizeArray(void** old, int oldSize, int newSize, int elemSize, bool condition)
{	
	if (!condition)
	{
		return;
	}

	RecyclingMemory::shared()->resizeArray(old, oldSize, newSize, elemSize);
}

void VertexList::addVerticesP(GLfloat* positions, int count)
{
	autoGrow(count);
	memcpy(m_positions + m_count * 3, positions, count * 3 * sizeof(GLfloat));
	m_count += count;
}

void VertexList::addVerticesPC(GLfloat* positions, GLubyte* vertexColors, int count)
{
	autoGrow(count);
	memcpy(m_positions + m_count * 3, positions, count * 3 * sizeof(GLfloat));
	memcpy(m_vertexColors + m_count * 4, vertexColors, count * 4 * sizeof(GLfloat));
	m_count += count;
}

void VertexList::autoGrow(int count)
{
	if (m_count + count >= m_capacity)
	{
		requestCapacity(m_capacity + ((count / VERTEX_LIST_GROW_RATE) + 1) * VERTEX_LIST_GROW_RATE);
	}
}
