#ifndef ODIN_MATHF_HPP
#define ODIN_MATHF_HPP


#include <cmath>
#include <climits>
#include <cfloat>
#include <cstdarg>


namespace Odin {

	template <typename Type> class AABB2;
	template <typename Type> class AABB3;
	template <typename Type> class Color;
	template <typename Type> class Mat2;
	template <typename Type> class Mat32;
	template <typename Type> class Mat3;
	template <typename Type> class Mat4;
	template <typename Type> class Mat43;
	template <typename Type> class Quat;
	template <typename Type> class Vec2;
	template <typename Type> class Vec3;
	template <typename Type> class Vec4;

	typedef Color<int32> Colori;
	typedef Color<float32> Colorf;

	typedef AABB2<int32> AABB2i;
	typedef AABB2<float32> AABB2f;

	typedef AABB3<int32> AABB3i;
	typedef AABB3<float32> AABB3f;

	typedef Vec2<int32> Vec2i;
	typedef Vec2<float32> Vec2f;

	typedef Vec3<int32> Vec3i;
	typedef Vec3<float32> Vec3f;

	typedef Vec4<int32> Vec4i;
	typedef Vec4<float32> Vec4f;

	typedef Quat<float32> Quatf;

	typedef Mat2<float32> Mat2f;
	typedef Mat32<float32> Mat32f;
	typedef Mat3<float32> Mat3f;
	typedef Mat4<float32> Mat4f;
	typedef Mat43<float32> Mat43f;

	constexpr float32 POS_INFINITY = INFINITY;
	constexpr float32 NEG_INFINITY = -INFINITY;

	constexpr float32 MAX_FLOAT32 = FLT_MAX;
	constexpr float32 MIN_FLOAT32 = FLT_MIN;
	constexpr float64 MAX_FLOAT64 = DBL_MAX;
	constexpr float64 MIN_FLOAT64 = DBL_MIN;

	constexpr int16 MAX_INT16 = SHRT_MAX;
	constexpr int16 MIN_INT16 = SHRT_MIN;
	constexpr int32 MAX_INT32 = INT_MAX;
	constexpr int32 MIN_INT32 = INT_MIN;
	constexpr int64 MAX_INT64 = LONG_MAX;
	constexpr int64 MIN_INT64 = LONG_MIN;

	constexpr uint16 MAX_UINT16 = USHRT_MAX;
	constexpr uint32 MAX_UINT32 = UINT_MAX;
	constexpr uint64 MAX_UINT64 = ULONG_MAX;
	
	template<typename Type> inline Type MIN_NUMBER(void) {
		return std::numeric_limits<Type>::min();
	}
	template<typename Type> inline Type MAX_NUMBER(void) {
		return std::numeric_limits<Type>::max();
	}

	class Mathf {

		public:
			static constexpr float32 PI = 3.14159265358979323846f;
			static constexpr float32 FOURTH_PI = PI * 0.25f;
			static constexpr float32 HALF_PI = PI * 0.5f;
			static constexpr float32 TWO_PI = PI * 2.0f;

			static constexpr float64 PI_64 = 3.1415926535897932384626433832795028841972;
			static constexpr float64 FOURTH_PI_64 = PI_64 * 0.25;
			static constexpr float64 HALF_PI_64 = PI_64 * 0.5;
			static constexpr float64 TWO_PI_64 = PI_64 * 2.0;

			static constexpr float32 Epsilon = FLT_EPSILON;
			static constexpr float64 Epsilon_64 = DBL_EPSILON;

			static constexpr float32 E = 2.71828182845904523536f;
			static constexpr float32 SQRT2 = 1.41421356237309504880f;
			static constexpr float32 SQRT1_2 = 0.70710676908493041992f;
			static constexpr float32 SQRT3 = 1.73205080756887729352f;

			static constexpr float32 TO_DEGS = 180.0f / PI;
			static constexpr float32 TO_RADS = PI / 180.0f;

			static constexpr float64 TO_DEGS_64 = 180.0 / PI_64;
			static constexpr float64 TO_RADS_64 = PI_64 / 180.0;
			
			inline void Init() {
				std::srand(std::time(0));
			}

