#ifndef _ODIN_OS_HPP
#define _ODIN_OS_HPP

namespace Odin {
#if defined(__WINDOWS__) || defined(_WIN32) || defined(_WIN64)
#define WINDOWS

#ifdef _WIN32
#define WINDOWS_32
#elif _WIN64
#define WINDOWS_64
#endif

#elif __APPLE__
#define APPLE
#include "TargetConditionals.h"

#if TARGET_OS_IPHONE && TARGET_IPHONE_SIMULATOR
#define IPHONE_SIMULATOR
#elif TARGET_OS_IPHONE
#define IPHONE
#else
#define MAC
#endif

#elif __linux
#define LINUX
#elif __unix
#define UNIX
#elif __posix
#define POSIX
#endif
}

#endif