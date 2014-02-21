#ifndef ODIN_VEC4_H
#define ODIN_VEC4_H

namespace Odin {

	struct Vec4 {

		float x;
		float y;
		float z;
		float w;

		inline Vec4(void);
		inline Vec4(const float X);
		inline Vec4(const float X, const float Y, const float Z);
		inline Vec4(const float X, const float Y, const float Z, const float W);
		inline Vec4(const Vec2& v);
		inline Vec4(const Vec3& v);
		inline Vec4(const Vec4& v);
		inline ~Vec4(void);

		inline Vec4& Set(const float X, const float Y, const float Z);
		inline Vec4& Set(const float X, const float Y, const float Z, const float W);
		inline Vec4& Zero();

		inline float Dot(const Vec4 v);
		inline float LengthSq();
		inline float Length();
		inline float Normalize();
		inline Vec4& Lerp(const Vec4& v, const float t);

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

		inline Vec4 operator =(const Vec4& v);
		inline bool operator ==(const Vec4& v);
		inline bool operator !=(const Vec4& v);

		inline std::string ToString(int p = 5);
	};
};

#endif