			inline int16 Abs(int16 x) {
				return x < static_cast<int16>(0) ? -x : x;
			}
			inline int32 Abs(int32 x) {
				return x < static_cast<int32>(0) ? -x : x;
			}
			inline int64 Abs(int64 x) {
				return x < static_cast<int64>(0) ? -x : x;
			}
			inline float32 Abs(float32 x) {
				return x < 0.0f ? -x : x;
			}
			inline float64 Abs(float64 x) {
				return x < 0.0 ? -x : x;
			}

			inline int16 Pow(int16 x, int16 y) {
				int16 r;

				for (r = x; y > static_cast<int16>(1); y--) {
					r *= x;
				}

				return r;
			}
			inline int32 Pow(int32 x, int32 y) {
				int32 r;

				for (r = x; y > static_cast<int32>(1); y--) {
					r *= x;
				}

				return r;
			}
			inline int64 Pow(int64 x, int64 y) {
				int64 r;

				for (r = x; y > static_cast<int64>(1); y--) {
					r *= x;
				}

				return r;
			}
			inline float32 Pow(float32 x, float32 y) {
				return powf(x, y);
			}
			inline float64 Pow(float64 x, float64 y) {
				return pow(x, y);
			}
			
			inline int16 Min(int16 a, int16 b) {
				return a < b ? a : b;
			}
			inline int32 Min(int32 a, int32 b) {
				return a < b ? a : b;
			}
			inline int64 Min(int64 a, int64 b) {
				return a < b ? a : b;
			}
			inline float32 Min(float32 a, float32 b) {
				return a < b ? a : b;
			}
			inline float64 Min(float64 a, float64 b) {
				return a < b ? a : b;
			}
			
			inline int16 Max(int16 a, int16 b) {
				return a > b ? a : b;
			}
			inline int32 Max(int32 a, int32 b) {
				return a > b ? a : b;
			}
			inline int64 Max(int64 a, int64 b) {
				return a > b ? a : b;
			}
			inline float32 Max(float32 a, float32 b) {
				return a > b ? a : b;
			}
			inline float64 Max(float64 a, float64 b) {
				return a > b ? a : b;
			}

			inline int16 Sqrt(int16 x) {
				return static_cast<int16>(sqrtf(static_cast<float32>(x)));
			}
			inline int32 Sqrt(int32 x) {
				return static_cast<int32>(sqrtf(static_cast<float32>(x)));
			}
			inline int64 Sqrt(int64 x) {
				return static_cast<int64>(sqrt(static_cast<float64>(x)));
			}
			inline float32 Sqrt(float32 x) {
				return sqrtf(x);
			}
			inline float64 Sqrt(float64 x) {
				return sqrt(x);
			}

			inline int16 Log(int16 x) {
				return static_cast<int16>(logf(static_cast<float32>(x)));
			}
			inline int32 Log(int32 x) {
				return static_cast<int32>(logf(static_cast<float32>(x)));
			}
			inline int64 Log(int64 x) {
				return static_cast<int64>(log(static_cast<float64>(x)));
			}
			inline float32 Log(float32 x) {
				return logf(x);
			}
			inline float64 Log(float64 x) {
				return log(x);
			}

			inline int16 Log10(int16 x) {
				return static_cast<int16>(log10f(static_cast<float32>(x)));
			}
			inline int32 Log10(int32 x) {
				return static_cast<int32>(log10f(static_cast<float32>(x)));
			}
			inline int64 Log10(int64 x) {
				return static_cast<int64>(log10(static_cast<float64>(x)));
			}
			inline float32 Log10(float32 x) {
				return log10f(x);
			}
			inline float64 Log10(float64 x) {
				return log10(x);
			}

			inline int16 Cos(int16 x) {
				return static_cast<int16>(cosf(static_cast<float32>(x)));
			}
			inline int32 Cos(int32 x) {
				return static_cast<int32>(cosf(static_cast<float32>(x)));
			}
			inline int64 Cos(int64 x) {
				return static_cast<int64>(cos(static_cast<float64>(x)));
			}
			inline float32 Cos(float32 x) {
				return cosf(x);
			}
			inline float64 Cos(float64 x) {
				return cos(x);
			}

