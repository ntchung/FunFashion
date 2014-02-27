#include "stdafx.h"

MemoryPool* RenderBatch::s_trianglesPool = 0;

RenderBatch* RenderBatch::create(Camera* camera)
{
	return new(true) RenderBatch(camera);
}

void RenderBatch::destroy()
{
	this->~RenderBatch();
	POOL(RenderBatch)->deallocate(this);
}

void RenderBatch::setup()
{
	s_trianglesPool = new MemoryPool(sizeof(Triangle), TRIANGLES_POOL_SIZE);
}

void RenderBatch::cleanUp()
{
	delete s_trianglesPool;
}

RenderBatch::RenderBatch(Camera* camera)
{
	m_camera = camera;
	m_camera->retain();

	m_opaqueTriangles = NULL;
	m_opaqueTrianglesCount = 0;

	m_transparentTriangles = NULL;
	m_transparentTrianglesCount = 0;

	m_indices = NULL;
	m_indicesCapacity = 0;
}

RenderBatch::~RenderBatch()
{	
	m_camera->release();
	clear();
}

void RenderBatch::addTriangle(VertexList* vertexList, int i0, int i1, int i2)
{
	bool isTransparent = vertexList->m_material->shader()->getRenderType() == GL_RENDER_TYPE_TRANSPARENT;	

	Triangle* p = (Triangle*)s_trianglesPool->allocate();

	p->vertexList = vertexList;
	p->idx[0] = i0;
	p->idx[1] = i1;
	p->idx[2] = i2;

	// Transparent
	if (isTransparent)
	{
		const GLfloat z0 = m_camera->rotateVertexByView(vertexList->getPos(i0)).z;
		const GLfloat z1 = m_camera->rotateVertexByView(vertexList->getPos(i1)).z;
		const GLfloat z2 = m_camera->rotateVertexByView(vertexList->getPos(i2)).z;
		p->maxZ = Mathf::Max(z0, z1, z2);
	
		Triangle* temp = m_transparentTriangles;
		m_transparentTriangles = p;
		m_transparentTriangles->next = temp;

		++m_transparentTrianglesCount;
	}
	// Opaque
	else
	{
		// Find same material chunk to add
		Triangle* temp;
		Triangle*& t = m_opaqueTriangles;
		while (t)
		{
			if (t->vertexList == vertexList)
			{
				temp = t;
				t = p;
				t->next = temp;
				break;
			}
			t = t->next;
		}

		// Not found? Just add to head
		if (!t)
		{
			temp = m_opaqueTriangles;
			m_opaqueTriangles = p;
			m_opaqueTriangles->next = temp;
		}

		++m_opaqueTrianglesCount;
	}
}

void RenderBatch::draw()
{	
	// Opaque pass
	draw(m_opaqueTriangles, m_opaqueTrianglesCount);

	// Sort transparent triangles
	sortList(&m_transparentTriangles);

	// Transparent pass
	draw(m_transparentTriangles, m_transparentTrianglesCount);
}

void RenderBatch::draw(Triangle* head, int count)
{
	if (count < 1)
	{
		return;
	}

	if (m_indicesCapacity < count * 3)
	{
		m_indicesCapacity = RecyclingMemory::shared()->resizeArray((void**)&m_indices, m_indicesCapacity, count * 3, sizeof(GLushort));
	}

	int cnt = 0;
	Triangle* p = head;
	VertexList* currentVertexList = p->vertexList;
	while (p)
	{
		if (p->vertexList != currentVertexList)
		{
			draw(m_camera, currentVertexList, m_indices, cnt);
			cnt = 0;
			currentVertexList = p->vertexList;			
		}

		memcpy(m_indices + cnt, p->idx, 3 * sizeof(GLushort));
		p = p->next;
		cnt += 3;
	}

	draw(m_camera, currentVertexList, m_indices, cnt);	
}

void RenderBatch::draw(Camera* camera, VertexList* vertexList, const GLushort* indices, int count)
{
	if (count < 1)
	{
		return;
	}

	int i;	
	Shader* shader = vertexList->m_material->shader();
	const Array<SPVRTPFXUniform>& uniforms = shader->uniforms();

	// GL states
	shader->begin();	
	
	// Attributes and Uniforms
	for (i = 0; i < uniforms.count(); ++i)
	{
		const SPVRTPFXUniform& uniform = uniforms[i];
		switch (uniform.nSemantic)
		{
		case ePVRTPFX_UsPOSITION:
			glVertexAttribPointer(uniform.nLocation, 3, GL_FLOAT, GL_FALSE, 0, vertexList->m_positions);
			glEnableVertexAttribArray(uniform.nLocation);			
			break;

		case ePVRTPFX_UsVERTEXCOLOR:
			glVertexAttribPointer(uniform.nLocation, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, vertexList->m_vertexColors);
			glEnableVertexAttribArray(uniform.nLocation);
			break;

		case ePVRTPFX_UsWORLDVIEWPROJECTION:
			glUniformMatrix4fv(uniform.nLocation, 1, GL_FALSE, camera->worldViewProjection().m);
			break;
		}		
	}

	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, indices);

	// Clean up
	shader->end();
}

void RenderBatch::clear()
{
	Triangle* p = m_opaqueTriangles;
	while (p)
	{
		Triangle* n = p;		
		p = p->next;

		s_trianglesPool->deallocate(n);
	}
	m_opaqueTriangles = NULL;
	m_opaqueTrianglesCount = 0;

	p = m_transparentTriangles;
	while (p)
	{
		Triangle* n = p;
		p = p->next;

		s_trianglesPool->deallocate(n);
	}
	m_transparentTriangles = NULL;
	m_transparentTrianglesCount = 0;
}

void RenderBatch::sortList(Triangle** first)
{
	Triangle *p, *q, *e, *tail;
	int insize, nmerges, psize, qsize, i;

	insize = 1;

	while (true)
	{
		p = *first;
		*first = NULL;
		tail = NULL;

		nmerges = 0;  // count number of merges we do in this pass

		while (p)
		{
			nmerges++;  // there exists a merge to be done

			// step `insize' places along from p
			q = p;
			psize = 0;
			for (i = 0; i < insize; i++)
			{
				psize++;
				q = q->next;
				if (!q)
				{
					break;
				}
			}

			// if q hasn't fallen off end, we have two lists to merge
			qsize = insize;

			// now we have two lists; merge them 
			while (psize > 0 || (qsize > 0 && q))
			{
				// decide whether next element of merge comes from p or q
				if (psize == 0)
				{
					// p is empty; e must come from q.
					e = q;
					q = q->next;
					qsize--;

				}
				else if (qsize == 0 || !q)
				{
					// q is empty; e must come from p.
					e = p;
					p = p->next;
					psize--;
				}
				else if (p->maxZ > q->maxZ)
				{
					// First element of p is lower (or same);
					// e must come from p.
					e = p;
					p = p->next;
					psize--;
				}
				else
				{
					// First element of q is lower; e must come from q.
					e = q;
					q = q->next;
					qsize--;
				}

				// add the next element to the merged list
				if (tail)
				{
					tail->next = e;
				}
				else
				{
					*first = e;
				}

				tail = e;
			}

			// now p has stepped `insize' places along, and q has too
			p = q;
		}

		tail->next = NULL;

		// If we have done only one merge, we're finished.
		if (nmerges <= 1)   // allow for nmerges==0, the empty list case
		{
			return;
		}

		// Otherwise repeat, merging lists twice the size
		insize <<= 1;
	}
}
