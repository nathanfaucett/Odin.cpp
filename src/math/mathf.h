#ifndef ODIN_MATHF_H
#define ODIN_MATHF_H

namespace Odin {

	struct AABB2;
	struct AABB3;
	struct Color;
	struct Mat2;
	struct Mat32;
	struct Mat3;
	struct Mat4;
	struct Quat;
	struct Vec2;
	struct Vec3;
	struct Vec4;


	constexpr float Infinity = INFINITY;
	constexpr float POS_Infinity = INFINITY;
	constexpr float NEG_Infinity = -INFINITY;

	constexpr float MAX_NUMBER = FLT_MAX;
	constexpr float MIN_NUMBER = FLT_MIN;


	inline float Vec2LengthSq(const float x, const float y) {

		return x * x + y * y;
	}

	inline float Vec2Length(const float x, const float y) {
		float length = x * x + y * y;

		return length == 0.0f ? 0.0f : sqrtf(length);
	}

	inline float Vec3LengthSq(const float x, const float y, const float z) {

		return x * x + y * y + z * z;
	}

	inline float Vec3Length(const float x, const float y, const float z) {
		float length = x * x + y * y + z * z;

		return length == 0.0f ? 0.0f : sqrtf(length);
	}

	inline float Vec4LengthSq(const float x, const float y, const float z, const float w) {

		return x * x + y * y + z * z + w * w;
	}

	inline float Vec4Length(const float x, const float y, const float z, const float w) {
		float length = x * x + y * y + z * z + w * w;

		return length == 0.0f ? 0.0f : sqrtf(length);
	}

	struct Mathf {
		static constexpr float PI = M_PI;
		static constexpr float FOURTH_PI = M_PI * 0.25f;
		static constexpr float HALF_PI = M_PI * 0.5f;
		static constexpr float TWO_PI = M_PI * 2.0f;

		static constexpr float Epsilon = FLT_EPSILON;

		static constexpr float E = 2.71828182845904523536f;
		static constexpr float SQRT_TWO = 1.41421356237309504880f;
		static constexpr float SQRT_THREE = 1.73205080756887729352f;

		static constexpr float TO_DEGS = 180.0f / M_PI;
		static constexpr float TO_RADS = M_PI / 180.0f;

		inline float Abs(const float x) {

			return x < 0.0f ? -x : x;
		}

		inline float Pow(const float x, const float e) {

			return powf(x, e);
		}

		inline float Sqrt(const float x) {

			return x > 0.0f ? sqrtf(x) : 0.0f;
		}

		inline float Log(const float x) {

			return logf(x);
		}
		inline float Log10(const float x) {

			return log10f(x);
		}

		inline float Cos(const float x) {

			return cosf(x);
		}
		inline float Sin(const float x) {

			return sinf(x);
		}
		inline float Tan(const float x) {

			return tanf(x);
		}

		inline float Acos(const float x) {

			return acosf(x);
		}
		inline float Asin(const float x) {

			return asinf(x);
		}
		inline float Atan(const float x) {

			return atanf(x);
		}

		inline float Atan2(const float y, const float x) {

			return atan2f(y, x);
		}

		inline float Cosh(const float x) {

			return coshf(x);
		}
		inline float Sinh(const float x) {

			return sinhf(x);
		}
		inline float Tanh(const float x) {

			return tanhf(x);
		}

		inline float Floor(const float x) {

			return floorf(x);
		}
		inline float Ceil(const float x) {

			return ceilf(x);
		}
		inline float Round(const float x) {

			return floorf(x + 0.5f);
		}

		inline bool Equals(const float a, const float b) {

			return Abs(a - b) < FLT_EPSILON;
		}

		inline float Modulo(const float a, const float b) {
			float r = fmod(a, b);

			return (r * b < FLT_EPSILON) ? r + b : r;
		}

		inline float Clamp(const float x, const float min, const float max) {

			return x < min ? min : x > max ? max : x;
		}

		inline float ClampBottom(const float x, const float min) {

			return x < min ? min : x;
		}

		inline float ClampTop(const float x, const float max) {

			return x > max ? max : x;
		}

		inline float Clamp01(const float x) {

			return x < 0.0f ? 0.0f : x > 1 ? 1 : x;

		}

		inline float Radian(const float x) {

			return Modulo(x, TWO_PI);
		}

		inline float Angle(const float x) {

			return Modulo(x, 360.0f);
		}

		inline float Sign(const float x) {

			return x ? x < 0.0f ? -1 : 1 : 0.0f;
		}

		inline int Sign(const int x) {

			return x ? x < 0 ? -1 : 1 : 0;
		}

		inline float Lerp(const float a, const float b, const float t) {

			return a + (b - a) * t;
		}

		inline float LerpCos(const float a, const float b, const float t) {
			float ft = t * PI,
			      f = (1 - cosf(ft)) * 0.5f;

			return a * (1 - f) + b * f;
		}

		inline float LerpCubic(const float v0, const float v1, const float v2, const float v3, const float t) {
			float P = (v3 - v2) - (v0 - v1),
			      Q = (v0 - v1) - P,
			      R = v2 - v0,
			      S = v1,

			      Pt = P * t,
			      Qt = Q * t,
			      Rt = R * t;

			return (Pt * Pt * Pt) + (Qt * Qt) + Rt + S;
		}

		inline float LerpRadian(const float a, const float b, const float t) {

			return Radian(a + (b - a) * t);
		}

		inline float LerpAngle(const float a, const float b, const float t) {

			return Angle(a + (b - a) * t);

		}

		inline float SmoothStep(const float x, const float min, const float max) {
			float t = x;

			if (t <= min) {
				return 0.0f;
			}

			if (t >= max) {
				return 1.0f;
			}

			t = (t - min) / (max - min);

			return t * t * (3.0f - 2.0f * t);
		}

		inline float SmootherStep(const float x, const float min, const float max) {
			float t = x;

			if (t <= min) {
				return 0.0f;
			}

			if (t >= max) {
				return 1.0f;
			}

			t = (t - min) / (max - min);

			return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
		}

		inline float PingPong(const float x, const float length) {

			return length - Abs(Modulo(x, 2 * length) - length);
		}

		inline float ToRads(const float x) {

			return Radian(x * TO_RADS);
		}

		inline float ToDegs(const float x) {

			return Angle(x * TO_DEGS);

		}

		inline bool IsPowerOfTwo(const float n) {
			int x = n;

			return (x & -x) == x;
		}

		inline float ToPowerOfTwo(const float n) {
			int x = Abs(n);

			--x;
			x |= x >> 1;
			x |= x >> 2;
			x |= x >> 4;
			x |= x >> 8;
			x |= x >> 16;

			return x + 1;
		}

		inline float Random(void) {

			return (double) std::rand() / RAND_MAX;
		}

		inline int RandInt(int const min, const int max) {

			return Round(min + (Random() * (max - min)));
		}

		inline float RandFloat(const float min, const float max) {

			return min + (Random() * (max - min));
		}
	};

	Mathf Mathf;
}

#endif