			inline int16 Sin(int16 x) {
				return static_cast<int16>(sinf(static_cast<float32>(x)));
			}
			inline int32 Sin(int32 x) {
				return static_cast<int32>(sinf(static_cast<float32>(x)));
			}
			inline int64 Sin(int64 x) {
				return static_cast<int64>(sin(static_cast<float64>(x)));
			}
			inline float32 Sin(float32 x) {
				return sinf(x);
			}
			inline float64 Sin(float64 x) {
				return sin(x);
			}

			inline int16 Tan(int16 x) {
				return static_cast<int16>(tanf(static_cast<float32>(x)));
			}
			inline int32 Tan(int32 x) {
				return static_cast<int32>(tanf(static_cast<float32>(x)));
			}
			inline int64 Tan(int64 x) {
				return static_cast<int64>(tan(static_cast<float64>(x)));
			}
			inline float32 Tan(float32 x) {
				return tanf(x);
			}
			inline float64 Tan(float64 x) {
				return tan(x);
			}

			inline int16 Acos(int16 x) {
				return static_cast<int16>(acosf(static_cast<float32>(x)));
			}
			inline int32 Acos(int32 x) {
				return static_cast<int32>(acosf(static_cast<float32>(x)));
			}
			inline int64 Acos(int64 x) {
				return static_cast<int64>(acos(static_cast<float64>(x)));
			}
			inline float32 Acos(float32 x) {
				return acosf(x);
			}
			inline float64 Acos(float64 x) {
				return acos(x);
			}

			inline int16 Asin(int16 x) {
				return static_cast<int16>(asinf(static_cast<float32>(x)));
			}
			inline int32 Asin(int32 x) {
				return static_cast<int32>(asinf(static_cast<float32>(x)));
			}
			inline int64 Asin(int64 x) {
				return static_cast<int64>(asin(static_cast<float64>(x)));
			}
			inline float32 Asin(float32 x) {
				return asinf(x);
			}
			inline float64 Asin(float64 x) {
				return asin(x);
			}

			inline int16 Atan(int16 x) {
				return static_cast<int16>(atanf(static_cast<float32>(x)));
			}
			inline int32 Atan(int32 x) {
				return static_cast<int32>(atanf(static_cast<float32>(x)));
			}
			inline int64 Atan(int64 x) {
				return static_cast<int64>(atan(static_cast<float64>(x)));
			}
			inline float32 Atan(float32 x) {
				return atanf(x);
			}
			inline float64 Atan(float64 x) {
				return atan(x);
			}

			inline int16 Atan2(int16 y, int16 x) {
				return static_cast<int16>(atan2f(static_cast<float32>(y), static_cast<float32>(x)));
			}
			inline int32 Atan2(int16 y, int32 x) {
				return static_cast<int32>(atan2f(static_cast<float32>(y), static_cast<float32>(x)));
			}
			inline int64 Atan2(int16 y, int64 x) {
				return static_cast<int64>(atan2(static_cast<float64>(y), static_cast<float64>(x)));
			}
			inline float32 Atan2(float32 y, float32 x) {
				return atan2f(y, x);
			}
			inline float64 Atan2(float64 y, float64 x) {
				return atan2(y, x);
			}

			inline int16 Cosh(int16 x) {
				return static_cast<int16>(coshf(static_cast<float32>(x)));
			}
			inline int32 Cosh(int32 x) {
				return static_cast<int32>(coshf(static_cast<float32>(x)));
			}
			inline int64 Cosh(int64 x) {
				return static_cast<int64>(cosh(static_cast<float64>(x)));
			}
			inline float32 Cosh(float32 x) {
				return coshf(x);
			}
			inline float64 Cosh(float64 x) {
				return cosh(x);
			}

			inline int16 Sinh(int16 x) {
				return static_cast<int16>(sinhf(static_cast<float32>(x)));
			}
			inline int32 Sinh(int32 x) {
				return static_cast<int32>(sinhf(static_cast<float32>(x)));
			}
			inline int64 Sinh(int64 x) {
				return static_cast<int64>(sinh(static_cast<float64>(x)));
			}
			inline float32 Sinh(float32 x) {
				return sinhf(x);
			}
			inline float64 Sinh(float64 x) {
				return sinh(x);
			}

