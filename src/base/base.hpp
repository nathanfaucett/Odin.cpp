#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <cstdio>
#include <string>
#include <functional>
#include <assert.h>
#include <unordered_map>

#include "typedefs.hpp"
#include "os.hpp"
#include "time.hpp"

namespace Odin{
	
	inline std::string ToString(char8 x, int32 precision = 0) {
		std::ostringstream convert;
		convert << x;
		return convert.str();
	}
	inline std::string ToString(char16 x, int32 precision = 0) {
		std::ostringstream convert;
		convert << x;
		return convert.str();
	}
	inline std::string ToString(char32 x, int32 precision = 0) {
		std::ostringstream convert;
		convert << x;
		return convert.str();
	}

	inline std::string ToString(int16 x, int32 precision = 0) {
		std::ostringstream convert;
		convert << x;
		return convert.str();
	}
	inline std::string ToString(int32 x, int32 precision = 0) {
		std::ostringstream convert;
		convert << x;
		return convert.str();
	}
	inline std::string ToString(int64 x, int32 precision = 0) {
		std::ostringstream convert;
		convert << x;
		return convert.str();
	}
	
	inline std::string ToString(uint16 x, int32 precision = 0) {
		std::ostringstream convert;
		return convert.str();
	}
	inline std::string ToString(uint32 x, int32 precision = 0) {
		std::ostringstream convert;
		convert << x;
		return convert.str();
	}
	inline std::string ToString(uint64 x, int32 precision = 0) {
		std::ostringstream convert;
		convert << x;
		return convert.str();
	}
	
	inline std::string ToString(float32 x, int32 precision = 16) {
		std::ostringstream convert;
		convert << std::setprecision(precision) << x;
		return convert.str();
	}
	inline std::string ToString(float64 x, int32 precision = 32) {
		std::ostringstream convert;
		convert << std::setprecision(precision) << x;
		return convert.str();
	}
	
	inline std::string ToString(bool x, int32 precision = 0) {

		return x ? "true" : "false";
	}
}

#include "array.h"
#include "object.h"
#include "object_pool.h"

#include "array.cpp"
#include "object.cpp"
#include "object_pool.cpp"

#endif