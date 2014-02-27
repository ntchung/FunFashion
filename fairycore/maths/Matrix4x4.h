#ifndef __MATRIX4x4_H__
#define __MATRIX4x4_H__

#include "maths/Vector3f.h"

struct Matrix4x4
{
public:
	static const Matrix4x4 identity;

	float m[16];
	bool isIdentity;

	Matrix4x4();
	Matrix4x4(float m00, float m10, float m20, float m30, float m01, float m11, float m21, float m31, float m02, float m12, float m22, float m32, float m03, float m13, float m23, float m33, bool identity = false);

	void set(float m00, float m10, float m20, float m30, float m01, float m11, float m21, float m31, float m02, float m12, float m22, float m32, float m03, float m13, float m23, float m33, bool identity = false);
	void set(const Matrix4x4& value);
	void set(const float* value);
	int compare(const float* value) const;

	Vector3f rotate(const Vector3f& vec) const;

	inline Matrix4x4& operator = (const Matrix4x4& value) { set(value); return *this; }
	inline operator float*() { return this->m; }

	inline int operator==(const Matrix4x4& other) const { return compare(other.m); }

	Vector3f operator * (const Vector3f& vec) const;
	Matrix4x4 operator * (const Matrix4x4& mat) const;
};

#endif // __MATRIX4x4_H__
