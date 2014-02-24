#ifndef ODIN_VEC2_H
#define ODIN_VEC2_H

namespace Odin {

	struct Vec2 {

		float x;
		float y;

		inline explicit Vec2(void);
		inline explicit Vec2(const float X);
		inline explicit Vec2(const float X, const float Y);
		inline Vec2(const Vec2& v);
		inline Vec2(const Vec2&& v);
		inline Vec2(const Vec3& v);
		inline Vec2(const Vec4& v);
		inline Vec2(const Color& v);
		inline ~Vec2(void);

		inline Vec2& Set(const float X, const float Y);
		inline Vec2& Zero(void);

		inline float Dot(const Vec2& v);
		inline float Cross(const Vec2& v);
		inline float LengthSq(void);
		inline float Length(void);
		inline float Normalize(void);

		inline Vec2& Lerp(const Vec2& v, const float t);

		inline Vec2& Min(const Vec2& v);
		inline Vec2& Max(const Vec2& v);

		inline static Vec2 Min(const Vec2& a, const Vec2& b) {
			float ax = a.x,
			      ay = a.y,
			      bx = b.x,
			      by = b.y;

			return Vec2(
			           bx < ax ? bx : ax,
			           by < ay ? by : ay
			       );
		}

		inline static Vec2 Max(const Vec2& a, const Vec2& b) {
			float ax = a.x,
			      ay = a.y,
			      bx = b.x,
			      by = b.y;

			return Vec2(
			           bx > ax ? bx : ax,
			           by > ay ? by : ay
			       );
		}

		inline static Vec2 Lerp(const Vec2& a, const Vec2& b, const float t) {

			return Vec2(
			           Mathf.Lerp(a.x, b.x, t),
			           Mathf.Lerp(a.y, b.y, t)
			       );
		}

		inline static float Dot(const Vec2& a, const Vec2& b) {

			return a.x * b.x + a.y * b.y;
		}

		inline static float Cross(const Vec2& a, const Vec2& b) {

			return a.x * b.y - a.y * b.x;
		}

		inline Vec2& operator -();

		inline float operator [] (int i) const;
		inline float& operator [] (int i);

		inline Vec2 operator *(const Mat2& m);
		inline Vec2& operator *=(const Mat2& m);

		inline Vec2 operator *(const Mat32& m);
		inline Vec2& operator *=(const Mat32& m);

		inline Vec2 operator *(const Mat4& m);
		inline Vec2& operator *=(const Mat4& m);

		inline Vec2 operator +(const Vec2& v);
		inline Vec2 operator -(const Vec2& v);
		inline Vec2 operator *(const Vec2& v);
		inline Vec2 operator /(const Vec2& v);

		inline void operator +=(const Vec2& v);
		inline void operator -=(const Vec2& v);
		inline void operator *=(const Vec2& v);
		inline void operator /=(const Vec2& v);

		inline Vec2 operator +(const float s);
		inline Vec2 operator -(const float s);
		inline Vec2 operator *(const float s);
		inline Vec2 operator /(const float s);

		inline void operator +=(const float s);
		inline void operator -=(const float s);
		inline void operator *=(const float s);
		inline void operator /=(const float s);

		inline Vec2& operator =(const Vec2& q);
		inline Vec2& operator =(const Vec2 && q);

		inline bool operator ==(const Vec2& v);
		inline bool operator !=(const Vec2& v);

		inline std::string ToString(int p = 5);
	};
}
#endif