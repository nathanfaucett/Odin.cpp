#ifndef ODIN_TYPEDEFS_HPP
#define ODIN_TYPEDEFS_HPP

namespace Odin {

	typedef float float32;
	typedef double float64;

	typedef short int int16;
	typedef int int32;
	typedef long int int64;

	typedef unsigned short int uint16;
	typedef unsigned int uint32;
	typedef unsigned long int uint64;

	typedef char char8;
	typedef char16_t char16;
	typedef char32_t char32;

	typedef unsigned char uchar8;
	
	#define BYTES_PER_INT16 sizeof(int16)
	#define BYTES_PER_INT32 sizeof(int32)
	#define BYTES_PER_INT64 sizeof(int64)
	
	#define BYTES_PER_FLOAT32 sizeof(float32)
	#define BYTES_PER_FLOAT64 sizeof(float64)
	
	#define BYTES_PER_UINT16 sizeof(uint16)
	#define BYTES_PER_UINT32 sizeof(uint32)
	#define BYTES_PER_UINT64 sizeof(uint64)
	
	#define BYTES_PER_CHAR8 sizeof(char8)
	#define BYTES_PER_CHAR16 sizeof(char16)
	#define BYTES_PER_CHAR32 sizeof(char32)
	#define BYTES_PER_UCHAR8 sizeof(uchar8)
}
#endif