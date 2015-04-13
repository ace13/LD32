#include "Time.hpp"

using namespace Util;

#if defined(WIN32) && _MSC_VER <= 1800
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace
{
	const long long g_Frequency = []() -> long long
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		return frequency.QuadPart;
	}();
}

ClockImpl::time_point ClockImpl::now()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return time_point(duration(count.QuadPart * static_cast<rep>(period::den) / g_Frequency));
}
#endif
