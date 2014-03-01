#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "maths/Vector3f.h"

struct Quaternion
{
public:
	
	//
	// Static Fields
	//
	static const float kEpsilon;

	//
	// Fields
	//	
	float x;
	float y;
	float z;
	float w;

	//
	// Static Properties
	//
	static const Quaternion identity;
	
	//
	// Properties
	//
	inline Vector3f eulerAngles()
	{
		// TODO
		return Vector3f();
	}

	inline void setEulerAngles(const Vector3f& value)		
	{
		// TODO
	}

	//
	// Indexer
	//
	inline float& operator[](int index)
	{
		switch (index)
		{
		case 1:
			return this->y;
		case 2:
			return this->z;
		case 3:
			return this->w;
		}

		return this->x;
	}	

	//
	// Constructors
	//
	Quaternion(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	//
	// Static Methods
	//
	inline static float Angle(const Quaternion& a, const Quaternion& b)
	{
		float f = Quaternion::Dot(a, b);
		return Mathf::Acos(Mathf::Min(Mathf::Abs(f), 1.f)) * 2.f * 57.29578f;
	}

	inline static Quaternion AngleAxis(float angle, const Vector3f& axis)
	{
		// TODO
		return Quaternion::identity;
	}

	
	inline static float Dot(const Quaternion& a, const Quaternion& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	inline static Quaternion Euler(float x, float y, float z)
	{
		// TODO
		return Quaternion::identity;
	}

	inline static Quaternion Euler(Vector3f euler)
	{
		// TODO
		return Quaternion::identity;
	}

	inline static Quaternion FromToRotation(const Vector3f& fromDirection, const Vector3f& toDirection)
	{
		// TODO
		return Quaternion::identity;
	}

	inline static Quaternion Inverse(const Quaternion& rotation)
	{
		// TODO
		return Quaternion::identity;
	}

	inline static Quaternion Lerp(const Quaternion& from, const Quaternion& to, float t)
	{
		// TODO
		return Quaternion::identity;
	}

	inline static Quaternion LookRotation(const Vector3f& forward, const Vector3f& upwards = Vector3f::up)
	{
		// TODO
		return Quaternion::identity;
	}

	inline static Quaternion LookRotation(const Vector3f& forward)
	{
		// TODO
		Vector3f up = Vector3f::up;
		return Quaternion::identity;
	}

	inline static Quaternion RotateTowards(const Quaternion& from, const Quaternion& to, float maxDegreesDelta)
	{
		float num = Quaternion::Angle(from, to);
		if (num == 0.f)
		{
			return to;
		}
		float t = Mathf::Min(1.f, maxDegreesDelta / num);
		return Quaternion::UnclampedSlerp(from, to, t);
	}

	inline static Quaternion UnclampedSlerp(const Quaternion& from, const Quaternion& to, float t)
	{
		// TODO
		return Quaternion::identity;
	}

	inline static Quaternion Slerp(const Quaternion& from, const Quaternion& to, float t)
	{
		// TODO
		return Quaternion::identity;
	}
	
	//
	// Methods
	//	
	inline void Set(float new_x, float new_y, float new_z, float new_w)
	{
		this->x = new_x;
		this->y = new_y;
		this->z = new_z;
		this->w = new_w;
	}

	inline void SetFromToRotation(const Vector3f& fromDirection, const Vector3f& toDirection)
	{
		*this = Quaternion::FromToRotation(fromDirection, toDirection);
	}

	inline void SetLookRotation(const Vector3f& view, const Vector3f& up = Vector3f::up)
	{
		*this = Quaternion::LookRotation(view, up);
	}
	
	inline void SetLookRotation(const Vector3f& view)
	{
		Vector3f up = Vector3f::up;
		this->SetLookRotation(view, up);
	}

	inline void ToAngleAxis(float& angle, Vector3f& axis)
	{
		// TODO
		//Quaternion::Internal_ToAxisAngleRad(this, out axis, out angle);
		//angle *= 57.29578f;
	}	
};

//
// Operators
//
inline bool operator ==(const Quaternion& lhs, const Quaternion& rhs)
{
	return Quaternion::Dot(lhs, rhs) > 0.999999f;
}

inline bool operator !=(const Quaternion& lhs, const Quaternion& rhs)
{
	return Quaternion::Dot(lhs, rhs) <= 0.999999f;
}

inline Quaternion operator *(const Quaternion& lhs, const Quaternion& rhs)
{
	return Quaternion(lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y, lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z, lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x, lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z);
}

inline Vector3f operator *(const Quaternion& rotation, const Vector3f& point)
{
	float num = rotation.x * 2.f;
	float num2 = rotation.y * 2.f;
	float num3 = rotation.z * 2.f;
	float num4 = rotation.x * num;
	float num5 = rotation.y * num2;
	float num6 = rotation.z * num3;
	float num7 = rotation.x * num2;
	float num8 = rotation.x * num3;
	float num9 = rotation.y * num3;
	float num10 = rotation.w * num;
	float num11 = rotation.w * num2;
	float num12 = rotation.w * num3;

	Vector3f result;
	result.x = (1.f - (num5 + num6)) * point.x + (num7 - num12) * point.y + (num8 + num11) * point.z;
	result.y = (num7 + num12) * point.x + (1.f - (num4 + num6)) * point.y + (num9 - num10) * point.z;
	result.z = (num8 - num11) * point.x + (num9 + num10) * point.y + (1.f - (num4 + num5)) * point.z;
	return result;
}

#endif // __QUATERNION_H__
