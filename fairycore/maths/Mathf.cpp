#include "stdafx.h"

// Mathf
const float Mathf::Deg2Rad = 0.0174532924f;
const float Mathf::Rad2Deg = 57.29578f;
const float Mathf::Epsilon = 1.401298E-45f;
const float Mathf::PI = 3.14159274f;
const float Mathf::Infinity = 1E+37f;
const float Mathf::NegativeInfinity = 1E-37f;


// Vector2f
const float Vector2f::kEpsilon = 1E-05f;
const Vector2f Vector2f::one(1.f, 1.f);
const Vector2f Vector2f::zero(0.f, 0.f);
const Vector2f Vector2f::right(1.f, 0.f);
const Vector2f Vector2f::up(0.f, 1.f);


// Vector3f
const float Vector3f::kEpsilon = 1E-05f;
const Vector3f Vector3f::zero(0.f, 0.f, 0.f);
const Vector3f Vector3f::one(1.f, 1.f, 1.f);
const Vector3f Vector3f::up(0.f, 1.f, 0.f);

// Quaternion
const float Quaternion::kEpsilon = 1E-06f;
const Quaternion Quaternion::identity(0.f, 0.f, 0.f, 1.f);
