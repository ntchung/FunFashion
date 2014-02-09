#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <android/log.h>

#define MAX_LEN 256

void DebugLog::print(const char* format, ...)
{
	char buf[MAX_LEN];

    va_list args;
    va_start(args, format);
    vsnprintf(buf, MAX_LEN, format, args);
    va_end(args);

    __android_log_print(ANDROID_LOG_DEBUG, "fairycore", "%s", buf);
}
