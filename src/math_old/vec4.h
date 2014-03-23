#ifndef _ODIN_VEC4_H_
#define _ODIN_VEC4_H_

namespace Odin {

	class Vec4 {

		public:

			float32 x;
			float32 y;
			float32 z;
			float32 w;

			inline explicit Vec4(void);
			inline explicit Vec4(float32 X);
			inline explicit Vec4(float32 X, float32 Y, float32 Z);
			inline explicit Vec4(float32 X, float32 Y, float32 Z, float32 W);
			inline Vec4(const Vec2& v);
			inline Vec4(const Vec3& v);
			inline Vec4(const Vec4& v);
			inline Vec4(const Vec4&& v);
			inline Vec4(const Color& v);
			inline ~Vec4(void);

			inline Vec4& Set(float32 X, float32 Y);
			inline Vec4& Set(float32 X, float32 Y, float32 Z);
			inline Vec4& Set(float32 X, float32 Y, float32 Z, float32 W);
			inline Vec4& Zero(void);

			inline float32 Dot(const Vec4 v);
			inline float32 LengthSq(void);
			inline float32 Length(void);
			inline float32 Normalize(void);
			inline Vec4& Lerp(const Vec4& v, float32 t);

			inline Vec4& Min(const Vec4& v);
			inline Vec4& Max(const Vec4& v);

			inline static Vec4 Min(const Vec4& a, const Vec4& b) {
				float32 ax = a.x,
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
				float32 ax = a.x,
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

			inline static Vec4 Lerp(const Vec4& a, const Vec4& b, float32 t) {

				return Vec4(
				           Mathf.Lerp(a.x, b.x, t),
				           Mathf.Lerp(a.y, b.y, t),
				           Mathf.Lerp(a.z, b.z, t),
				           Mathf.Lerp(a.w, b.w, t)
				       );
			}

			inline static float32 Dot(const Vec4& a, const Vec4& b) {

				return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
			}

			static const Vec4 ZERO;
			static const Vec4 UNIT_X;
			static const Vec4 UNIT_Y;
			static const Vec4 UNIT_Z;
			static const Vec4 UNIT_W;
			static const Vec4 NEGATIVE_UNIT_X;
			static const Vec4 NEGATIVE_UNIT_Y;
			static const Vec4 NEGATIVE_UNIT_Z;
			static const Vec4 NEGATIVE_UNIT_W;
			static const Vec4 UNIT_SCALE;

			inline Vec4& operator -();

			inline float32 operator [] (int32 i) const;
			inline float32& operator [] (int32 i);

			inline Vec4 operator +(const Vec4& v);
			inline Vec4 operator -(const Vec4& v);
			inline Vec4 operator *(const Vec4& v);
			inline Vec4 operator /(const Vec4& v);

			inline void operator +=(const Vec4& v);
			inline void operator -=(const Vec4& v);
			inline void operator *=(const Vec4& v);
			inline void operator /=(const Vec4& v);

			inline Vec4 operator +(float32 s);
			inline Vec4 operator -(float32 s);
			inline Vec4 operator *(float32 s);
			inline Vec4 operator /(float32 s);

			inline void operator +=(float32 s);
			inline void operator -=(float32 s);
			inline void operator *=(float32 s);
			inline void operator /=(float32 s);

			inline Vec4& operator =(const Vec4& v);
			inline Vec4& operator =(const Vec4 && v);

			inline bool operator ==(const Vec4& v);
			inline bool operator !=(const Vec4& v);

			inline std::string ToString(int32 p = 5);
	};
};

#endif