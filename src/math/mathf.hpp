#ifndef _ODIN_MATHF_HPP_
#define _ODIN_MATHF_HPP_


namespace Odin {

	template <typename Type> class AABB2;
	template <typename Type> class AABB3;
	template <typename Type> class Color;
	template <typename Type> class Mat2;
	template <typename Type> class Mat32;
	template <typename Type> class Mat3;
	template <typename Type> class Mat4;
	template <typename Type> class Quat;
	template <typename Type> class Vec2;
	template <typename Type> class Vec3;
	template <typename Type> class Vec4;

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

	constexpr float32 Infinity = INFINITY;
	constexpr float32 POS_Infinity = INFINITY;
	constexpr float32 NEG_Infinity = -INFINITY;

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


	template<typename Type> inline Type Vec2LengthSq(Type x, Type y) {

		return x * x + y * y;
	}

	template<typename Type> inline Type Vec2Length(Type x, Type y) {
		Type length = x * x + y * y;

		return length == 0 ? 0 : sqrtf(length);
	}

	template<typename Type> inline Type Vec3LengthSq(Type x, Type y, Type z) {

		return x * x + y * y + z * z;
	}

	template<typename Type> inline Type Vec3Length(Type x, Type y, Type z) {
		Type length = x * x + y * y + z * z;

		return length == 0 ? 0 : sqrtf(length);
	}

	template<typename Type> inline Type Vec4LengthSq(Type x, Type y, Type z, Type w) {

		return x * x + y * y + z * z + w * w;
	}

	template<typename Type> inline Type Vec4Length(Type x, Type y, Type z, Type w) {
		Type length = x * x + y * y + z * z + w * w;

		return length == 0 ? 0 : sqrtf(length);
	}

