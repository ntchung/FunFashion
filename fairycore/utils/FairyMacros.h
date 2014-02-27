#ifndef __FAIRYMACROS_H__
#define __FAIRYMACROS_H__

#ifndef NULL
#define NULL 0
#endif

#define SAFE_DELETE(p)				do { if(p) { delete (p); (p) = 0; } } while(0)
#define SAFE_DELETE_ARRAY(p)		do { if(p) { delete[] (p); (p) = 0; } } while(0)
#define SAFE_RELEASE(p)				do { if(p) { (p)->release(); } } while(0)
#define SAFE_RELEASE_NULL(p)		do { if(p) { (p)->release(); (p) = 0; } } while(0)
#define SAFE_RETAIN(p)				do { if(p) { (p)->retain(); } } while(0)

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#define MIN_STRING_LENGTH	32
#define MAX_STRING_LENGTH	2048

#ifdef _DEBUG
#define ASSERT(_x)		assert(_x)
#else
#define ASSERT(_x)		((void)0)
#endif

#ifndef INT_MAX
#define INT_MAX       2147483647    /* maximum (signed) int value */
#endif

#define STREAM__BUFFER_SIZE				512

#define VERTEX_LIST_GROW_RATE			32

#define TRIANGLES_POOL_SIZE				4096

#define GL_RENDER_TYPE_OPAQUE			0x8D00
#define GL_RENDER_TYPE_TRANSPARENT		0x8D01

#endif // __FAIRYMACROS_H__
