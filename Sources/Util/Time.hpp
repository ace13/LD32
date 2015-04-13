#pragma once

#include <chrono>

namespace Util
{

#if defined(WIN32) && _MSC_VER <= 1800
	class ClockImpl
	{
	public:
		typedef long long                          rep;
		typedef std::nano                          period;
		typedef std::chrono::duration<rep, period> duration;
		typedef std::chrono::time_point<ClockImpl> time_point;
		static const bool is_steady = true;

		static time_point now();
	};
#else
	typedef std::chrono::high_resolution_clock ClockImpl;
#endif
	typedef ClockImpl::duration Timespan;
	typedef ClockImpl::time_point Timestamp;

}
