#ifndef _ODIN_VEC2_H
#define _ODIN_VEC2_H

namespace Odin {

	class Vec2 {

		public:

			float32 x;
			float32 y;

			inline explicit Vec2(void);
			inline explicit Vec2(float32 X);
			inline explicit Vec2(float32 X, float32 Y);
			inline Vec2(const Vec2& v);
			inline Vec2(const Vec2&& v);
			inline Vec2(const Vec3& v);
			inline Vec2(const Vec4& v);
			inline Vec2(const Color& v);
			inline ~Vec2(void);

			inline Vec2& Set(float32 X, float32 Y);
			inline Vec2& Zero(void);

			inline float32 Dot(const Vec2& v);
			inline float32 Cross(const Vec2& v);
			inline float32 LengthSq(void);
			inline float32 Length(void);
			inline float32 Normalize(void);

			inline Vec2& Lerp(const Vec2& v, float32 t);

			inline Vec2& Min(const Vec2& v);
			inline Vec2& Max(const Vec2& v);

			inline static Vec2 Min(const Vec2& a, const Vec2& b) {
				float32 ax = a.x,
				        ay = a.y,
				        bx = b.x,
				        by = b.y;

				return Vec2(
				           bx < ax ? bx : ax,
				           by < ay ? by : ay
				       );
			}

			inline static Vec2 Max(const Vec2& a, const Vec2& b) {
				float32 ax = a.x,
				        ay = a.y,
				        bx = b.x,
				        by = b.y;

				return Vec2(
				           bx > ax ? bx : ax,
				           by > ay ? by : ay
				       );
			}

			inline static Vec2 Lerp(const Vec2& a, const Vec2& b, float32 t) {

				return Vec2(
				           Mathf.Lerp(a.x, b.x, t),
				           Mathf.Lerp(a.y, b.y, t)
				       );
			}

			inline static float32 Dot(const Vec2& a, const Vec2& b) {

				return a.x * b.x + a.y * b.y;
			}

			inline static float32 Cross(const Vec2& a, const Vec2& b) {

				return a.x * b.y - a.y * b.x;
			}

			static const Vec2 ZERO;
			static const Vec2 UNIT_X;
			static const Vec2 UNIT_Y;
			static const Vec2 NEGATIVE_UNIT_X;
			static const Vec2 NEGATIVE_UNIT_Y;
			static const Vec2 UNIT_SCALE;

			inline Vec2& operator -();

			inline float32 operator [] (int32 i) const;
			inline float32& operator [] (int32 i);

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

			inline Vec2 operator +(float32 s);
			inline Vec2 operator -(float32 s);
			inline Vec2 operator *(float32 s);
			inline Vec2 operator /(float32 s);

			inline void operator +=(float32 s);
			inline void operator -=(float32 s);
			inline void operator *=(float32 s);
			inline void operator /=(float32 s);

			inline Vec2& operator =(const Vec2& q);
			inline Vec2& operator =(const Vec2 && q);

			inline bool operator ==(const Vec2& v);
			inline bool operator !=(const Vec2& v);

			inline std::string ToString(int32 p = 5);
	};
}
#endif