#ifndef __VECTOR2F_H__
#define __VECTOR2F_H__

#include "maths/Mathf.h"

struct Vector2f;

inline static Vector2f operator +(const Vector2f& a, const Vector2f& b);
inline static Vector2f operator /(const Vector2f& a, float d);
inline static bool operator ==(const Vector2f& lhs, Vector2f rhs);
inline static bool operator !=(const Vector2f& lhs, Vector2f rhs);
inline static Vector2f operator *(const Vector2f& a, float d);
inline static Vector2f operator *(float d, const Vector2f& a);
inline static Vector2f operator -(const Vector2f& a, const Vector2f& b);
inline static Vector2f operator -(const Vector2f& a);

struct Vector2f
{
public:
	//
	// Static Fields
	//
	static const float kEpsilon;
	static const Vector2f one;
	static const Vector2f zero;
	static const Vector2f right;
	static const Vector2f up;

	//
	// Fields
	//
	float y;
	float x;

	//
	// Properties
	//
	inline float magnitude() const
	{
		return Mathf::Sqrt(this->x * this->x + this->y * this->y);	
	}

	inline Vector2f normalized() const
	{
		Vector2f result(this->x, this->y);
		result.Normalize();
		return result;
	}

	inline float sqrMagnitude() const
	{
		return this->x * this->x + this->y * this->y;	
	}

	//
	// Indexer
	//
	inline float& operator[](int index)
	{
		if (index == 0)
		{
			return this->x;
		}
		
		return this->y;
	}

	//
	// Constructors
	//
	Vector2f(float nx, float ny)
		: x(nx)
		, y(ny)
	{
	}

	//
	// Static Methods
	//
	inline static float Angle(const Vector2f& from, const Vector2f& to)
	{
		return Mathf::Acos(Mathf::Clamp(Vector2f::Dot(from.normalized(), to.normalized()), -1.f, 1.f)) * 57.29578f;
	}

	inline static Vector2f ClampMagnitude(const Vector2f& vector, float maxLength)
	{
		if (vector.sqrMagnitude() > maxLength * maxLength)
		{
			return vector.normalized() * maxLength;
		}
		return vector;
	}

	inline static float Distance(const Vector2f& a, const Vector2f& b)
	{
		return (a - b).magnitude();
	}

	inline static float Dot(const Vector2f& lhs, const Vector2f& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}

	inline static Vector2f Lerp(const Vector2f& from, const Vector2f& to, float t)
	{
		t = Mathf::Clamp01(t);
		return Vector2f(from.x + (to.x - from.x) * t, from.y + (to.y - from.y) * t);
	}

	inline static Vector2f Max(const Vector2f& lhs, const Vector2f& rhs)
	{
		return Vector2f(Mathf::Max(lhs.x, rhs.x), Mathf::Max(lhs.y, rhs.y));
	}

	inline static Vector2f Min(const Vector2f& lhs, const Vector2f& rhs)
	{
		return Vector2f(Mathf::Min(lhs.x, rhs.x), Mathf::Min(lhs.y, rhs.y));
	}

	inline static Vector2f MoveTowards(const Vector2f& current, const Vector2f& target, float maxDistanceDelta)
	{
		Vector2f a = target - current;
		float magnitude = a.magnitude();
		if (magnitude <= maxDistanceDelta || magnitude == 0.f)
		{
			return target;
		}
		return current + a / magnitude * maxDistanceDelta;
	}

	inline static Vector2f Scale(const Vector2f& a, const Vector2f& b)
	{
		return Vector2f(a.x * b.x, a.y * b.y);
	}

	inline static float SqrMagnitude(const Vector2f& a)
	{
		return a.x * a.x + a.y * a.y;
	}

	//
	// Methods
	//	
	inline void Normalize()
	{
		float magnitude = this->magnitude();
		if (magnitude > 1E-05f)
		{
			x /= magnitude;
			y /= magnitude;
		}
		else
		{
			x = y = 0.f;
		}
	}

	inline void Scale(const Vector2f& scale)
	{
		this->x *= scale.x;
		this->y *= scale.y;
	}

	inline void Set(float new_x, float new_y)
	{
		this->x = new_x;
		this->y = new_y;
	}

	inline float SqrMagnitude()
	{
		return this->x * this->x + this->y * this->y;
	}	
};

//
// Operators
//
inline static Vector2f operator +(const Vector2f& a, const Vector2f& b)
{
	return Vector2f(a.x + b.x, a.y + b.y);
}

inline static Vector2f operator /(const Vector2f& a, float d)
{
	return Vector2f(a.x / d, a.y / d);
}

inline static bool operator ==(const Vector2f& lhs, const Vector2f& rhs)
{
	return Vector2f::SqrMagnitude(lhs - rhs) < 9.99999944E-11f;
}

inline static bool operator !=(const Vector2f& lhs, const Vector2f& rhs)
{
	return Vector2f::SqrMagnitude(lhs - rhs) >= 9.99999944E-11f;
}

inline static Vector2f operator *(const Vector2f& a, float d)
{
	return Vector2f(a.x * d, a.y * d);
}

inline static Vector2f operator *(float d, const Vector2f& a)
{
	return Vector2f(a.x * d, a.y * d);
}

inline static Vector2f operator -(const Vector2f& a, const Vector2f& b)
{
	return Vector2f(a.x - b.x, a.y - b.y);
}

inline static Vector2f operator -(const Vector2f& a)
{
	return Vector2f(-a.x, -a.y);
}

#endif // __VECTOR2F_H__
