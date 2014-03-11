#include "stdafx.h"
#include <windows.h>

long long Timer::getRealTime()
{
	return GetTickCount();
}
