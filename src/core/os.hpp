#ifndef ODIN_OS_HPP
#define ODIN_OS_HPP

#if defined(__WINDOWS__) || defined(_WIN32) || defined(__WIN32__)
	#define WINDOWS

	#ifdef _WIN32
		#define WINDOWS_32
	#elif _WIN64
		#define WINDOWS_64
	#endif

#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)
	#include "TargetConditionals.h"
	#define APPLE

	#if defined(__IPHONEOS__) || defined(TARGET_OS_IPHONE)
		#define IPHONE
		#define OPENGL_ES
		#define Mobile
		
		#if defined(TARGET_IPHONE_SIMULATOR)
			#define IPHONE_SIMULATOR
		#endif
	#endif

#elif defined(__ANDROID__)
	#define ANDROID
	#define OPENGL_ES
	#define Mobile

#elif defined(linux) || defined(__linux)
	#define LINUX
	
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
	#define FREEBSD
	
#elif __unix
	#define UNIX
	
#elif __posix
	#define POSIX
	
#endif

#endif