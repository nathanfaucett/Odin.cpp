#ifndef _ODIN_COLOR_H_
#define _ODIN_COLOR_H_


namespace Odin {

	class Color {

		public:

			float32 r;
			float32 g;
			float32 b;

			inline explicit Color(void);
			inline explicit Color(float32 X);
			inline explicit Color(float32 R, float32 G, float32 B);
			inline Color(const Vec2& v);
			inline Color(const Vec3& v);
			inline Color(const Vec4& v);
			inline Color(const Color& c);
			inline Color(const Color&& c);

			inline ~Color(void);

			inline Color& Set(float32 R, float32 G, float32 B);
			inline Color& Zero(void);

			inline float32 Dot(const Color c);

			inline float32 LengthSq(void);
			inline float32 Length(void);

			inline float32 Normalize(void);
			inline void CNormalize(void);

			inline Color& Lerp(const Color& c, float32 t);

			inline static Color Lerp(const Color& a, const Color& b, float32 t) {

				return Color(
				           Mathf.Lerp(a.r, b.r, t),
				           Mathf.Lerp(a.g, b.g, t),
				           Mathf.Lerp(a.b, b.b, t)
				       );
			}

			inline static float32 Dot(const Color& a, const Color& b) {

				return a.r * b.r + a.g * b.g + a.b * b.b;
			}

			inline Color& operator -();

			inline float32 operator [] (int32 i) const;
			inline float32& operator [] (int32 i);

			inline Color operator +(const Color& c);
			inline Color operator -(const Color& c);
			inline Color operator *(const Color& c);
			inline Color operator /(const Color& c);

			inline void operator +=(const Color& c);
			inline void operator -=(const Color& c);
			inline void operator *=(const Color& c);
			inline void operator /=(const Color& c);

			inline Color operator +(float32 s);
			inline Color operator -(float32 s);
			inline Color operator *(float32 s);
			inline Color operator /(float32 s);

			inline void operator +=(float32 s);
			inline void operator -=(float32 s);
			inline void operator *=(float32 s);
			inline void operator /=(float32 s);

			inline Color& operator =(const Color& c);
			inline Color& operator =(const Color && c);

			inline bool operator ==(const Color& c);
			inline bool operator !=(const Color& c);

			inline std::string ToString(int32 p = 5);
	};
}

#endif