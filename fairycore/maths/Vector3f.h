#ifndef __VECTOR3F_H__
#define __VECTOR3F_H__

#include "maths/Mathf.h"

struct Vector3f;

inline Vector3f operator +(const Vector3f& a, const Vector3f& b);
inline Vector3f operator /(const Vector3f& a, float d);
inline bool operator ==(const Vector3f& lhs, const Vector3f& rhs);
inline bool operator !=(const Vector3f& lhs, const Vector3f& rhs);
inline Vector3f operator *(const Vector3f& a, float d);
inline Vector3f operator *(float d, const Vector3f& a);
inline Vector3f operator -(const Vector3f& a, const Vector3f& b);
inline Vector3f operator -(const Vector3f& a);

struct Vector3f
{
public:
	//
	// Static Fields
	//
	static const float kEpsilon;
	static const Vector3f zero;
	static const Vector3f one;
	static const Vector3f up;
	static const Vector3f forward;
	static const Vector3f right;
	
	//
	// Fields
	//
	float z;
	float y;
	float x;

	//
	// Static Properties
	//
	static inline Vector3f back()
	{
		return Vector3f(0.f, 0.f, -1.f);
	}

	static inline Vector3f down()
	{
		return Vector3f(0.f, -1.f, 0.f);
	}

	static inline Vector3f left()
	{
		return Vector3f(-1.f, 0.f, 0.f);
	}

