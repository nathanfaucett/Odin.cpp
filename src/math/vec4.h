#ifndef ODIN_VEC4_H
#define ODIN_VEC4_H

namespace Odin {

	struct Vec4 {

		float x;
		float y;
		float z;
		float w;

		inline explicit Vec4(void);
		inline explicit Vec4(const float X);
		inline explicit Vec4(const float X, const float Y, const float Z);
		inline explicit Vec4(const float X, const float Y, const float Z, const float W);
		inline Vec4(const Vec2& v);
		inline Vec4(const Vec3& v);
		inline Vec4(const Vec4& v);
		inline Vec4(const Vec4&& v);
		inline Vec4(const Color& v);
		inline ~Vec4(void);

		inline Vec4& Set(const float X, const float Y);
		inline Vec4& Set(const float X, const float Y, const float Z);
		inline Vec4& Set(const float X, const float Y, const float Z, const float W);
		inline Vec4& Zero(void);

		inline float Dot(const Vec4 v);
		inline float LengthSq(void);
		inline float Length(void);
		inline float Normalize(void);
		inline Vec4& Lerp(const Vec4& v, const float t);

		inline Vec4& Min(const Vec4& v);
		inline Vec4& Max(const Vec4& v);

		inline static Vec4 Min(const Vec4& a, const Vec4& b) {
			float ax = a.x,
			      ay = a.y,
			      az = a.z,
			      aw = a.w,
			      bx = b.x,
			      by = b.y,
			      bz = b.z,
			      bw = b.w;

			return Vec4(
			           bx < ax ? bx : ax,
			           by < ay ? by : ay,
			           bz < az ? bz : az,
			           bw < aw ? bw : aw
			       );
		}

		inline static Vec4 Max(const Vec4& a, const Vec4& b) {
			float ax = a.x,
			      ay = a.y,
			      az = a.z,
			      aw = a.w,
			      bx = b.x,
			      by = b.y,
			      bz = b.z,
			      bw = b.w;

			return Vec4(
			           bx > ax ? bx : ax,
			           by > ay ? by : ay,
			           bz > az ? bz : az,
			           bw < aw ? bw : aw
			       );
		}

		inline static Vec4 Lerp(const Vec4& a, const Vec4& b, const float t) {

			return Vec4(
			           Mathf.Lerp(a.x, b.x, t),
			           Mathf.Lerp(a.y, b.y, t),
			           Mathf.Lerp(a.z, b.z, t),
			           Mathf.Lerp(a.w, b.w, t)
			       );
		}

		inline static float Dot(const Vec4& a, const Vec4& b) {

			return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
		}

		inline Vec4 operator -();

		inline float operator [] (int i) const;
		inline float& operator [] (int i);

		inline Vec4 operator +(const Vec4& v);
		inline Vec4 operator -(const Vec4& v);
		inline Vec4 operator *(const Vec4& v);
		inline Vec4 operator /(const Vec4& v);

		inline void operator +=(const Vec4& v);
		inline void operator -=(const Vec4& v);
		inline void operator *=(const Vec4& v);
		inline void operator /=(const Vec4& v);

		inline Vec4 operator +(const float s);
		inline Vec4 operator -(const float s);
		inline Vec4 operator *(const float s);
		inline Vec4 operator /(const float s);

		inline void operator +=(const float s);
		inline void operator -=(const float s);
		inline void operator *=(const float s);
		inline void operator /=(const float s);

		inline Vec4& operator =(const Vec4& v);
		inline Vec4& operator =(const Vec4 && v);

		inline bool operator ==(const Vec4& v);
		inline bool operator !=(const Vec4& v);

		inline std::string ToString(int p = 5);
	};
};

#endif