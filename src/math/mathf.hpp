#ifndef _ODIN_MATHF_HPP
#define _ODIN_MATHF_HPP

namespace Odin {

	class AABB2;
	class AABB3;
	class Color;
	class Mat2;
	class Mat32;
	class Mat3;
	class Mat4;
	class Quat;
	class Vec2;
	class Vec3;
	class Vec4;

	constexpr float32 Infinity = INFINITY;
	constexpr float32 POS_Infinity = INFINITY;
	constexpr float32 NEG_Infinity = -INFINITY;

	constexpr float32 MAX_NUMBER = FLT_MAX;
	constexpr float32 MIN_NUMBER = FLT_MIN;


	inline float32 Vec2LengthSq(float32 x, float32 y) {

		return x * x + y * y;
	}

	inline float32 Vec2Length(float32 x, float32 y) {
		float32 length = x * x + y * y;

		return length == 0.0f ? 0.0f : sqrtf(length);
	}

	inline float32 Vec3LengthSq(float32 x, float32 y, float32 z) {

		return x * x + y * y + z * z;
	}

	inline float32 Vec3Length(float32 x, float32 y, float32 z) {
		float32 length = x * x + y * y + z * z;

		return length == 0.0f ? 0.0f : sqrtf(length);
	}

	inline float32 Vec4LengthSq(float32 x, float32 y, float32 z, float32 w) {

		return x * x + y * y + z * z + w * w;
	}

	inline float32 Vec4Length(float32 x, float32 y, float32 z, float32 w) {
		float32 length = x * x + y * y + z * z + w * w;

		return length == 0.0f ? 0.0f : sqrtf(length);
	}

	inline float32 inv_sqrtf(float32 x) {

		return x == 0.0f ? 0.0f : 1.0f / sqrtf(x);
	}

	class Mathf {

		public:
			static constexpr float32 PI = M_PI;
			static constexpr float32 FOURTH_PI = M_PI * 0.25f;
			static constexpr float32 HALF_PI = M_PI * 0.5f;
			static constexpr float32 TWO_PI = M_PI * 2.0f;

			static constexpr float32 Epsilon = FLT_EPSILON;

			static constexpr float32 E = 2.71828182845904523536f;
			static constexpr float32 SQRT_TWO = 1.41421356237309504880f;
			static constexpr float32 SQRT_THREE = 1.73205080756887729352f;

			static constexpr float32 TO_DEGS = 180.0f / M_PI;
			static constexpr float32 TO_RADS = M_PI / 180.0f;

			inline void Init() {
				std::srand(std::time(0));
			}

			inline float32 Abs(float32 x) {

				return x < 0.0f ? -x : x;
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

			inline float32 Sqrt(float32 x) {

				return x == 0.0f ? 0.0f : sqrtf(x);
			}

			inline float32 InvSqrt(float32 x) {

				return x == 0.0f ? 0.0f : 1.0 / sqrtf(x);
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
			inline float32 Sin(float32 x) {

				return sinf(x);
			}
			inline float32 Tan(float32 x) {

				return tanf(x);
			}

			inline float32 Acos(float32 x) {

				return acosf(x);
			}
			inline float32 Asin(float32 x) {

				return asinf(x);
			}
			inline float32 Atan(float32 x) {

				return atanf(x);
			}

			inline float32 Atan2(float32 y, float32 x) {

				return atan2f(y, x);
			}

			inline float32 Cosh(float32 x) {

				return coshf(x);
			}
			inline float32 Sinh(float32 x) {

				return sinhf(x);
			}
			inline float32 Tanh(float32 x) {

				return tanhf(x);
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

			inline int32 Clamp(int32 x, int32 min, int32 max) {

				return x < min ? min : x > max ? max : x;
			}

			inline float32 Clamp(float32 x, float32 min, float32 max) {

				return x < min ? min : x > max ? max : x;
			}

			inline float32 Clamp01(float32 x) {

				return x < 0.0f ? 0.0f : x > 1 ? 1 : x;

			}

			inline float32 Radian(float32 x) {

				return Modulo(x, TWO_PI);
			}

			inline float32 Angle(float32 x) {

				return Modulo(x, 360.0f);
			}

			inline float32 Sign(float32 x) {

				return x ? x < 0.0f ? -1 : 1 : 0.0f;
			}

			inline int32 Sign(int32 x) {

				return x ? x < 0 ? -1 : 1 : 0;
			}

			inline float32 Lerp(float32 a, float32 b, float32 t) {

				return a + (b - a) * t;
			}

			inline float32 LerpCos(float32 a, float32 b, float32 t) {
				float32 ft = t * PI,
				        f = (1 - cosf(ft)) * 0.5f;

				return a * (1 - f) + b * f;
			}

			inline float32 LerpCubic(float32 v0, float32 v1, float32 v2, float32 v3, float32 t) {
				float32 P = (v3 - v2) - (v0 - v1),
				        Q = (v0 - v1) - P,
				        R = v2 - v0,
				        S = v1,

				        Pt = P * t,
				        Qt = Q * t,
				        Rt = R * t;

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
					return 1.0f;
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

			inline int32 RandInt(int32 min, int32 max) {

				return Round(min + (Random() * (max - min)));
			}

			inline float32 RandFloat(float32 min, float32 max) {

				return min + (Random() * (max - min));
			}
	};

	Mathf Mathf;
}

#endif