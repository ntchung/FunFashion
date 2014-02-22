#include "stdafx.h"

RenderBatch* RenderBatch::create(Material* material)
{
	return new(true) RenderBatch(material);
}

void RenderBatch::destroy()
{
	this->~RenderBatch();
	POOL(RenderBatch)->deallocate(this);
}

RenderBatch::RenderBatch(Material* material)
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
	m_verticesCount = 0;
	m_verticesCapacity = 0;

	m_indices = NULL;
	m_indicesCount = 0;
	m_indicesCapacity = 0;
}

RenderBatch::~RenderBatch()
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
	rmem->recycle(m_indices);

	m_material->release();
}

int RenderBatch::verticesLeft() const
{
	return m_verticesCapacity - m_verticesCount;
}

int RenderBatch::indicesLeft() const
{
	return m_indicesCapacity - m_indicesCount;
}

void RenderBatch::draw()
{
	if (m_indicesCount < 1 || m_verticesCount < 1)
	{
		return;
	}


}

void RenderBatch::clear()
{
	m_verticesCount = 0;
	m_indicesCount = 0;
}

void RenderBatch::requestCapacity(int verticesCount, int indicesCount)
{
	if (m_verticesCapacity < verticesCount)
	{
		m_verticesCapacity = verticesCount;

		const Shader* shader = m_material->shader();
		resizeArray((void**)&m_positions, m_verticesCount * 3, m_verticesCapacity * 3, sizeof(GLfloat), shader->isAttributeRequired(ePVRTPFX_UsPOSITION));
		resizeArray((void**)&m_normals, m_verticesCount * 3, m_verticesCapacity * 3, sizeof(GLfloat), shader->isAttributeRequired(ePVRTPFX_UsNORMAL));
		resizeArray((void**)&m_tangents, m_verticesCount * 3, m_verticesCapacity * 3, sizeof(GLfloat), shader->isAttributeRequired(ePVRTPFX_UsTANGENT));
		resizeArray((void**)&m_binormals, m_verticesCount * 3, m_verticesCapacity * 3, sizeof(GLfloat), shader->isAttributeRequired(ePVRTPFX_UsBINORMAL));
		resizeArray((void**)&m_uvs, m_verticesCount * 2, m_verticesCapacity * 2, sizeof(GLfloat), shader->isAttributeRequired(ePVRTPFX_UsUV));

		resizeArray((void**)&m_vertexColors, m_verticesCount * 4, m_verticesCapacity * 4, sizeof(GLubyte), shader->isAttributeRequired(ePVRTPFX_UsVERTEXCOLOR));
		resizeArray((void**)&m_boneIndices, m_verticesCount, m_verticesCapacity, sizeof(GLubyte), shader->isAttributeRequired(ePVRTPFX_UsBONEINDEX));
		resizeArray((void**)&m_boneWeights, m_verticesCount, m_verticesCapacity, sizeof(GLubyte), shader->isAttributeRequired(ePVRTPFX_UsBONEWEIGHT));
	}

	if (m_indicesCapacity < indicesCount)
	{
		m_indicesCapacity = indicesCount;
		resizeArray((void**)&m_indices, m_indicesCount, m_indicesCapacity, sizeof(GLushort));
	}
}

void RenderBatch::resizeArray(void** old, int oldSize, int newSize, int elemSize, bool condition)
{	
	if (!condition)
	{
		return;
	}

	void* newArray = RecyclingMemory::shared()->allocate(newSize);
	if (oldSize > 0)
	{
		memcpy(newArray, *old, oldSize * elemSize);
	}
	RecyclingMemory::shared()->recycle(*old);
	*old = newArray;
}

void RenderBatch::addIndices(GLushort* indices, int count)
{
	memcpy(m_indices + m_indicesCount, indices, count * sizeof(GLushort));
	m_indicesCount += count;
}

void RenderBatch::addVerticesP(GLfloat* positions, int count)
{
	memcpy(m_positions + m_verticesCount * 3, positions, count * 3 * sizeof(GLfloat));
	m_verticesCount += count;
}
