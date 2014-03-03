#ifndef _ODIN_VEC3_H
#define _ODIN_VEC3_H


namespace Odin {

	class Vec3 {

		public:

			float32 x;
			float32 y;
			float32 z;

			inline explicit Vec3(void);
			inline explicit Vec3(float32 X);
			inline explicit Vec3(float32 X, float32 Y);
			inline explicit Vec3(float32 X, float32 Y, float32 Z);
			inline Vec3(const Vec2& v);
			inline Vec3(const Vec3& v);
			inline Vec3(const Vec3&& v);
			inline Vec3(const Vec4& v);
			inline Vec3(const Color& v);
			inline ~Vec3(void);

			inline Vec3& Set(float32 X, float32 Y);
			inline Vec3& Set(float32 X, float32 Y, float32 Z);
			inline Vec3& Zero(void);

			inline float32 Dot(const Vec3 v);
			inline Vec3 Cross(const Vec3 v);

			inline float32 LengthSq(void);
			inline float32 Length(void);
			inline float32 Normalize(void);

			inline Vec3& Lerp(const Vec3& v, float32 t);

			inline Vec3& Min(const Vec3& v);
			inline Vec3& Max(const Vec3& v);

			inline static Vec3 Min(const Vec3& a, const Vec3& b) {
				float32 ax = a.x,
				        ay = a.y,
				        az = a.z,
				        bx = b.x,
				        by = b.y,
				        bz = b.z;

				return Vec3(
				           bx < ax ? bx : ax,
				           by < ay ? by : ay,
				           bz < az ? bz : az
				       );
			}

			inline static Vec3 Max(const Vec3& a, const Vec3& b) {
				float32 ax = a.x,
				        ay = a.y,
				        az = a.z,
				        bx = b.x,
				        by = b.y,
				        bz = b.z;

				return Vec3(
				           bx > ax ? bx : ax,
				           by > ay ? by : ay,
				           bz > az ? bz : az
				       );
			}

			inline static Vec3 Lerp(const Vec3& a, const Vec3& b, float32 t) {

				return Vec3(
				           Mathf.Lerp(a.x, b.x, t),
				           Mathf.Lerp(a.y, b.y, t),
				           Mathf.Lerp(a.z, b.z, t)
				       );
			}

			inline static float32 Dot(const Vec3& a, const Vec3& b) {

				return a.x * b.x + a.y * b.y + a.z * b.z;
			}

			inline static Vec3 Cross(const Vec3& a, const Vec3& b) {

				return Vec3(
				           a.y * b.z - a.z * b.y,
				           a.z * b.x - a.x * b.z,
				           a.x * b.y - a.y * b.x
				       );
			}

			static const Vec3 ZERO;
			static const Vec3 UNIT_X;
			static const Vec3 UNIT_Y;
			static const Vec3 UNIT_Z;
			static const Vec3 NEGATIVE_UNIT_X;
			static const Vec3 NEGATIVE_UNIT_Y;
			static const Vec3 NEGATIVE_UNIT_Z;
			static const Vec3 UNIT_SCALE;

			inline Vec3& operator -();

			inline float32 operator [] (int32 i) const;
			inline float32& operator [] (int32 i);

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


			inline Vec3 operator +(float32 s);
			inline Vec3 operator -(float32 s);
			inline Vec3 operator *(float32 s);
			inline Vec3 operator /(float32 s);

			inline void operator +=(float32 s);
			inline void operator -=(float32 s);
			inline void operator *=(float32 s);
			inline void operator /=(float32 s);

			inline Vec3& operator =(const Vec3& v);
			inline Vec3& operator =(const Vec3 && v);

			inline bool operator ==(const Vec3& v);
			inline bool operator !=(const Vec3& v);

			inline std::string ToString(int32 p = 5);
	};
}

#endif