#include "stdafx.h"

Transform* Transform::create(bool isAutoRelease)
{
	Transform* ptr = new(true) Transform();
	if (isAutoRelease)
	{
		ptr->autorelease();
	}
	return ptr;
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
{
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
		child->setParent(this->m_parent);
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
	m_parent = parent;
	if (m_parent)
	{
		this->m_nextSibling = m_parent->m_firstChild;
		m_parent->m_firstChild = this;
	}
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
		const float x = positions[i];
		const float y = positions[i+1];
		const float z = positions[i+2];


	}
}

void Transform::UpdateMatrix()
{
	
}
