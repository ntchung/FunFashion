#ifndef __COLOR32_H__
#define __COLOR32_H__

#include <GLES2/gl2.h>
#include "maths/Mathf.h"

struct Color32
{
public:

	//
	// Fields
	//
	GLubyte b;
	GLubyte a;
	GLubyte r;
	GLubyte g;

	//
	// Constructors
	//
	Color32(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	//
	// Static Methods
	//
	inline static Color32 Lerp(const Color32& a, const Color32& b, float t)
	{
		t = Mathf::Clamp01(t);
		return Color32((GLubyte)((float)a.r + (float)(b.r - a.r) * t), (GLubyte)((float)a.g + (float)(b.g - a.g) * t), (GLubyte)((float)a.b + (float)(b.b - a.b) * t), (GLubyte)((float)a.a + (float)(b.a - a.a) * t));
	}
};

#endif // __COLOR32_H__
