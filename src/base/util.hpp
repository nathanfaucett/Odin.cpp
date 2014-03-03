#ifndef _ODIN_UTIL_HPP
#define _ODIN_UTIL_HPP

namespace Odin {

	class util {

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

			inline float32 Test(std::function<void()> fn, int32 times = 1000) {
				float32 start = 0.0f, avg = 0.0f,
				        d = 1.0f / float32(times);

				for (int32 i = 0; i < times; i++) {
					start = Time.Now();
					fn();
					avg += Time.Now() - start;
				}

				return (avg * d);
			}
	};

	util util;
}

#endif