#ifndef ODIN_COLOR_H
#define ODIN_COLOR_H


namespace Odin {

	struct Color {

		float r;
		float g;
		float b;

		inline explicit Color(void);
		inline explicit Color(const float X);
		inline explicit Color(const float R, const float G, const float B);
		inline Color(const Vec2& v);
		inline Color(const Vec3& v);
		inline Color(const Vec4& v);
		inline Color(const Color& c);
		inline Color(const Color&& c);

		inline ~Color(void);

		inline Color& Set(const float R, const float G, const float B);
		inline Color& Zero(void);

		inline float Dot(const Color c);

		inline float LengthSq(void);
		inline float Length(void);

		inline float Normalize(void);
		inline void CNormalize(void);

		inline Color& Lerp(const Color& c, const float t);

		inline static Color Lerp(const Color& a, const Color& b, const float t) {

			return Color(
			           Mathf.Lerp(a.r, b.r, t),
			           Mathf.Lerp(a.g, b.g, t),
			           Mathf.Lerp(a.b, b.b, t)
			       );
		}

		inline static float Dot(const Color& a, const Color& b) {

			return a.r * b.r + a.g * b.g + a.b * b.b;
		}

		inline Color operator -();

		inline float operator [] (int i) const;
		inline float& operator [] (int i);

		inline Color operator +(const Color& c);
		inline Color operator -(const Color& c);
		inline Color operator *(const Color& c);
		inline Color operator /(const Color& c);

		inline void operator +=(const Color& c);
		inline void operator -=(const Color& c);
		inline void operator *=(const Color& c);
		inline void operator /=(const Color& c);

		inline Color operator +(const float s);
		inline Color operator -(const float s);
		inline Color operator *(const float s);
		inline Color operator /(const float s);

		inline void operator +=(const float s);
		inline void operator -=(const float s);
		inline void operator *=(const float s);
		inline void operator /=(const float s);

		inline Color& operator =(const Color& c);
		inline Color& operator =(const Color && c);

		inline bool operator ==(const Color& c);
		inline bool operator !=(const Color& c);

		inline std::string ToString(int p = 5);
	};
}

#endif