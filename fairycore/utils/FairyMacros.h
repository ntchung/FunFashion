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
#define MAX_TEXTURE_UNITS				4

#define RENDER_QUEUE_GEOMETRY			10000
#define RENDER_QUEUE_TRANSPARENT		20000
#define RENDER_QUEUE_OVERLAY			40000

#define TRIANGLES_SORT_NONE					0
#define TRIANGLES_SORT_MATERIAL				1
#define TRIANGLES_SORT_BACK_TO_FRONT		2
#define TRIANGLES_SORT_TYPES_COUNT			3

#endif // __FAIRYMACROS_H__
