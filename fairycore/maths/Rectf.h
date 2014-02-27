#ifndef __RECT_H__
#define __RECT_H__

#include "maths/Vector2f.h"
#include "maths/Vector3f.h"

struct Rectf
{
public:	
	inline Vector2f center()
	{
		return Vector2f(this->m_XMin + this->m_Width / 2.f, this->m_YMin + this->m_Height / 2.f);
	}

	inline void setCenter(const Vector2f& value)
	{
		this->m_XMin = value.x - this->m_Width / 2.f;
		this->m_YMin = value.y - this->m_Height / 2.f;
	}

	inline float height() const
	{
		return this->m_Height;
	}

	inline void setHeight(float value)
	{
		this->m_Height = value;
	}

	inline float width() const
	{
		return this->m_Width;
	}

	inline void setWidth(float value)
	{
		this->m_Width = value;
	}

	inline float x() const
	{
		return this->m_XMin;
	}

	inline void setX(float value)
	{
		this->m_XMin = value;
	}

	inline float xMax() const
	{
		return this->m_Width + this->m_XMin;
	}

	inline void setXMax(float value)
	{
		this->m_Width = value - this->m_XMin;
	}

	inline float xMin() const
	{
		return this->m_XMin;
	}

	inline void setXMin(float value)
	{
		float xMax = this->xMax();
		this->m_XMin = value;
		this->m_Width = xMax - this->m_XMin;
	}

	inline float y() const
	{
		return this->m_YMin;
	}

	inline void setY(float value)
	{
		this->m_YMin = value;
	}

	inline float yMax() const
	{
		return this->m_Height + this->m_YMin;
	}

	inline void setYMax(float value)
	{
		this->m_Height = value - this->m_YMin;
	}

	inline float yMin() const
	{
		return this->m_YMin;
	}

	inline void setYMin(float value)
	{
		float yMax = this->yMax();
		this->m_YMin = value;
		this->m_Height = yMax - this->m_YMin;
	}

	//
	// Constructors
	//
	Rectf()
		: m_XMin(0)
		, m_YMin(0)
		, m_Width(0)
		, m_Height(0)
	{
	}

	Rectf(const Rectf& source)
	{
		this->m_XMin = source.m_XMin;
		this->m_YMin = source.m_YMin;
		this->m_Width = source.m_Width;
		this->m_Height = source.m_Height;
	}

	Rectf(float left, float top, float width, float height)
	{
		this->m_XMin = left;
		this->m_YMin = top;
		this->m_Width = width;
		this->m_Height = height;
	}

	//
	// Static Methods
	//
	inline static Rectf MinMaxRect(float left, float top, float right, float bottom)
	{
		return Rectf(left, top, right - left, bottom - top);
	}

	//
	// Methods
	//
	inline bool Contains(const Vector2f& point)
	{
		return point.x >= this->xMin() && point.x < this->xMax() && point.y >= this->yMin() && point.y < this->yMax();
	}

	inline bool Contains(const Vector3f& point)
	{
		return point.x >= this->xMin() && point.x < this->xMax() && point.y >= this->yMin() && point.y < this->yMax();
	}

	inline bool Contains(const Vector3f& point, bool allowInverse)
	{
		if (!allowInverse)
		{
			return this->Contains(point);
		}
		bool flag = false;
		if ((this->width() < 0.f && point.x <= this->xMin() && point.x > this->xMax()) || (this->width() >= 0.f && point.x >= this->xMin() && point.x < this->xMax()))
		{
			flag = true;
		}
		return flag && ((this->height() < 0.f && point.y <= this->yMin() && point.y > this->yMax()) || (this->height() >= 0.f && point.y >= this->yMin() && point.y < this->yMax()));
	}

	inline bool Overlaps(const Rectf& other)
	{
		return other.xMax() > this->xMin() && other.xMin() < this->xMax() && other.yMax() > this->yMin() && other.yMin() < this->yMax();
	}

	inline void Set(float left, float top, float width, float height)
	{
		this->m_XMin = left;
		this->m_YMin = top;
		this->m_Width = width;
		this->m_Height = height;
	}

private:
	float m_XMin;
	float m_YMin;
	float m_Width;
	float m_Height;
};

//
// Operators
//
inline bool operator ==(const Rectf& lhs, const Rectf& rhs)
{
	return lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.width() == rhs.width() && lhs.height() == rhs.height();
}

inline bool operator !=(const Rectf& lhs, const Rectf& rhs)
{
	return lhs.x() != rhs.x() || lhs.y() != rhs.y() || lhs.width() != rhs.width() || lhs.height() != rhs.height();
}

#endif // __RECT_H__
