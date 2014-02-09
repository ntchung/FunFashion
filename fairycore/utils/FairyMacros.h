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

#define MIN_STRING_LENGTH	16
#define MAX_STRING_LENGTH	1024

#endif // __FAIRYMACROS_H__
