#ifndef __FAIRYTYPES_H__
#define __FAIRYTYPES_H__

#include <GLES2/gl2.h>

struct Color3B
{
	GLubyte red;
	GLubyte green;
	GLubyte blue;

	Color3B(GLubyte r, GLubyte g, GLubyte b)
		: red(r)
		, green(g)
		, blue(b)
	{
	}
};

struct Color4B
{
	GLubyte red;
	GLubyte green;
	GLubyte blue;
	GLubyte alpha;

	Color4B(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
		: red(r)
		, green(g)
		, blue(b)
		, alpha(a)
	{
	}
};

struct Color4F
{
	GLfloat red;
	GLfloat green;
	GLfloat blue;
	GLfloat alpha;

	Color4F(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
		: red(r)
		, green(g)
		, blue(b)
		, alpha(a)
	{
	}
};

#endif // __FAIRYTYPES_H__
