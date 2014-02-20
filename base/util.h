#ifndef ODIN_UTIL_H
#define ODIN_UTIL_H

namespace Odin{
	
	struct util{
		
		private:
			
		public:
			
			inline std::string ToString(int x, int precision = 5) {
				std::ostringstream convert;
				convert << std::setprecision(precision) << x;
				return convert.str();
			}
			inline std::string ToString(float x, int precision = 5) {
				std::ostringstream convert;
				convert << std::setprecision(precision) << x;
				return convert.str();
			}
			inline std::string ToString(double x, int precision = 5) {
				std::ostringstream convert;
				convert << std::setprecision(precision) << x;
				return convert.str();
			}
			inline std::string ToString(bool x, int precision = 5) {
				
				return x ? "true" : "false";
			}
	};
	
	util util;
}

#endif