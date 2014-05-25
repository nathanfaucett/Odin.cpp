#ifndef ODIN_CORE_HPP
#define ODIN_CORE_HPP

#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <cstdio>
#include <string>
#include <functional>
#include <map>
#include <unordered_map>
#include <regex>
#include <cassert>

#include "typedefs.hpp"
#include "os.hpp"
#include "time.hpp"
#include "enums.hpp"

#define GLSL(version, src) (version >= 330 ? "#version " #version " core\n" #src : "#version " #version "\n" #src)
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

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
	
	inline std::string LoadFile(std::string filename) {
		std::ifstream in(filename, std::ios::in | std::ios::binary);
		
		if (in) {
			std::string contents;
			
			in.seekg(0, std::ios::end);
			contents.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&contents[0], contents.size());
			in.close();
			
			return contents;
		}
		
		throw(errno);
	}
}

#include "array.h"
#include "object.h"
#include "object_pool.h"

#include "array.cpp"
#include "object.cpp"
#include "object_pool.cpp"

#endif