	inline float32 inv_sqrtf(float32 x) {

		return x == 0 ? 0 : 1 / sqrtf(x);
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

			static constexpr float32 E = 2.71828182845904523536f;
			static constexpr float32 SQRT2 = 1.41421356237309504880f;
			static constexpr float32 SQRT1_2 = 0.70710676908493041992f;
			static constexpr float32 SQRT3 = 1.73205080756887729352f;

			static constexpr float32 TO_DEGS = 180.0f / PI;
			static constexpr float32 TO_RADS = PI / 180.0f;

			inline void Init() {
				std::srand(std::time(0));
			}

			inline int16 Abs(int16 x) {
				return x < 0 ? -x : x;
			}
			inline int32 Abs(int32 x) {
				return x < 0 ? -x : x;
			}
			inline int64 Abs(int64 x) {
				return x < 0 ? -x : x;
			}
			inline float32 Abs(float32 x) {
				return x < 0.0f ? -x : x;
			}
			inline float64 Abs(float64 x) {
				return x < 0.0 ? -x : x;
			}

			inline int32 Pow(int32 x, int32 y) {
				int32 r;

				for (r = x; y > 1; y--) {
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

			inline float32 Sqrt(float32 x) {
				return x == 0.0f ? 0.0f : sqrtf(x);
			}
			inline float64 Sqrt(float64 x) {
				return x == 0.0 ? 0.0 : sqrt(x);
			}

			inline float32 InvSqrt(float32 x) {
				return x == 0.0f ? 0.0f : 1.0f / sqrtf(x);
			}
			inline float64 InvSqrt(float64 x) {
				return x == 0.0 ? 0.0 : 1.0 / sqrt(x);
			}

			inline float32 Log(float32 x) {

				return logf(x);
			}
			inline float32 Log10(float32 x) {

				return log10f(x);
			}

			inline float32 Cos(float32 x) {
				return cosf(x);
			}
			inline float64 Cos(float64 x) {
				return cos(x);
			}

			inline float32 Sin(float32 x) {
				return sinf(x);
			}
			inline float64 Sin(float64 x) {
				return sin(x);
			}

			inline float32 Tan(float32 x) {
				return tanf(x);
			}
			inline float64 Tan(float64 x) {
				return tan(x);
			}

			inline float32 Acos(float32 x) {
				return acosf(x);
			}
			inline float64 Acos(float64 x) {
				return acos(x);
			}

			inline float32 Asin(float32 x) {
				return asinf(x);
			}
			inline float64 Asin(float64 x) {
				return asin(x);
			}

			inline float32 Atan(float32 x) {
				return atanf(x);
			}
			inline float64 Atan(float64 x) {
				return atan(x);
			}

			inline float32 Atan2(float32 y, float32 x) {
				return atan2f(y, x);
			}
			inline float64 Atan2(float64 y, float64 x) {
				return atan2(y, x);
			}

			inline float32 Cosh(float32 x) {
				return coshf(x);
			}
			inline float64 Cosh(float64 x) {
				return cosh(x);
			}

			inline float32 Sinh(float32 x) {
				return sinhf(x);
			}
			inline float64 Sinh(float64 x) {
				return sinh(x);
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
			inline float32 Ceil(float32 x) {

				return ceilf(x);
			}
			inline float32 Round(float32 x) {

				return floorf(x + 0.5f);
			}

			inline bool Equals(float32 a, float32 b, float32 e = Epsilon) {

				return Abs(a - b) < e;
			}

			inline float32 Modulo(float32 a, float32 b) {
				float32 r = fmod(a, b);

				return (r * b < 0.0f) ? r + b : r;
			}
			inline float64 Modulo(float64 a, float64 b) {
				float64 r = fmod(a, b);

				return (r * b < 0.0f) ? r + b : r;
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

			inline float32 Radian(float32 x) {
				return Modulo(x, TWO_PI);
			}
			inline float64 Radian(float64 x) {
				return Modulo(x, TWO_PI_64);
			}

			inline float32 Angle(float32 x) {
				return Modulo(x, 360.0f);
			}
			inline float64 Angle(float64 x) {
				return Modulo(x, 360.0);
			}

			inline int16 Sign(int16 x) {
				return x ? x < 0 ? -1 : 1 : 0;
			}
			inline int32 Sign(int32 x) {
				return x ? x < 0 ? -1 : 1 : 0;
			}
			inline int64 Sign(int64 x) {
				return x ? x < 0 ? -1 : 1 : 0;
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
			inline float64 Lerp(float64 a, float64 b, float64 t) {
				return a + (b - a) * t;
			}

			inline float32 LerpCos(float32 a, float32 b, float32 t) {
				float32 ft = t * PI,
				        f = (1 - Cos(ft)) * 0.5f;

				return a * (1 - f) + b * f;
			}
			inline float64 LerpCos(float64 a, float64 b, float64 t) {
				float64 ft = t * PI,
				        f = (1 - Cos(ft)) * 0.5f;

				return a * (1 - f) + b * f;
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

			inline float32 LerpRadian(float32 a, float32 b, float32 t) {

				return Radian(a + (b - a) * t);
			}

			inline float32 LerpAngle(float32 a, float32 b, float32 t) {

				return Angle(a + (b - a) * t);

			}

			inline float32 SmoothStep(float32 x, float32 min, float32 max) {

				if (x <= min) {
					return 0.0f;
				}

				if (x >= max) {
					return 1;
				}

				x = (x - min) / (max - min);

				return x * x * (3.0f - 2.0f * x);
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

			inline float32 PingPong(float32 x, float32 length) {

				return length - Abs(Modulo(x, 2 * length) - length);
			}

			inline float32 ToRads(float32 x) {

				return Radian(x * TO_RADS);
			}

			inline float32 ToDegs(float32 x) {

				return Angle(x * TO_DEGS);

			}

			inline bool IsPowerOfTwo(int32 x) {

				return (x & (x - 1)) == 0 && x > 0;
			}

			inline int32 PowerOfTwo(int32 n) {
				int32 x = n, tmp;

				x--;
				x |= x >> 1;
				x |= x >> 2;
				x |= x >> 4;
				x |= x >> 8;
				x |= x >> 16;
				x++;
				tmp = x >> 1;

				if (Abs(tmp - n) < Abs(x - n)) {
					return tmp;
				}

				return x;
			}

			inline int32 FloorPowerOfTwo(int32 x) {
				x--;
				x |= x >> 1;
				x |= x >> 2;
				x |= x >> 4;
				x |= x >> 8;
				x |= x >> 16;
				x++;
				return x >> 1;
			}

			inline int32 CeilPowerOfTwo(int32 x) {
				x--;
				x |= x >> 1;
				x |= x >> 2;
				x |= x >> 4;
				x |= x >> 8;
				x |= x >> 16;
				x++;
				return x;
			}

			inline float32 Random(void) {
				return (float64) std::rand() / RAND_MAX;
			}
			inline float64 Random64(void) {
				return std::rand() / RAND_MAX;
			}

			inline int32 RandInt(int32 min, int32 max) {
				return Round(min + (Random() * (max - min)));
			}

			inline float32 RandFloat(float32 min, float32 max) {
				return min + (Random() * (max - min));
			}
			inline float64 RandFloat(float64 min, float64 max) {
				return min + (Random64() * (max - min));
			}
	};

	Mathf Mathf;
}

#endif