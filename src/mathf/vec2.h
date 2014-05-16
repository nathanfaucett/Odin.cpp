#ifndef ODIN_VEC2_H
#define ODIN_VEC2_H

namespace Odin {

	template <typename Type> class Vec2 {

		public:

			Type x;
			Type y;

			inline explicit Vec2(void);
			inline explicit Vec2(Type X);
			inline explicit Vec2(Type X, Type Y);
			inline Vec2(const Vec2<Type>& v);
			inline Vec2(const Vec2<Type>&& v);
			inline Vec2(const Vec3<Type>& v);
			inline Vec2(const Vec4<Type>& v);
			inline Vec2(const Color<Type>& c);
			inline ~Vec2(void);

			inline Vec2<Type>& Set(Type X, Type Y);
			inline Vec2<Type>& Zero(void);

			inline Type Dot(const Vec2<Type>& v);
			inline Type Cross(const Vec2<Type>& v);
			inline Type LengthSq(void);
			inline Type Length(void);
			inline Type Normalize(void);

			inline Vec2<Type>& Lerp(const Vec2<Type>& v, float32 t);

			inline Vec2<Type>& Min(const Vec2<Type>& v);
			inline Vec2<Type>& Max(const Vec2<Type>& v);
			
			inline Vec2<Type>& TransformProjection(const Mat4<Type>& m);

			inline static Vec2<Type> Min(const Vec2<Type>& a, const Vec2<Type>& b) {
				Type ax = a.x,
				     ay = a.y,
				     bx = b.x,
				     by = b.y;

				return Vec2(
				           bx < ax ? bx : ax,
				           by < ay ? by : ay
				       );
			}

			inline static Vec2<Type> Max(const Vec2<Type>& a, const Vec2<Type>& b) {
				Type ax = a.x,
				     ay = a.y,
				     bx = b.x,
				     by = b.y;

				return Vec2(
				           bx > ax ? bx : ax,
				           by > ay ? by : ay
				       );
			}

			inline static Vec2<Type> Lerp(const Vec2<Type>& a, const Vec2<Type>& b, float32 t) {

				return Vec2(
				           Mathf.Lerp(a.x, b.x, t),
				           Mathf.Lerp(a.y, b.y, t)
				       );
			}

			inline static Type Dot(const Vec2<Type>& a, const Vec2<Type>& b) {

				return a.x * b.x + a.y * b.y;
			}

			inline static Type Cross(const Vec2<Type>& a, const Vec2<Type>& b) {

				return a.x * b.y - a.y * b.x;
			}

			static Vec2<Type> Right;
			static Vec2<Type> Up;
			static Vec2<Type> Left;
			static Vec2<Type> Down;

			inline Vec2<Type>& operator -(void);

			inline Type operator [] (int32 i) const;
			inline Type& operator [] (int32 i);

			inline Vec2<Type> operator *(const Quat<Type>& q);
			inline Vec2<Type>& operator *=(const Quat<Type>& q);

			inline Vec2<Type> operator *(const Mat2<Type>& m);
			inline Vec2<Type>& operator *=(const Mat2<Type>& m);

			inline Vec2<Type> operator *(const Mat32<Type>& m);
			inline Vec2<Type>& operator *=(const Mat32<Type>& m);

			inline Vec2<Type> operator *(const Mat4<Type>& m);
			inline Vec2<Type>& operator *=(const Mat4<Type>& m);

			inline Vec2<Type> operator *(const Mat43<Type>& m);
			inline Vec2<Type>& operator *=(const Mat43<Type>& m);

			inline Vec2<Type> operator +(const Vec2<Type>& v);
			inline Vec2<Type> operator -(const Vec2<Type>& v);
			inline Vec2<Type> operator *(const Vec2<Type>& v);
			inline Vec2<Type> operator /(const Vec2<Type>& v);

			inline Vec2<Type>& operator +=(const Vec2<Type>& v);
			inline Vec2<Type>& operator -=(const Vec2<Type>& v);
			inline Vec2<Type>& operator *=(const Vec2<Type>& v);
			inline Vec2<Type>& operator /=(const Vec2<Type>& v);

			inline Vec2<Type> operator +(const Vec3<Type>& v);
			inline Vec2<Type> operator -(const Vec3<Type>& v);
			inline Vec2<Type> operator *(const Vec3<Type>& v);
			inline Vec2<Type> operator /(const Vec3<Type>& v);

			inline Vec2<Type>& operator +=(const Vec3<Type>& v);
			inline Vec2<Type>& operator -=(const Vec3<Type>& v);
			inline Vec2<Type>& operator *=(const Vec3<Type>& v);
			inline Vec2<Type>& operator /=(const Vec3<Type>& v);

			inline Vec2<Type> operator +(Type s);
			inline Vec2<Type> operator -(Type s);
			inline Vec2<Type> operator *(Type s);
			inline Vec2<Type> operator /(Type s);

			inline Vec2<Type>& operator +=(Type s);
			inline Vec2<Type>& operator -=(Type s);
			inline Vec2<Type>& operator *=(Type s);
			inline Vec2<Type>& operator /=(Type s);

			inline Vec2<Type>& operator =(const Vec2<Type>& v);
			inline Vec2<Type>& operator =(const Vec2<Type> && v);

			inline Vec2<Type>& operator =(const Vec3<Type>& v);
			inline Vec2<Type>& operator =(const Vec3<Type> && v);

			inline Vec2<Type>& operator =(const Vec4<Type>& v);
			inline Vec2<Type>& operator =(const Vec4<Type> && v);

			inline bool operator ==(const Vec2<Type>& v);
			inline bool operator !=(const Vec2<Type>& v);

			inline std::string ToString(int32 p = 6);
	};
}
#endif