			inline int16 Tanh(int16 x) {
				return static_cast<int16>(tanhf(static_cast<float32>(x)));
			}
			inline int32 Tanh(int32 x) {
				return static_cast<int32>(tanhf(static_cast<float32>(x)));
			}
			inline int64 Tanh(int64 x) {
				return static_cast<int64>(tanh(static_cast<float64>(x)));
			}
			inline float32 Tanh(float32 x) {
				return tanhf(x);
			}
			inline float64 Tanh(float64 x) {
				return tanh(x);
			}

			inline float32 Floor(float32 x) {
				return floorf(x);
			}
			inline float64 Floor(float64 x) {
				return floor(x);
			}

			inline float32 Ceil(float32 x) {
				return ceilf(x);
			}
			inline float64 Ceil(float64 x) {
				return ceil(x);
			}

			inline float32 Round(float32 x) {
				return floorf(x + 0.5f);
			}
			inline float64 Round(float64 x) {
				return floor(x + 0.5);
			}

			inline bool Equals(float32 a, float32 b, float32 e = Epsilon) {
				return Abs(a - b) < e;
			}
			inline bool Equals(float64 a, float64 b, float64 e = Epsilon_64) {
				return Abs(a - b) < e;
			}

			inline int16 Modulo(int16 a, int16 b) {
				int16 r = a % b;
				return (r * b < 0) ? r + b : r;
			}
			inline int32 Modulo(int32 a, int32 b) {
				int32 r = a % b;
				return (r * b < 0) ? r + b : r;
			}
			inline int64 Modulo(int64 a, int64 b) {
				int64 r = a % b;
				return (r * b < 0) ? r + b : r;
			}
			inline float32 Modulo(float32 a, float32 b) {
				float32 r = fmod(a, b);
				return (r * b < 0.0f) ? r + b : r;
			}
			inline float64 Modulo(float64 a, float64 b) {
				float64 r = fmod(a, b);
				return (r * b < 0.0) ? r + b : r;
			}

			inline int16 Clamp(int16 x, int16 min, int16 max) {
				return x < min ? min : x > max ? max : x;
			}
			inline int32 Clamp(int32 x, int32 min, int32 max) {
				return x < min ? min : x > max ? max : x;
			}
			inline int64 Clamp(int64 x, int64 min, int64 max) {
				return x < min ? min : x > max ? max : x;
			}
			inline float32 Clamp(float32 x, float32 min, float32 max) {
				return x < min ? min : x > max ? max : x;
			}
			inline float64 Clamp(float64 x, float64 min, float64 max) {
				return x < min ? min : x > max ? max : x;
			}

			inline float32 Clamp01(float32 x) {
				return x < 0.0f ? 0.0f : x > 1.0f ? 1.0f : x;
			}
			inline float64 Clamp01(float64 x) {
				return x < 0.0 ? 0.0 : x > 1.0 ? 1.0 : x;
			}

			inline int16 Radian(int16 x) {
				return Modulo(x, static_cast<int16>(TWO_PI));
			}
			inline int32 Radian(int32 x) {
				return Modulo(x, static_cast<int32>(TWO_PI));
			}
			inline int64 Radian(int64 x) {
				return Modulo(x, static_cast<int64>(TWO_PI));
			}
			inline float32 Radian(float32 x) {
				return Modulo(x, TWO_PI);
			}
			inline float64 Radian(float64 x) {
				return Modulo(x, TWO_PI_64);
			}

			inline int16 Angle(int16 x) {
				return Modulo(x, static_cast<int16>(360));
			}
			inline int32 Angle(int32 x) {
				return Modulo(x, static_cast<int32>(360));
			}
			inline int64 Angle(int64 x) {
				return Modulo(x, static_cast<int64>(360));
			}
			inline float32 Angle(float32 x) {
				return Modulo(x, 360.0f);
			}
			inline float64 Angle(float64 x) {
				return Modulo(x, 360.0);
			}

