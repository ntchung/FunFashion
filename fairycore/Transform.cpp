#include "stdafx.h"

static Transform* g_transformRoot = 0;

Transform* Transform::create(Transform* parent)
{
	return new(true) Transform(parent);	
}

void Transform::destroy()
{
	this->~Transform();
	POOL(Transform)->deallocate(this);
}

Transform::Transform()
: m_parent(NULL)
, m_firstChild(NULL)
, m_nextSibling(NULL)
, m_scale(Vector3f::one)
, m_isIdentity(true)
{
}

Transform::Transform(Transform* parent)
: m_parent(NULL)
, m_firstChild(NULL)
, m_nextSibling(NULL)
, m_scale(Vector3f::one)
, m_isIdentity(true)
{
	setParent(parent);
}

Transform::~Transform()
{
	DetachChildren();

	this->setParent(NULL);
}

Transform* Transform::parent() const
{
	return m_parent;
}

void Transform::DetachChildren()
{
	Transform* child = m_firstChild;
	while (child)
	{
		child->m_parent = NULL; // do not need to tackle with my children list, just find your new parent
		if (this->m_parent)
		{
			child->setParent(this->m_parent);
		}
		child = child->m_nextSibling;
	}
}

void Transform::setParent(Transform* parent)
{
	// Remove me from old parent
	if (m_parent)
	{		
		Transform* child = m_parent->m_firstChild;
		Transform* prev = NULL;
		while (child)
		{
			if (child == this)
			{
				if (!prev)
				{
					m_parent->m_firstChild = child->m_nextSibling;
				}
				else
				{
					prev->m_nextSibling = child->m_nextSibling;
				}
				break;
			}

			prev = child;
			child = child->m_nextSibling;
		}
	}

	// Add me to the new family
	m_parent = parent ? parent : g_transformRoot;
	this->m_nextSibling = m_parent->m_firstChild;
	m_parent->m_firstChild = this;	
}

int Transform::childCount() const
{
	// TODO - optimize
	int count = 0;
	Transform* child = m_firstChild;
	while (child)
	{
		++count;
		child = child->m_nextSibling;
	}
	return count;
}

Transform* Transform::root() const
{
	Transform* parent = m_parent;
	while (parent)
	{
		if (parent->m_parent)
		{
			parent = parent->m_parent;
		}
		else
		{
			return parent;
		}
	}

	return parent;
}

void Transform::TransformPoints(float* positions, int size)
{
	for (int i = 0; i < size; i += 3)
	{
		Vector3f t = m_worldMatrix * Vector3f(positions[i], positions[i + 1], positions[i + 2]);
		positions[i] = t.x;
		positions[i+1] = t.y;
		positions[i+2] = t.z;
	}
}

void Transform::setup()
{
	g_transformRoot = new(true) Transform();
	g_transformRoot->autorelease();
	g_transformRoot->retain();
}

void Transform::update()
{
	update(g_transformRoot);
}

void Transform::update(Transform* root)
{
	Transform* p = root->m_firstChild;
	while (p)
	{
		p->UpdateMatrix();

		update(p);
		p = p->m_nextSibling;
	}
}

void Transform::UpdateMatrix()
{
	if (!m_isIdentity)
	{
		m_localMatrix.set(m_position, m_rotation, m_scale);
	}

	m_worldMatrix = m_parent->m_worldMatrix * m_localMatrix;
}
