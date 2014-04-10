#ifndef ODIN_OS_HPP
#define ODIN_OS_HPP

namespace Odin {
#if defined(__WINDOWS__) || defined(_WIN32) || defined(__WIN32__)
#define WINDOWS

#ifdef _WIN32
#define WINDOWS_32
#elif _WIN64
#define WINDOWS_64
#endif

#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)
#define APPLE
#include "TargetConditionals.h"

#if TARGET_OS_IPHONE && TARGET_IPHONE_SIMULATOR
#define IPHONE
#define IPHONE_SIMULATOR
#elif TARGET_OS_IPHONE
#define IPHONE
#else
#define MAC
#endif

#elif defined(linux) || defined(__linux)
#define LINUX
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
#define FREEBSD
#elif __unix
#define UNIX
#elif __posix
#define POSIX
#endif
}

#endif