			inline int16 Sign(int16 x) {
				return x ? x < static_cast<int16>(0) ? -static_cast<int16>(1) : static_cast<int16>(1) : static_cast<int16>(0);
			}
			inline int32 Sign(int32 x) {
				return x ? x < static_cast<int32>(0) ? -static_cast<int32>(1) : static_cast<int32>(1) : static_cast<int32>(0);
			}
			inline int64 Sign(int64 x) {
				return x ? x < static_cast<int64>(0) ? -static_cast<int64>(1) : static_cast<int64>(1) : static_cast<int64>(0);
			}
			inline float32 Sign(float32 x) {
				return x ? x < 0.0f ? -1.0f : 1.0f : 0.0f;
			}
			inline float32 Sign(float64 x) {
				return x ? x < 0.0 ? -1.0 : 1.0 : 0.0;
			}

			inline int16 Lerp(int16 a, int16 b, float32 t) {
				return a + (b - a) * t;
			}
			inline int32 Lerp(int32 a, int32 b, float32 t) {
				return a + (b - a) * t;
			}
			inline int64 Lerp(int64 a, int64 b, float32 t) {
				return a + (b - a) * t;
			}
			inline float32 Lerp(float32 a, float32 b, float32 t) {
				return a + (b - a) * t;
			}
			inline float64 Lerp(float64 a, float64 b, float32 t) {
				return a + (b - a) * t;
			}
			inline float64 Lerp(float64 a, float64 b, float64 t) {
				return a + (b - a) * t;
			}

			inline float32 LerpCos(float32 a, float32 b, float32 t) {
				float32 ft = t * PI,
				        f = (1.0f - Cos(ft)) * 0.5f;

				return a * (1.0f - f) + b * f;
			}
			inline float64 LerpCos(float64 a, float64 b, float64 t) {
				float64 ft = t * PI,
				        f = (1.0 - Cos(ft)) * 0.5;

				return a * (1.0 - f) + b * f;
			}

			inline float32 LerpCubic(float32 v0, float32 v1, float32 v2, float32 v3, float32 t) {
				float32 P = (v3 - v2) - (v0 - v1),
				        Q = (v0 - v1) - P,
				        R = v2 - v0,
				        S = v1,
				        Pt = P * t, Qt = Q * t, Rt = R * t;

				return (Pt * Pt * Pt) + (Qt * Qt) + Rt + S;
			}
			inline float64 LerpCubic(float64 v0, float64 v1, float64 v2, float64 v3, float64 t) {
				float64 P = (v3 - v2) - (v0 - v1),
				        Q = (v0 - v1) - P,
				        R = v2 - v0,
				        S = v1,
				        Pt = P * t, Qt = Q * t, Rt = R * t;

				return (Pt * Pt * Pt) + (Qt * Qt) + Rt + S;
			}

			inline int16 LerpRadian(int16 a, int16 b, float32 t) {
				return Radian(a + (b - a) * t);
			}
			inline int32 LerpRadian(int32 a, int32 b, float32 t) {
				return Radian(a + (b - a) * t);
			}
			inline int64 LerpRadian(int64 a, int64 b, float32 t) {
				return Radian(a + (b - a) * t);
			}
			inline float32 LerpRadian(float32 a, float32 b, float32 t) {
				return Radian(a + (b - a) * t);
			}
			inline float64 LerpRadian(float64 a, float64 b, float64 t) {
				return Radian(a + (b - a) * t);
			}

			inline int16 LerpAngle(int16 a, int16 b, float32 t) {
				return Angle(a + (b - a) * t);
			}
			inline int32 LerpAngle(int32 a, int32 b, float32 t) {
				return Angle(a + (b - a) * t);
			}
			inline int64 LerpAngle(int64 a, int64 b, float32 t) {
				return Angle(a + (b - a) * t);
			}
			inline float32 LerpAngle(float32 a, float32 b, float32 t) {
				return Angle(a + (b - a) * t);
			}
			inline float64 LerpAngle(float64 a, float64 b, float64 t) {
				return Angle(a + (b - a) * t);
			}

			inline float32 SmoothStep(float32 x, float32 min, float32 max) {
				if (x <= min) {
					return 0.0f;
				}

				if (x >= max) {
					return 1.0f;
				}

				x = (x - min) / (max - min);

				return x * x * (3.0f - 2.0f * x);
			}
			inline float64 SmoothStep(float64 x, float64 min, float64 max) {
				if (x <= min) {
					return 0.0;
				}

				if (x >= max) {
					return 1.0;
				}

				x = (x - min) / (max - min);

				return x * x * (3.0 - 2.0 * x);
			}

