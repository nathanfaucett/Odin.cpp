#ifndef _ODIN_VEC3_H_
#define _ODIN_VEC3_H_


namespace Odin {

	template <typename Type> class Vec3 {

		public:

			Type x;
			Type y;
			Type z;

			inline explicit Vec3(void);
			inline explicit Vec3(Type X);
			inline explicit Vec3(Type X, Type Y);
			inline explicit Vec3(Type X, Type Y, Type Z);
			inline Vec3(const Vec2<Type>& v);
			inline Vec3(const Vec3<Type>& v);
			inline Vec3(const Vec3<Type>&& v);
			inline Vec3(const Vec4<Type>& v);
			inline Vec3(const Color<Type>& v);
			inline ~Vec3(void);

			inline Vec3<Type>& Set(Type X, Type Y);
			inline Vec3<Type>& Set(Type X, Type Y, Type Z);
			inline Vec3<Type>& Zero(void);

			inline Type Dot(const Vec3<Type> v);
			inline Vec3<Type> Cross(const Vec3<Type> v);

			inline Type LengthSq(void);
			inline Type Length(void);
			inline Type Normalize(void);

			inline Vec3<Type>& Lerp(const Vec3<Type>& v, Type t);

			inline Vec3<Type>& Min(const Vec3<Type>& v);
			inline Vec3<Type>& Max(const Vec3<Type>& v);

			inline static Vec3<Type> Min(const Vec3<Type>& a, const Vec3<Type>& b) {
				Type ax = a.x,
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

			inline static Vec3<Type> Max(const Vec3<Type>& a, const Vec3<Type>& b) {
				Type ax = a.x,
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

			inline static Vec3<Type> Lerp(const Vec3<Type>& a, const Vec3<Type>& b, Type t) {

				return Vec3(
				           Mathf.Lerp(a.x, b.x, t),
				           Mathf.Lerp(a.y, b.y, t),
				           Mathf.Lerp(a.z, b.z, t)
				       );
			}

			inline static Type Dot(const Vec3<Type>& a, const Vec3<Type>& b) {

				return a.x * b.x + a.y * b.y + a.z * b.z;
			}

			inline static Vec3<Type> Cross(const Vec3<Type>& a, const Vec3<Type>& b) {

				return Vec3(
				           a.y * b.z - a.z * b.y,
				           a.z * b.x - a.x * b.z,
				           a.x * b.y - a.y * b.x
				       );
			}

			static const Vec3<Type> ZERO;
			static const Vec3<Type> UNIT_X;
			static const Vec3<Type> UNIT_Y;
			static const Vec3<Type> UNIT_Z;
			static const Vec3<Type> NEGATIVE_UNIT_X;
			static const Vec3<Type> NEGATIVE_UNIT_Y;
			static const Vec3<Type> NEGATIVE_UNIT_Z;
			static const Vec3<Type> UNIT_SCALE;

			inline Vec3<Type>& operator -();

			inline Type operator [] (int32 i) const;
			inline Type& operator [] (int32 i);

			inline Vec3<Type> operator *(const Mat2<Type>& m);
			inline Vec3<Type>& operator *=(const Mat2<Type>& m);

			inline Vec3<Type> operator *(const Mat32<Type>& m);
			inline Vec3<Type>& operator *=(const Mat32<Type>& m);

			inline Vec3<Type> operator *(const Mat4<Type>& m);
			inline Vec3<Type>& operator *=(const Mat4<Type>& m);

			inline Vec3<Type> operator +(const Vec3<Type>& v);
			inline Vec3<Type> operator -(const Vec3<Type>& v);
			inline Vec3<Type> operator *(const Vec3<Type>& v);
			inline Vec3<Type> operator /(const Vec3<Type>& v);

			inline void operator +=(const Vec3<Type>& v);
			inline void operator -=(const Vec3<Type>& v);
			inline void operator *=(const Vec3<Type>& v);
			inline void operator /=(const Vec3<Type>& v);


			inline Vec3<Type> operator +(Type s);
			inline Vec3<Type> operator -(Type s);
			inline Vec3<Type> operator *(Type s);
			inline Vec3<Type> operator /(Type s);

			inline void operator +=(Type s);
			inline void operator -=(Type s);
			inline void operator *=(Type s);
			inline void operator /=(Type s);

			inline Vec3<Type>& operator =(const Vec3<Type>& v);
			inline Vec3<Type>& operator =(const Vec3<Type> && v);

			inline bool operator ==(const Vec3<Type>& v);
			inline bool operator !=(const Vec3<Type>& v);

			inline std::string ToString(int32 p = 5);
	};
}

#endif