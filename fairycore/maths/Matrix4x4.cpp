#include "stdafx.h"

const Matrix4x4 Matrix4x4::identity(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1,
	true
	);

Matrix4x4::Matrix4x4()
: isIdentity(true)
{
	set(identity);	
}

Matrix4x4::Matrix4x4(float m00, float m10, float m20, float m30, float m01, float m11, float m21, float m31, float m02, float m12, float m22, float m32, float m03, float m13, float m23, float m33, bool identity)
{
	set(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33, identity);
}

void Matrix4x4::set(float m00, float m10, float m20, float m30, float m01, float m11, float m21, float m31, float m02, float m12, float m22, float m32, float m03, float m13, float m23, float m33, bool identity)
{
	m[0]  = m00;	m[1]  = m10;	m[2]  = m20;	m[3]  = m30;
	m[4]  = m01;	m[5]  = m11;	m[6]  = m21;	m[7]  = m31;
	m[8]  = m02;	m[9]  = m12;	m[10] = m22;	m[11] = m32;
	m[12] = m03;	m[13] = m13;	m[14] = m23;	m[15] = m33;

	isIdentity = identity;
}

void Matrix4x4::set(const Matrix4x4& value)
{
	set(value.m);	
	isIdentity = value.isIdentity;
}

void Matrix4x4::set(const float* value)
{
	memcpy(this->m, value, 16 * sizeof(float));
	isIdentity = false;
}

int Matrix4x4::compare(const float* value) const
{
	return memcmp(this->m, value, 16 * sizeof(float));
}

Vector3f Matrix4x4::rotate(const Vector3f& vec) const
{
	if (isIdentity)
	{
		return vec;
	}

	return Vector3f(
		vec.x * m[0] + vec.y * m[4] + vec.z * m[8],
		vec.x * m[1] + vec.y * m[5] + vec.z * m[9],
		vec.x * m[2] + vec.y * m[6] + vec.z * m[10]
		);
}

Vector3f Matrix4x4::operator * (const Vector3f& vec) const
{
	if (isIdentity)
	{
		return vec;
	}

	return Vector3f(
	vec.x * m[0] + vec.y * m[4] + vec.z * m[8]  + m[12],
	vec.x * m[1] + vec.y * m[5] + vec.z * m[9]	+ m[13],
	vec.x * m[2] + vec.y * m[6] + vec.z * m[10] + m[14]
	);
}

Matrix4x4 Matrix4x4::operator * (const Matrix4x4& mat) const
{
	if (isIdentity)
	{
		return mat;
	}

	if (mat.isIdentity)
	{
		return *this;
	}

	const float* m1 = this->m;
	const float* m2 = mat.m;

	return Matrix4x4(
	m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2] + m1[12] * m2[3],
	m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2] + m1[13] * m2[3],
	m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3],
	m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3],

	m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6] + m1[12] * m2[7],
	m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6] + m1[13] * m2[7],
	m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7],
	m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7],

	m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10] + m1[12] * m2[11],
	m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10] + m1[13] * m2[11],
	m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10] + m1[14] * m2[11],
	m1[3] * m2[8] + m1[7] * m2[9] + m1[11] * m2[10] + m1[15] * m2[11],

	m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12] * m2[15],
	m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13] * m2[15],
	m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15],
	m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15]
	);
}
