#ifndef ODIN_VEC3_H
#define ODIN_VEC3_H


namespace Odin {

	struct Vec3 {

		float x;
		float y;
		float z;

		inline explicit Vec3(void);
		inline explicit Vec3(const float X);
		inline explicit Vec3(const float X, const float Y);
		inline explicit Vec3(const float X, const float Y, const float Z);
		inline Vec3(const Vec2& v);
		inline Vec3(const Vec3& v);
		inline Vec3(const Vec3&& v);
		inline Vec3(const Vec4& v);
		inline Vec3(const Color& v);
		inline ~Vec3(void);

		inline Vec3& Set(const float X, const float Y, const float Z);
		inline Vec3& Zero(void);

		inline float Dot(const Vec3 v);
		inline Vec3 Cross(const Vec3 v);

		inline float LengthSq(void);
		inline float Length(void);
		inline float Normalize(void);

		inline Vec3& Lerp(const Vec3& v, const float t);

		inline static Vec3 Lerp(const Vec3& a, const Vec3& b, const float t) {

			return Vec3(
			           Mathf.Lerp(a.x, b.x, t),
			           Mathf.Lerp(a.y, b.y, t),
			           Mathf.Lerp(a.z, b.z, t)
			       );
		}

		inline static float Dot(const Vec3& a, const Vec3& b) {

			return a.x * b.x + a.y * b.y + a.z * b.z;
		}

		inline static Vec3 Cross(const Vec3& a, const Vec3& b) {

			return Vec3(
			           a.y * b.z - a.z * b.y,
			           a.z * b.x - a.x * b.z,
			           a.x * b.y - a.y * b.x
			       );
		}

		inline Vec3 operator -();

		inline float operator [] (int i) const;
		inline float& operator [] (int i);

		inline Vec3 operator *(const Mat2& m);
		inline Vec3& operator *=(const Mat2& m);

		inline Vec3 operator *(const Mat32& m);
		inline Vec3& operator *=(const Mat32& m);

		inline Vec3 operator *(const Mat4& m);
		inline Vec3& operator *=(const Mat4& m);

		inline Vec3 operator +(const Vec3& v);
		inline Vec3 operator -(const Vec3& v);
		inline Vec3 operator *(const Vec3& v);
		inline Vec3 operator /(const Vec3& v);

		inline void operator +=(const Vec3& v);
		inline void operator -=(const Vec3& v);
		inline void operator *=(const Vec3& v);
		inline void operator /=(const Vec3& v);


		inline Vec3 operator +(const float s);
		inline Vec3 operator -(const float s);
		inline Vec3 operator *(const float s);
		inline Vec3 operator /(const float s);

		inline void operator +=(const float s);
		inline void operator -=(const float s);
		inline void operator *=(const float s);
		inline void operator /=(const float s);

		inline Vec3& operator =(const Vec3& v);
		inline Vec3& operator =(const Vec3 && v);

		inline bool operator ==(const Vec3& v);
		inline bool operator !=(const Vec3& v);

		inline std::string ToString(int p = 5);
	};
}

#endif