			inline float32 SmootherStep(float32 x, float32 min, float32 max) {
				if (x <= min) {
					return 0.0f;
				}

				if (x >= max) {
					return 1.0f;
				}

				x = (x - min) / (max - min);

				return x * x * x * (x * (x * 6.0f - 15.0f) + 10.0f);
			}
			inline float64 SmootherStep(float64 x, float64 min, float64 max) {
				if (x <= min) {
					return 0.0;
				}

				if (x >= max) {
					return 1.0;
				}

				x = (x - min) / (max - min);

				return x * x * x * (x * (x * 6.0 - 15.0) + 10.0);
			}

			inline int16 PingPong(int16 x, int16 length) {
				return length - Abs(Modulo(x, static_cast<int16>(2 * length)) - length);
			}
			inline int32 PingPong(int32 x, int32 length) {
				return length - Abs(Modulo(x, static_cast<int32>(2 * length)) - length);
			}
			inline int64 PingPong(int64 x, int64 length) {
				return length - Abs(Modulo(x, static_cast<int64>(2 * length)) - length);
			}
			inline float32 PingPong(float32 x, float32 length) {
				return length - Abs(Modulo(x, 2.0f * length) - length);
			}
			inline float64 PingPong(float64 x, float64 length) {
				return length - Abs(Modulo(x, 2.0 * length) - length);
			}

			inline int16 ToRads(int16 x) {
				return Radian(x * static_cast<int16>(TO_RADS));
			}
			inline int32 ToRads(int32 x) {
				return Radian(x * static_cast<int32>(TO_RADS));
			}
			inline int64 ToRads(int64 x) {
				return Radian(x * static_cast<int64>(TO_RADS));
			}
			inline float32 ToRads(float32 x) {
				return Radian(x * TO_RADS);
			}
			inline float64 ToRads(float64 x) {
				return Radian(x * TO_RADS_64);
			}

			inline int16 ToDegs(int16 x) {
				return Angle(x * static_cast<int16>(TO_DEGS));
			}
			inline int32 ToDegs(int32 x) {
				return Angle(x * static_cast<int32>(TO_DEGS));
			}
			inline int64 ToDegs(int64 x) {
				return Angle(x * static_cast<int64>(TO_DEGS));
			}
			inline float32 ToDegs(float32 x) {
				return Angle(x * TO_DEGS);
			}
			inline float64 ToDegs(float64 x) {
				return Angle(x * TO_DEGS_64);
			}

			inline bool IsPowerOfTwo(int16 x) {
				return (x & (x - static_cast<int16>(1))) == static_cast<int16>(0) && x > static_cast<int16>(0);
			}
			inline bool IsPowerOfTwo(int32 x) {
				return (x & (x - static_cast<int32>(1))) == static_cast<int32>(0) && x > static_cast<int32>(0);
			}
			inline bool IsPowerOfTwo(int64 x) {
				return (x & (x - static_cast<int64>(1))) == static_cast<int64>(0) && x > static_cast<int64>(0);
			}
			inline bool IsPowerOfTwo(float32 a) {
				int32 x = static_cast<int32>(a);
				return (x & (x - 1)) == 0 && x > 0;
			}
			inline bool IsPowerOfTwo(float64 a) {
				int64 x = static_cast<int64>(a);
				return (x & (x - 1)) == 0 && x > 0;
			}
			
