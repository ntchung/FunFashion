#include "stdafx.h"
#include <windows.h>

long long Timer::getRealTime()
{
	struct timespec res;
    clock_gettime(CLOCK_REALTIME, &res);
    return 1000*res.tv_sec + ( res.tv_nsec/1e6 );
}
