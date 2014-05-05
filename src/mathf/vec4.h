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
			inline Vec4<Type>& Lerp(const Vec4<Type>& v, float32 t);

			inline Vec4<Type>& Min(const Vec4<Type>& v);
			inline Vec4<Type>& Max(const Vec4<Type>& v);
			
			inline Vec4<Type>& TransformProjection(const Mat4<Type>& m);

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

			inline static Vec4<Type> Lerp(const Vec4<Type>& a, const Vec4<Type>& b, float32 t) {

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

			static const Vec4<Type> Right;
			static const Vec4<Type> Forward;
			static const Vec4<Type> Up;
			static const Vec4<Type> Left;
			static const Vec4<Type> Backward;
			static const Vec4<Type> Down;

			inline Vec4<Type>& operator -(void);

			inline Type operator [] (int32 i) const;
			inline Type& operator [] (int32 i);

			inline Vec4<Type> operator *(const Quat<Type>& q);
			inline Vec4<Type>& operator *=(const Quat<Type>& q);

			inline Vec4<Type> operator *(const Mat2<Type>& m);
			inline Vec4<Type>& operator *=(const Mat2<Type>& m);

			inline Vec4<Type> operator *(const Mat32<Type>& m);
			inline Vec4<Type>& operator *=(const Mat32<Type>& m);

			inline Vec4<Type> operator *(const Mat3<Type>& m);
			inline Vec4<Type>& operator *=(const Mat3<Type>& m);

			inline Vec4<Type> operator *(const Mat4<Type>& m);
			inline Vec4<Type>& operator *=(const Mat4<Type>& m);

			inline Vec4<Type> operator *(const Mat43<Type>& m);
			inline Vec4<Type>& operator *=(const Mat43<Type>& m);

			inline Vec4<Type> operator +(const Vec4<Type>& v);
			inline Vec4<Type> operator -(const Vec4<Type>& v);
			inline Vec4<Type> operator *(const Vec4<Type>& v);
			inline Vec4<Type> operator /(const Vec4<Type>& v);

			inline Vec4<Type>& operator +=(const Vec4<Type>& v);
			inline Vec4<Type>& operator -=(const Vec4<Type>& v);
			inline Vec4<Type>& operator *=(const Vec4<Type>& v);
			inline Vec4<Type>& operator /=(const Vec4<Type>& v);

			inline Vec4<Type> operator +(Type s);
			inline Vec4<Type> operator -(Type s);
			inline Vec4<Type> operator *(Type s);
			inline Vec4<Type> operator /(Type s);

			inline Vec4<Type>& operator +=(Type s);
			inline Vec4<Type>& operator -=(Type s);
			inline Vec4<Type>& operator *=(Type s);
			inline Vec4<Type>& operator /=(Type s);

			inline Vec4<Type>& operator =(const Vec2<Type>& v);
			inline Vec4<Type>& operator =(const Vec2<Type> && v);

			inline Vec4<Type>& operator =(const Vec3<Type>& v);
			inline Vec4<Type>& operator =(const Vec3<Type> && v);

			inline Vec4<Type>& operator =(const Vec4<Type>& v);
			inline Vec4<Type>& operator =(const Vec4<Type> && v);

			inline bool operator ==(const Vec4<Type>& v);
			inline bool operator !=(const Vec4<Type>& v);

			inline std::string ToString(int32 p = 6);
	};
};

#endif