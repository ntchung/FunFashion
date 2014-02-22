#include "stdafx.h"

const Matrix4x4 Matrix4x4::identity(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
	);

Matrix4x4::Matrix4x4()
{
}

Matrix4x4::Matrix4x4(float m00, float m10, float m20, float m30, float m01, float m11, float m21, float m31, float m02, float m12, float m22, float m32, float m03, float m13, float m23, float m33)
{
	m[0]  = m00;	m[1]  = m10;	m[2]  = m20;	m[3]  = m30;
	m[4]  = m01;	m[5]  = m11;	m[6]  = m21;	m[7]  = m31;
	m[8]  = m02;	m[9]  = m12;	m[10] = m22;	m[11] = m32;
	m[12] = m03;	m[13] = m13;	m[14] = m23;	m[15] = m33;
}
