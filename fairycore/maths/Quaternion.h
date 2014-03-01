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
		float sqw = w * w;
		float sqx = x * x;
		float sqy = y * y;
		float sqz = z * z;
		float unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
		float test = x * y + z * w;

		float heading, attitude, bank;

		if (test > 0.499f * unit)
		{ 
			// singularity at north pole
			heading = 2.f * (float)Mathf::Atan2(x, w);
			attitude = (float)Mathf::PI / 2.f;
			bank = 0.f;
		}
		else if (test < -0.499 * unit)
		{ 
			// singularity at south pole
			heading = -2.f * (float)Mathf::Atan2(x, w);
			attitude = -(float)Mathf::PI / 2.f;
			bank = 0.f;
		}
		else
		{
			heading = (float)Mathf::Atan2(2.f * y * w - 2.f * x * z, sqx - sqy - sqz + sqw);
			attitude = (float)Mathf::Asin(2.f * test / unit);
			bank = (float)Mathf::Atan2(2.f * x * w - 2.f * y * z, -sqx + sqy - sqz + sqw);
		}

		return Vector3f(bank * Mathf::Rad2Deg, heading * Mathf::Rad2Deg, attitude * Mathf::Rad2Deg);
	}

	inline void setEulerAngles(float tx, float ty, float tz)
	{
		float theta_z = tz * Mathf::Deg2Rad;
		float theta_x = tx * Mathf::Deg2Rad;
		float theta_y = ty * Mathf::Deg2Rad;

		float cos_z_2 = Mathf::Cos(0.5f*theta_z);
		float cos_y_2 = Mathf::Cos(0.5f*theta_y);
		float cos_x_2 = Mathf::Cos(0.5f*theta_x);

		float sin_z_2 = Mathf::Sin(0.5f*theta_z);
		float sin_y_2 = Mathf::Sin(0.5f*theta_y);
		float sin_x_2 = Mathf::Sin(0.5f*theta_x);

		// and now compute quaternion
		w = cos_z_2*cos_y_2*cos_x_2 + sin_z_2*sin_y_2*sin_x_2;
		x = cos_z_2*cos_y_2*sin_x_2 - sin_z_2*sin_y_2*cos_x_2;
		y = cos_z_2*sin_y_2*cos_x_2 + sin_z_2*cos_y_2*sin_x_2;
		z = sin_z_2*cos_y_2*cos_x_2 - cos_z_2*sin_y_2*sin_x_2;
	}

	inline void setEulerAngles(const Vector3f& value)
	{
		setEulerAngles(value.x, value.y, value.z);
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
	Quaternion()
		: x(0)
		, y(0)
		, z(0)
		, w(1)
	{
	}

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
		return Mathf::Acos(Mathf::Min(Mathf::Abs(f), 1.f)) * 2.f * Mathf::Rad2Deg;
	}

	inline static Quaternion AngleAxis(float angle, const Vector3f& axis)
	{
		const float fHalfAngle = 0.5f * angle * Mathf::Deg2Rad;
		const float fSin = Mathf::Sin(fHalfAngle);

		return Quaternion(
			fSin * axis.x,
			fSin * axis.y,
			fSin * axis.z,
			Mathf::Cos(fHalfAngle));
	}

	
	inline static float Dot(const Quaternion& a, const Quaternion& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	inline static Quaternion Euler(float x, float y, float z)
	{		
		Quaternion res;
		res.setEulerAngles(x, y, z);
		return res;
	}

	inline static Quaternion Euler(const Vector3f& euler)
	{
		Quaternion res;
		res.setEulerAngles(euler);
		return res;
	}

	inline static Quaternion FromToRotation(const Vector3f& fromDirection, const Vector3f& toDirection)
	{
		// Based on Stan Melax's article in Game Programming Gems
		Quaternion q;

		// Copy, since cannot modify local
		Vector3f v0 = fromDirection;
		Vector3f v1 = toDirection;
		v0.Normalize();
		v1.Normalize();

		float d = Vector3f::Dot(v0, v1);

		// If dot == 1, vectors are the same
		if (d >= 1.f)
		{
			return identity;
		}

		if (d < (1e-6f - 1.f))
		{			
			// Generate an axis
			Vector3f axis = Vector3f::Cross(Vector3f::right, fromDirection);
			if (axis.sqrMagnitude() == 0.f)
			{
				// pick another if colinear
				axis = Vector3f::Cross(Vector3f::up, fromDirection);
			}				
			axis.Normalize();

			q = Quaternion::AngleAxis(Mathf::PI * Mathf::Rad2Deg, axis);			
		}
		else
		{
			float s = Mathf::Sqrt((1 + d) * 2);
			float invs = 1.f / s;

			Vector3f c = Vector3f::Cross(v0, v1);

			q.x = c.x * invs;
			q.y = c.y * invs;
			q.z = c.z * invs;
			q.w = s * 0.5f;
			q.Normalize();
		}

		return q;
	}

	inline static Quaternion Inverse(const Quaternion& rotation)
	{
		float d = 1.f / (rotation.w * rotation.w + rotation.x * rotation.x + rotation.y * rotation.y + rotation.z * rotation.z);
		return Quaternion(-rotation.x * d, -rotation.y * d, -rotation.z * d, rotation.w * d);
	}

	inline static Quaternion Lerp(const Quaternion& from, const Quaternion& to, float t)
	{
		const float it = 1.f - t;
		return Quaternion(
			from.x * it + to.x * t,
			from.y * it + to.y * t,
			from.z * it + to.z * t,
			from.w * it + to.w * t
			);
	}

	inline static Quaternion LookRotation(const Vector3f& forward, const Vector3f& upwards = Vector3f::up)
	{
		Vector3f vector = Vector3f::Normalize(forward);
		Vector3f vector2 = Vector3f::Normalize(Vector3f::Cross(upwards, vector));
		Vector3f vector3 = Vector3f::Cross(vector, vector2);

		float m00 = vector2.x;
		float m01 = vector2.y;
		float m02 = vector2.z;
		float m10 = vector3.x;
		float m11 = vector3.y;
		float m12 = vector3.z;
		float m20 = vector.x;
		float m21 = vector.y;
		float m22 = vector.z;

		float num8 = (m00 + m11) + m22;
		Quaternion quaternion;
		if (num8 > 0.f)
		{
			float num = (float)Mathf::Sqrt(num8 + 1.f);
			quaternion.w = num * 0.5f;
			num = 0.5f / num;
			quaternion.x = (m12 - m21) * num;
			quaternion.y = (m20 - m02) * num;
			quaternion.z = (m01 - m10) * num;
			return quaternion;
		}
		if ((m00 >= m11) && (m00 >= m22))
		{
			float num7 = (float)Mathf::Sqrt(((1.f + m00) - m11) - m22);
			float num4 = 0.5f / num7;
			quaternion.x = 0.5f * num7;
			quaternion.y = (m01 + m10) * num4;
			quaternion.z = (m02 + m20) * num4;
			quaternion.w = (m12 - m21) * num4;
			return quaternion;
		}
		if (m11 > m22)
		{
			float num6 = (float)Mathf::Sqrt(((1.f + m11) - m00) - m22);
			float num3 = 0.5f / num6;
			quaternion.x = (m10 + m01) * num3;
			quaternion.y = 0.5f * num6;
			quaternion.z = (m21 + m12) * num3;
			quaternion.w = (m20 - m02) * num3;
			return quaternion;
		}
		float num5 = (float)Mathf::Sqrt(((1.f + m22) - m00) - m11);
		float num2 = 0.5f / num5;
		quaternion.x = (m20 + m02) * num2;
		quaternion.y = (m21 + m12) * num2;
		quaternion.z = 0.5f * num5;
		quaternion.w = (m01 - m10) * num2;
		return quaternion;
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
		return Slerp(from, to, t);
	}

	inline static Quaternion Slerp(const Quaternion& from, const Quaternion& to, float t)
	{
		// Check for out-of range parameter and return edge points if so
		if (t <= 0.f)
		{			
			return from;
		}

		if (t >= 1.f)
		{
			return to;
		}

		// Compute "cosine of angle between quaternions" using dot product
		float cosOmega = Dot(from, to);

		// If negative dot, use -q1.  Two quaternions q and -q
		// represent the same rotation, but may produce
		// different slerp.  We chose q or -q to rotate using
		// the acute angle.
		float q1w = to.w;
		float q1x = to.x;
		float q1y = to.y;
		float q1z = to.z;

		if (cosOmega < 0.f)
		{
			q1w = -q1w;
			q1x = -q1x;
			q1y = -q1y;
			q1z = -q1z;
			cosOmega = -cosOmega;
		}

		// We should have two unit quaternions, so dot should be <= 1.0
		// ASSERT(cosOmega < 1.1.f);

		// Compute interpolation fraction, checking for quaternions
		// almost exactly the same
		float k0, k1;

		if (cosOmega > 0.9999f)
		{
			// Very close - just use linear interpolation,
			// which will protect againt a divide by zero

			k0 = 1.f - t;
			k1 = t;
		}
		else
		{
			// Compute the sin of the angle using the
			// trig identity sin^2(omega) + cos^2(omega) = 1 
			float sinOmega = Mathf::Sqrt(1.f - (cosOmega * cosOmega));

			// Compute the angle from its sin and cosine
			float omega = Mathf::Atan2(sinOmega, cosOmega);

			// Compute inverse of denominator, so we only have
			// to divide once
			float oneOverSinOmega = 1.f / (sinOmega);

			// Compute interpolation parameters
			k0 = Mathf::Sin((1.f - t) * omega) * oneOverSinOmega;
			k1 = Mathf::Sin(t * omega) * oneOverSinOmega;
		}

		// Interpolate and return new quaternion
		return Quaternion(
			(k0 * from.x) + (k1 * q1x),
			(k0 * from.y) + (k1 * q1y),
			(k0 * from.z) + (k1 * q1z),
			(k0 * from.w) + (k1 * q1w));
	}
	
	//
	// Methods
	//	
	inline void Normalize()
	{
		float sqrlen = w * w + x * x + y * y + z * z;

		if (sqrlen == 0.f)
		{
			w = 1;
			x = 0;
			y = 0;
			z = 0;
			return;
		}

		float invlen = 1.f / (sqrlen);
		w *= invlen;
		x *= invlen;
		y *= invlen;
		z *= invlen;
	}

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
		const float scale = Mathf::Sqrt(x * x + y * y + z * z);

		if (scale == 0.f || w > 1.f || w < -1.f)
		{
			angle = 0.f;
			axis.x = 0.f;
			axis.y = 1.f;
			axis.z = 0.f;
		}
		else
		{
			const float invscale = 1.f / scale;
			angle = 2.f * Mathf::Acos(w) * Mathf::Rad2Deg;
			axis.x = x * invscale;
			axis.y = y * invscale;
			axis.z = z * invscale;
		}
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
