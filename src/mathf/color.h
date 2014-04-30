#ifndef ODIN_COLOR_H
#define ODIN_COLOR_H


namespace Odin {

	template <typename Type> class Color {
	
		public:

			Type r;
			Type g;
			Type b;

			inline explicit Color(void);
			inline explicit Color(Type X);
			inline explicit Color(Type R, Type G, Type B);
			inline Color(const Vec2<Type>& v);
			inline Color(const Vec3<Type>& v);
			inline Color(const Vec4<Type>& v);
			inline Color(const Color<Type>& c);
			inline Color(const Color<Type>&& c);

			inline ~Color(void);

			inline Color<Type>& Set(Type R, Type G, Type B);
			inline Color<Type>& Set(std::string value);
			inline Color<Type>& Zero(void);

			inline Type Dot(const Color<Type> c);

			inline Type LengthSq(void);
			inline Type Length(void);

			inline Type Normalize(void);
			inline void CNormalize(void);
			inline void HexNormalize(void);

			inline Color<Type>& Lerp(const Color<Type>& c, Type t);

			inline static Color<Type> Lerp(const Color<Type>& a, const Color<Type>& b, Type t) {

				return Color(
				           Mathf.Lerp(a.r, b.r, t),
				           Mathf.Lerp(a.g, b.g, t),
				           Mathf.Lerp(a.b, b.b, t)
				       );
			}

			inline static Type Dot(const Color<Type>& a, const Color<Type>& b) {

				return a.r * b.r + a.g * b.g + a.b * b.b;
			}

			static const Color<Type> Black;
			static const Color<Type> White;
			static const Color<Type> Red;
			static const Color<Type> Green;
			static const Color<Type> Blue;
			static const Color<Type> Yellow;
			static const Color<Type> Orange;

			inline Color<Type>& operator -();

			inline Type operator [] (int32 i) const;
			inline Type& operator [] (int32 i);

			inline Color<Type> operator +(const Color<Type>& c);
			inline Color<Type> operator -(const Color<Type>& c);
			inline Color<Type> operator *(const Color<Type>& c);
			inline Color<Type> operator /(const Color<Type>& c);

			inline void operator +=(const Color<Type>& c);
			inline void operator -=(const Color<Type>& c);
			inline void operator *=(const Color<Type>& c);
			inline void operator /=(const Color<Type>& c);

			inline Color<Type> operator +(Type s);
			inline Color<Type> operator -(Type s);
			inline Color<Type> operator *(Type s);
			inline Color<Type> operator /(Type s);

			inline void operator +=(Type s);
			inline void operator -=(Type s);
			inline void operator *=(Type s);
			inline void operator /=(Type s);

			inline Color<Type>& operator =(const Color<Type>& c);
			inline Color<Type>& operator =(const Color<Type> && c);

			inline bool operator ==(const Color<Type>& c);
			inline bool operator !=(const Color<Type>& c);

			inline std::string ToString(int32 p = 6);
	};
}

#endif