	//
	// Properties
	//
	inline float magnitude() const
	{
		return Mathf::Sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	inline Vector3f normalized() const
	{
		return Vector3f::Normalize(*this);
	}

	inline float sqrMagnitude() const
	{
		return x * x + y * y + z * z;
	}

	//
	// Indexer
	//
	inline float& operator[](int index)
	{
		switch (index)
		{
		case 1:
			return y;
		case 2:
			return z;
		}

		return x;
	}

	//
	// Constructors
	//
	Vector3f()
		: x(0)
		, y(0)
		, z(0)
	{
	}

	Vector3f(float nx, float ny)
		: x(nx)
		, y(ny)
		, z(0.f)
	{		
	}

	Vector3f(float nx, float ny, float nz)
		: x(nx)
		, y(ny)
		, z(nz)
	{		
	}

	//
	// Static Methods
	//
	static inline float Angle(const Vector3f& from, const Vector3f& to)
	{
		return Mathf::Acos(Mathf::Clamp(Vector3f::Dot(from.normalized(), to.normalized()), -1.f, 1.f)) * 57.29578f;
	}
	
	static inline Vector3f ClampMagnitude(const Vector3f& vector, float maxLength)
	{
		if (vector.sqrMagnitude() > maxLength * maxLength)
		{
			return vector.normalized() * maxLength;
		}
		return vector;
	}

	static inline Vector3f Cross(const Vector3f& lhs, const Vector3f& rhs)
	{
		return Vector3f(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x);
	}

	static inline float Distance(const Vector3f& a, const Vector3f& b)
	{
		Vector3f vector(a.x - b.x, a.y - b.y, a.z - b.z);
		return Mathf::Sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	}

	static inline float Dot(const Vector3f& lhs, const Vector3f& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	static inline Vector3f Exclude(const Vector3f& excludeThis, const Vector3f& fromThat)
	{
		return fromThat - Vector3f::Project(fromThat, excludeThis);
	}

	static inline Vector3f Lerp(const Vector3f& from, const Vector3f& to, float t)
	{
		t = Mathf::Clamp01(t);
		return Vector3f(from.x + (to.x - from.x) * t, from.y + (to.y - from.y) * t, from.z + (to.z - from.z) * t);
	}

	static inline float Magnitude(const Vector3f& a)
	{
		return Mathf::Sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	}

	static inline Vector3f Max(const Vector3f& lhs, const Vector3f& rhs)
	{
		return Vector3f(Mathf::Max(lhs.x, rhs.x), Mathf::Max(lhs.y, rhs.y), Mathf::Max(lhs.z, rhs.z));
	}

	static inline Vector3f Min(const Vector3f& lhs, const Vector3f& rhs)
	{
		return Vector3f(Mathf::Min(lhs.x, rhs.x), Mathf::Min(lhs.y, rhs.y), Mathf::Min(lhs.z, rhs.z));
	}

	static inline Vector3f MoveTowards(const Vector3f& current, const Vector3f& target, float maxDistanceDelta)
	{
		Vector3f a = target - current;
		float magnitude = a.magnitude();
		if (magnitude <= maxDistanceDelta || magnitude == 0.f)
		{
			return target;
		}
		return current + a / magnitude * maxDistanceDelta;
	}

	static inline Vector3f Normalize(const Vector3f& value)
	{
		float num = Vector3f::Magnitude(value);
		if (num > 1E-05f)
		{
			return value / num;
		}
		return Vector3f::zero;
	}

	static inline void OrthoNormalize(Vector3f& normal, Vector3f& tangent, Vector3f& binormal)
	{
		Vector3f norm, tan, binorm;

		normal.Normalize();
		norm = normal;
		tan = tangent.normalized();

		Vector3f temp = Vector3f::Cross(norm, tan);
		tangent = Vector3f::Cross(temp, norm);
		tangent.Normalize();

		binormal = Vector3f::Cross(norm, tangent);
		binormal.Normalize();
	}

	static inline void OrthoNormalize(Vector3f& normal, Vector3f& tangent)
	{
		normal.Normalize();
		Vector3f norm = normal;
		Vector3f tan = tangent.normalized();

		tangent = tan - (norm * Vector3f::Dot(norm, tan));
		tangent.Normalize();
	}

	static inline Vector3f Project(const Vector3f& vector, const Vector3f& onNormal)
	{
		float num = Vector3f::Dot(onNormal, onNormal);
		if (num < 1.401298E-45f)
		{
			return Vector3f::zero;
		}
		return onNormal * Vector3f::Dot(vector, onNormal) / num;
	}

	static inline Vector3f Reflect(const Vector3f& inDirection, const Vector3f& inNormal)
	{
		return -2.f * Vector3f::Dot(inNormal, inDirection) * inNormal + inDirection;
	}

	static inline Vector3f RotateTowards(const Vector3f& current, const Vector3f& target, float maxRadiansDelta, float maxMagnitudeDelta)
	{
		// TODO
	}

	static inline Vector3f Scale(const Vector3f& a, const Vector3f& b)
	{
		return Vector3f(a.x * b.x, a.y * b.y, a.z * b.z);
	}

	static inline Vector3f Slerp(const Vector3f& from, const Vector3f& to, float t)
	{
		float dot = Vector3f::Dot(from, to);

		if (dot < -1.0f) dot = -1.0f;
		if (dot > 1.0f) dot = 1.0f;

		float theta = Mathf::Acos(dot) * t;
		Vector3f relative = (to - (from * dot));
		relative.Normalize();

		return ((from * Mathf::Cos(theta)) + (relative * Mathf::Sin(theta)));
	}
	
	// TODO
	/*
	static inline Vector3f SmoothDamp(Vector3f current, Vector3f target, ref Vector3f currentVelocity, float smoothTime)
	{
		float deltaTime = Time.deltaTime;
		float maxSpeed = float.PositiveInfinity;
		return Vector3f::SmoothDamp(current, target, ref currentVelocity, smoothTime, maxSpeed, deltaTime);
	}

	static inline Vector3f SmoothDamp(Vector3f current, Vector3f target, ref Vector3f currentVelocity, float smoothTime, [DefaultValue("Mathf::Infinity")] float maxSpeed, [DefaultValue("Time.deltaTime")] float deltaTime)
	{
		smoothTime = Mathf::Max(0.0001f, smoothTime);
		float num = 2.f / smoothTime;
		float num2 = num * deltaTime;
		float d = 1.f / (1.f + num2 + 0.48f * num2 * num2 + 0.235f * num2 * num2 * num2);
		Vector3f vector = current - target;
		Vector3f vector2 = target;
		float maxLength = maxSpeed * smoothTime;
		vector = Vector3f::ClampMagnitude(vector, maxLength);
		target = current - vector;
		Vector3f vector3 = (currentVelocity + num * vector) * deltaTime;
		currentVelocity = (currentVelocity - num * vector3) * d;
		Vector3f vector4 = target + (vector + vector3) * d;
		if (Vector3f::Dot(vector2 - current, vector4 - vector2) > 0.f)
		{
			vector4 = vector2;
			currentVelocity = (vector4 - vector2) / deltaTime;
		}
		return vector4;
	}
	
	[ExcludeFromDocs]
	static inline Vector3f SmoothDamp(Vector3f current, Vector3f target, ref Vector3f currentVelocity, float smoothTime, float maxSpeed)
	{
		float deltaTime = Time.deltaTime;
		return Vector3f::SmoothDamp(current, target, ref currentVelocity, smoothTime, maxSpeed, deltaTime);
	}
	*/

	static inline float SqrMagnitude(const Vector3f& a)
	{
		return a.x * a.x + a.y * a.y + a.z * a.z;
	}
	
	//
	// Methods
	//	
	inline void Normalize()
	{
		float num = Vector3f::Magnitude(*this);
		if (num > 1E-05f)
		{
			x /= num;
			y /= num;
			z /= num;
		}
		else
		{
			x = y = z = 0.f;
		}
	}

	inline void Scale(const Vector3f& scale)
	{
		this->x *= scale.x;
		this->y *= scale.y;
		this->z *= scale.z;
	}

	inline void Set(float new_x, float new_y, float new_z)
	{
		this->x = new_x;
		this->y = new_y;
		this->z = new_z;
	}

	inline Vector3f& operator = (const Vector3f& value) 
	{ 
		x = value.x;
		y = value.y;
		z = value.z;
		return *this; 
	}
};

//
// Operators
//
inline Vector3f operator +(const Vector3f& a, const Vector3f& b)
{
	return Vector3f(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline Vector3f operator /(const Vector3f& a, float d)
{
	return Vector3f(a.x / d, a.y / d, a.z / d);
}

inline bool operator ==(const Vector3f& lhs, const Vector3f& rhs)
{
	return Vector3f::SqrMagnitude(lhs - rhs) < 9.99999944E-11f;
}

inline bool operator !=(const Vector3f& lhs, const Vector3f& rhs)
{
	return Vector3f::SqrMagnitude(lhs - rhs) >= 9.99999944E-11f;
}

inline Vector3f operator *(const Vector3f& a, float d)
{
	return Vector3f(a.x * d, a.y * d, a.z * d);
}

inline Vector3f operator *(float d, const Vector3f& a)
{
	return Vector3f(a.x * d, a.y * d, a.z * d);
}

inline Vector3f operator -(const Vector3f& a, const Vector3f& b)
{
	return Vector3f(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline Vector3f operator -(const Vector3f& a)
{
	return Vector3f(-a.x, -a.y, -a.z);
}

#endif // __VECTOR3F_H__
