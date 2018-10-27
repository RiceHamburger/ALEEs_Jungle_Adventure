#ifndef DEBUG_PRINTF_H_
#define DEBUG_PRINTF_H_

#include <Windows.h>
#include <stdio.h>

inline void DebugPrintf(const char* pFormat, ...) {
#if defined(_DEBUG) || defined(DEBUG)
	va_list argp;
	char buf[256];
	va_start(argp, pFormat);
	vsprintf_s(buf, 256, pFormat, argp);
	va_end(argp);
	OutputDebugStringA(buf);
#endif // _DEBUG || DEBUG
}

#endif // DEBUG_PRINTF_H_