			inline int16 PowerOfTwo(int16 n) {
				int16 x = n, tmp;

				x--;
				x |= x >> static_cast<int16>(1);
				x |= x >> static_cast<int16>(2);
				x |= x >> static_cast<int16>(4);
				x |= x >> static_cast<int16>(8);
				x |= x >> static_cast<int16>(16);
				x++;
				tmp = x >> static_cast<int16>(1);

				if (Abs(tmp - n) < Abs(x - n)) {
					return tmp;
				}

				return x;
			}
			inline int32 PowerOfTwo(int32 n) {
				int32 x = n, tmp;

				x--;
				x |= x >> static_cast<int32>(1);
				x |= x >> static_cast<int32>(2);
				x |= x >> static_cast<int32>(4);
				x |= x >> static_cast<int32>(8);
				x |= x >> static_cast<int32>(16);
				x++;
				tmp = x >> static_cast<int32>(1);

				if (Abs(tmp - n) < Abs(x - n)) {
					return tmp;
				}

				return x;
			}
			inline int64 PowerOfTwo(int64 n) {
				int64 x = n, tmp;

				x--;
				x |= x >> static_cast<int64>(1);
				x |= x >> static_cast<int64>(2);
				x |= x >> static_cast<int64>(4);
				x |= x >> static_cast<int64>(8);
				x |= x >> static_cast<int64>(16);
				x++;
				tmp = x >> static_cast<int64>(1);

				if (Abs(tmp - n) < Abs(x - n)) {
					return tmp;
				}

				return x;
			}
			inline float32 PowerOfTwo(float32 a) {
				int32 n = static_cast<int32>(a),
					  x = n, tmp;

				x--;
				x |= x >> static_cast<int32>(1);
				x |= x >> static_cast<int32>(2);
				x |= x >> static_cast<int32>(4);
				x |= x >> static_cast<int32>(8);
				x |= x >> static_cast<int32>(16);
				x++;
				tmp = x >> static_cast<int32>(1);

				if (Abs(tmp - n) < Abs(x - n)) {
					return tmp;
				}

				return static_cast<float32>(x);
			}
			inline float64 PowerOfTwo(float64 a) {
				int64 n = static_cast<int64>(a),
					  x = n, tmp;

				x--;
				x |= x >> static_cast<int64>(1);
				x |= x >> static_cast<int64>(2);
				x |= x >> static_cast<int64>(4);
				x |= x >> static_cast<int64>(8);
				x |= x >> static_cast<int64>(16);
				x++;
				tmp = x >> static_cast<int64>(1);

				if (Abs(tmp - n) < Abs(x - n)) {
					return tmp;
				}

				return static_cast<float64>(x);
			}

			inline int16 FloorPowerOfTwo(int16 x) {
				x--;
				x |= x >> static_cast<int16>(1);
				x |= x >> static_cast<int16>(2);
				x |= x >> static_cast<int16>(4);
				x |= x >> static_cast<int16>(8);
				x |= x >> static_cast<int16>(16);
				x++;
				return x >> static_cast<int16>(1);
			}
			inline int32 FloorPowerOfTwo(int32 x) {
				x--;
				x |= x >> static_cast<int32>(1);
				x |= x >> static_cast<int32>(2);
				x |= x >> static_cast<int32>(4);
				x |= x >> static_cast<int32>(8);
				x |= x >> static_cast<int32>(16);
				x++;
				return x >> static_cast<int32>(1);
			}
			inline int64 FloorPowerOfTwo(int64 x) {
				x--;
				x |= x >> static_cast<int64>(1);
				x |= x >> static_cast<int64>(2);
				x |= x >> static_cast<int64>(4);
				x |= x >> static_cast<int64>(8);
				x |= x >> static_cast<int64>(16);
				x++;
				return x >> static_cast<int64>(1);
			}
			inline float32 FloorPowerOfTwo(float32 a) {
				int32 x = static_cast<int32>(a);
				x--;
				x |= x >> static_cast<int32>(1);
				x |= x >> static_cast<int32>(2);
				x |= x >> static_cast<int32>(4);
				x |= x >> static_cast<int32>(8);
				x |= x >> static_cast<int32>(16);
				x++;
				return static_cast<float32>(x >> static_cast<int32>(1));
			}
			inline float64 FloorPowerOfTwo(float64 a) {
				int64 x = static_cast<int64>(a);
				x--;
				x |= x >> static_cast<int64>(1);
				x |= x >> static_cast<int64>(2);
				x |= x >> static_cast<int64>(4);
				x |= x >> static_cast<int64>(8);
				x |= x >> static_cast<int64>(16);
				x++;
				return static_cast<float64>(x >> static_cast<int64>(1));
			}

