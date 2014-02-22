#ifndef __MATRIX4x4_H__
#define __MATRIX4x4_H__

struct Matrix4x4
{
public:
	static const Matrix4x4 identity;

	float m[16];

	Matrix4x4();
	Matrix4x4(float m00, float m10, float m20, float m30, float m01, float m11, float m21, float m31, float m02, float m12, float m22, float m32, float m03, float m13, float m23, float m33);
};

#endif // __MATRIX4x4_H__
