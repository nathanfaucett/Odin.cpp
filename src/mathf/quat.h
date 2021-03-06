#ifndef ODIN_QUAT_H
#define ODIN_QUAT_H

namespace Odin {

	template <typename Type> class Quat {

		public:

			Type x;
			Type y;
			Type z;
			Type w;

			inline explicit Quat(void);
			inline explicit Quat(Type X, Type Y, Type Z);
			inline explicit Quat(Type X, Type Y, Type Z, Type W);
			inline Quat(const Vec3<Type>& v);
			inline Quat(const Vec3<Type>& v, Type angle);
			inline Quat(const Vec4<Type>& v);
			inline Quat(const Quat<Type>& q);
			inline Quat(const Quat<Type>&& q);
			inline ~Quat(void);

			inline Quat<Type>& Set(Type X, Type Y, Type Z);
			inline Quat<Type>& Set(Type X, Type Y, Type Z, Type W);
			inline Quat<Type>& Zero(void);

			inline Type Dot(const Quat<Type> q);
			inline Type LengthSq(void);
			inline Type Length(void);
			inline Type Normalize(void);

			inline Quat<Type> Lerp(const Quat<Type>& q, float32 t);
			inline Quat<Type>& Slerp(const Quat<Type>& q, float32 t);

			inline static Quat<Type> Lerp(const Quat<Type>& a, const Quat<Type>& b, float32 t) {

				return Quat(
				           Mathf.Lerp(a.x, b.x, t),
				           Mathf.Lerp(a.y, b.y, t),
				           Mathf.Lerp(a.z, b.z, t),
				           Mathf.Lerp(a.w, b.w, t)
				       );
			}

			inline static Quat<Type> Slerp(const Quat<Type>& a, const Quat<Type>& b, float32 t) {
				Type ax = a.x,
				     ay = a.y,
				     az = a.z,
				     aw = a.w,
				     bx = b.x,
				     by = b.y,
				     bz = b.z,
				     bw = b.w,

				     omega, sinom, scale0, scale1,
				     cosom = ax * bx + ay * by + az * bz + aw * bw;

				if (cosom < 0) {
					cosom *= -static_cast<Type>(1);
					bx *= -static_cast<Type>(1);
					by *= -static_cast<Type>(1);
					bz *= -static_cast<Type>(1);
					bw *= -static_cast<Type>(1);
				}

				if (1 - cosom > Mathf.Epsilon) {
					omega = acosf(cosom);
					sinom = static_cast<Type>(1) / Mathf.Sin(omega);
					scale0 = Mathf.Sin((1 - t) * omega) * sinom;
					scale1 = Mathf.Sin(t * omega) * sinom;

				} else {
					scale0 = static_cast<Type>(1) - t;
					scale1 = t;
				}

				return Quat(
				           scale0 * ax + scale1 * bx,
				           scale0 * ay + scale1 * by,
				           scale0 * az + scale1 * bz,
				           scale0 * aw + scale1 * bw
				       );
			}

			inline static Type Dot(const Quat<Type>& a, const Quat<Type>& b) {

				return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
			}

			inline Quat<Type>& FromMatrix(const Mat3<Type>& m);
			inline Quat<Type>& FromMatrix(const Mat4<Type>& m);
			inline Quat<Type>& FromMatrix(const Mat43<Type>& m);

			inline Quat<Type>& operator -(void);
			inline Quat<Type> Inverse(void);

			inline Quat<Type>& CalculateW(void);

			inline Type GetRotationX(void);
			inline Type GetRotationY(void);
			inline Type GetRotationZ(void);
			
			inline Quat<Type>& RotateX(Type angle);
			inline Quat<Type>& RotateY(Type angle);
			inline Quat<Type>& RotateZ(Type angle);
			inline Quat<Type>& Rotate(Type x, Type y, Type z);
			inline Quat<Type>& LookRotation(const Vec3<Type>& forward, const Vec3<Type>& up);
			inline Quat<Type>& FromAxisAngle(const Vec3<Type>& axis, Type angle);
			inline Quat<Type>& FromVec3s(const Vec3<Type>& u, const Vec3<Type>& v);

			inline Type operator [] (int32 i) const;
			inline Type& operator [] (int32 i);

			inline Quat<Type> operator *(const Mat3<Type>& m);
			inline Quat<Type>& operator *=(const Mat3<Type>& m);

			inline Quat<Type> operator *(const Mat4<Type>& m);
			inline Quat<Type>& operator *=(const Mat4<Type>& m);

			inline Quat<Type> operator *(const Mat43<Type>& m);
			inline Quat<Type>& operator *=(const Mat43<Type>& m);
			
			inline Quat<Type> operator +(const Quat<Type>& q);
			inline Quat<Type> operator -(const Quat<Type>& q);
			inline Quat<Type> operator *(const Quat<Type>& q);
			inline Quat<Type> operator /(const Quat<Type>& q);

			inline Quat<Type>& operator +=(const Quat<Type>& q);
			inline Quat<Type>& operator -=(const Quat<Type>& q);
			inline Quat<Type>& operator *=(const Quat<Type>& q);
			inline Quat<Type>& operator /=(const Quat<Type>& q);

			inline Quat<Type> operator +(Type s);
			inline Quat<Type> operator -(Type s);
			inline Quat<Type> operator *(Type s);
			inline Quat<Type> operator /(Type s);

			inline Quat<Type>& operator +=(Type s);
			inline Quat<Type>& operator -=(Type s);
			inline Quat<Type>& operator *=(Type s);
			inline Quat<Type>& operator /=(Type s);

			inline Quat<Type>& operator =(const Quat<Type>& q);
			inline Quat<Type>& operator =(const Quat<Type> && q);

			inline bool operator ==(const Quat<Type>& q);
			inline bool operator !=(const Quat<Type>& q);

			inline std::string ToString(int32 p = 6);
	};
};

#endif