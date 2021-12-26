/*
 * Common.cpp
 *
 *  Created on: Nov 27, 2013
 *      Author: cfyz
 */

#include "Common.hpp"

#if defined(_WIN32)

uint64_t GetTime()
{
	// Equivalent: std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	// return timeGetTime();
	return 0;
}
#endif
#if defined(__linux) || defined(__APPLE__)
#include <unistd.h>
#include <sys/time.h>
uint64_t GetTime()
{
	timeval t;
	gettimeofday(&t, nullptr);
	return t.tv_sec*1000 + t.tv_usec/1000;
}
#endif
