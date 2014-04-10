#ifndef ODIN_UTIL_HPP
#define ODIN_UTIL_HPP

namespace Odin {

	class Util {

		private:

		public:

			inline std::string ToString(int32 x, int32 precision = 5) {
				std::ostringstream convert;
				convert << std::setprecision(precision) << x;
				return convert.str();
			}
			inline std::string ToString(uint32 x, int32 precision = 5) {
				std::ostringstream convert;
				convert << std::setprecision(precision) << x;
				return convert.str();
			}
			inline std::string ToString(float32 x, int32 precision = 5) {
				std::ostringstream convert;
				convert << std::setprecision(precision) << x;
				return convert.str();
			}
			inline std::string ToString(float64 x, int32 precision = 5) {
				std::ostringstream convert;
				convert << std::setprecision(precision) << x;
				return convert.str();
			}
			inline std::string ToString(bool x, int32 precision = 5) {

				return x ? "true" : "false";
			}
	} Util;
}

#endif