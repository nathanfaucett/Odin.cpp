#ifndef ODIN_VEC4_H
#define ODIN_VEC4_H

namespace Odin {

	template <typename Type> class Vec4 {

		public:

			Type x;
			Type y;
			Type z;
			Type w;

			inline explicit Vec4(void);
			inline explicit Vec4(Type X);
			inline explicit Vec4(Type X, Type Y, Type Z);
			inline explicit Vec4(Type X, Type Y, Type Z, Type W);
			inline Vec4(const Vec2<Type>& v);
			inline Vec4(const Vec3<Type>& v);
			inline Vec4(const Vec4<Type>& v);
			inline Vec4(const Vec4<Type>&& v);
			inline Vec4(const Color<Type>& c);
			inline ~Vec4(void);

			inline Vec4<Type>& Set(Type X, Type Y);
			inline Vec4<Type>& Set(Type X, Type Y, Type Z);
			inline Vec4<Type>& Set(Type X, Type Y, Type Z, Type W);
			inline Vec4<Type>& Zero(void);

			inline Type Dot(const Vec4<Type> v);
			inline Type LengthSq(void);
			inline Type Length(void);
			inline Type Normalize(void);
			inline Vec4<Type>& Lerp(const Vec4<Type>& v, Type t);

			inline Vec4<Type>& Min(const Vec4<Type>& v);
			inline Vec4<Type>& Max(const Vec4<Type>& v);

			inline static Vec4<Type> Min(const Vec4<Type>& a, const Vec4<Type>& b) {
				Type ax = a.x,
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

			inline static Vec4<Type> Max(const Vec4<Type>& a, const Vec4<Type>& b) {
				Type ax = a.x,
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

			inline static Vec4<Type> Lerp(const Vec4<Type>& a, const Vec4<Type>& b, Type t) {

				return Vec4(
				           Mathf.Lerp(a.x, b.x, t),
				           Mathf.Lerp(a.y, b.y, t),
				           Mathf.Lerp(a.z, b.z, t),
				           Mathf.Lerp(a.w, b.w, t)
				       );
			}

			inline static Type Dot(const Vec4<Type>& a, const Vec4<Type>& b) {

				return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
			}

			static const Vec4<Type> ZERO;
			static const Vec4<Type> UNIT_X;
			static const Vec4<Type> UNIT_Y;
			static const Vec4<Type> UNIT_Z;
			static const Vec4<Type> UNIT_W;
			static const Vec4<Type> NEGATIVE_UNIT_X;
			static const Vec4<Type> NEGATIVE_UNIT_Y;
			static const Vec4<Type> NEGATIVE_UNIT_Z;
			static const Vec4<Type> NEGATIVE_UNIT_W;
			static const Vec4<Type> UNIT_SCALE;

			inline Vec4<Type>& operator -();

			inline Type operator [] (int32 i) const;
			inline Type& operator [] (int32 i);

			inline Vec4<Type> operator +(const Vec4<Type>& v);
			inline Vec4<Type> operator -(const Vec4<Type>& v);
			inline Vec4<Type> operator *(const Vec4<Type>& v);
			inline Vec4<Type> operator /(const Vec4<Type>& v);

			inline void operator +=(const Vec4<Type>& v);
			inline void operator -=(const Vec4<Type>& v);
			inline void operator *=(const Vec4<Type>& v);
			inline void operator /=(const Vec4<Type>& v);

			inline Vec4<Type> operator +(Type s);
			inline Vec4<Type> operator -(Type s);
			inline Vec4<Type> operator *(Type s);
			inline Vec4<Type> operator /(Type s);

			inline void operator +=(Type s);
			inline void operator -=(Type s);
			inline void operator *=(Type s);
			inline void operator /=(Type s);

			inline Vec4<Type>& operator =(const Vec4<Type>& v);
			inline Vec4<Type>& operator =(const Vec4<Type> && v);

			inline bool operator ==(const Vec4<Type>& v);
			inline bool operator !=(const Vec4<Type>& v);

			inline std::string ToString(int32 p = 5);
	};
};

#endif