			inline int16 CeilPowerOfTwo(int16 x) {
				x--;
				x |= x >> static_cast<int16>(1);
				x |= x >> static_cast<int16>(2);
				x |= x >> static_cast<int16>(4);
				x |= x >> static_cast<int16>(8);
				x |= x >> static_cast<int16>(16);
				x++;
				return x;
			}
			inline int32 CeilPowerOfTwo(int32 x) {
				x--;
				x |= x >> static_cast<int32>(1);
				x |= x >> static_cast<int32>(2);
				x |= x >> static_cast<int32>(4);
				x |= x >> static_cast<int32>(8);
				x |= x >> static_cast<int32>(16);
				x++;
				return x;
			}
			inline int64 CeilPowerOfTwo(int64 x) {
				x--;
				x |= x >> static_cast<int64>(1);
				x |= x >> static_cast<int64>(2);
				x |= x >> static_cast<int64>(4);
				x |= x >> static_cast<int64>(8);
				x |= x >> static_cast<int64>(16);
				x++;
				return x;
			}
			inline float32 CeilPowerOfTwo(float32 a) {
				int32 x = static_cast<int32>(a);
				x--;
				x |= x >> static_cast<int32>(1);
				x |= x >> static_cast<int32>(2);
				x |= x >> static_cast<int32>(4);
				x |= x >> static_cast<int32>(8);
				x |= x >> static_cast<int32>(16);
				x++;
				return static_cast<float32>(x);
			}
			inline float64 CeilPowerOfTwo(float64 a) {
				int64 x = static_cast<int64>(a);
				x--;
				x |= x >> static_cast<int64>(1);
				x |= x >> static_cast<int64>(2);
				x |= x >> static_cast<int64>(4);
				x |= x >> static_cast<int64>(8);
				x |= x >> static_cast<int64>(16);
				x++;
				return static_cast<float64>(x);
			}

			inline float32 Random(void) {
				return (float64) std::rand() / RAND_MAX;
			}
			inline float64 Random64(void) {
				return (float64) std::rand() / RAND_MAX;
			}

			inline int16 RandInt(int16 min, int16 max) {
				return Round(min + (Random() * (max - min)));
			}
			inline int32 RandInt(int32 min, int32 max) {
				return Round(min + (Random() * (max - min)));
			}
			inline int64 RandInt(int64 min, int64 max) {
				return Round(min + (Random() * (max - min)));
			}

			inline float32 RandFloat(float32 min, float32 max) {
				return min + (Random() * (max - min));
			}
			inline float64 RandFloat(float64 min, float64 max) {
				return min + (Random64() * (max - min));
			}
	} Mathf;

	template<typename Type> inline Type Vec2LengthSq(Type x, Type y) {

		return x * x + y * y;
	}

	template<typename Type> inline Type Vec2Length(Type x, Type y) {
		Type length = x * x + y * y;

		return length == static_cast<Type>(0) ? static_cast<Type>(0) : Mathf.Sqrt(length);
	}

	template<typename Type> inline Type Vec3LengthSq(Type x, Type y, Type z) {

		return x * x + y * y + z * z;
	}

	template<typename Type> inline Type Vec3Length(Type x, Type y, Type z) {
		Type length = x * x + y * y + z * z;

		return length == static_cast<Type>(0) ? static_cast<Type>(0) : Mathf.Sqrt(length);
	}

	template<typename Type> inline Type Vec4LengthSq(Type x, Type y, Type z, Type w) {

		return x * x + y * y + z * z + w * w;
	}

	template<typename Type> inline Type Vec4Length(Type x, Type y, Type z, Type w) {
		Type length = x * x + y * y + z * z + w * w;

		return length == static_cast<Type>(0) ? static_cast<Type>(0) : Mathf.Sqrt(length);
	}
}


#include "color.h"
#include "mat2.h"
#include "mat3.h"
#include "mat32.h"
#include "mat4.h"
#include "mat43.h"
#include "quat.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "aabb2.h"
#include "aabb3.h"

#include "color.cpp"
#include "mat2.cpp"
#include "mat3.cpp"
#include "mat32.cpp"
#include "mat4.cpp"
#include "mat43.cpp"
#include "quat.cpp"
#include "vec2.cpp"
#include "vec3.cpp"
#include "vec4.cpp"
#include "aabb2.cpp"
#include "aabb3.cpp"


#endif