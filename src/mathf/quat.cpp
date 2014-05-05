#ifndef ODIN_QUAT_CPP
#define ODIN_QUAT_CPP

namespace Odin {

	template <typename Type> inline Quat<Type>::Quat(void) {
		x = static_cast<Type>(0);
		y = static_cast<Type>(0);
		z = static_cast<Type>(0);
		w = static_cast<Type>(1);
	}

	template <typename Type> inline Quat<Type>::Quat(Type X, Type Y, Type Z) {
		x = X;
		y = Y;
		z = Z;
		w = static_cast<Type>(1);
	}

	template <typename Type> inline Quat<Type>::Quat(Type X, Type Y, Type Z, Type W) {
		x = X;
		y = Y;
		z = Z;
		w = W;
	}

	template <typename Type> inline Quat<Type>::Quat(const Vec3<Type>& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = static_cast<Type>(1);
	}

	template <typename Type> inline Quat<Type>::Quat(const Vec3<Type>& axis, Type angle) {
		Type halfAngle = angle * static_cast<Type>(0.5),
		     s = Mathf.Sin(halfAngle);

		x = axis.x * s;
		y = axis.y * s;
		z = axis.z * s;
		w = Mathf.Cos(halfAngle);
	}

	template <typename Type> inline Quat<Type>::Quat(const Vec4<Type>& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}

	template <typename Type> inline Quat<Type>::Quat(const Quat<Type>& q) {
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;
	}

	template <typename Type> inline Quat<Type>::Quat(const Quat<Type>&& q) {
		x = std::move(q.x);
		y = std::move(q.y);
		z = std::move(q.z);
		w = std::move(q.w);
	}

	template <typename Type> inline Quat<Type>::~Quat(void) {}

	template <typename Type> inline Quat<Type>& Quat<Type>::Set(Type X, Type Y, Type Z) {
		x = X;
		y = Y;
		z = Z;

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::Set(Type X, Type Y, Type Z, Type W) {
		x = X;
		y = Y;
		z = Z;
		w = W;

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::Zero(void) {
		x = static_cast<Type>(0);
		y = static_cast<Type>(0);
		z = static_cast<Type>(0);
		w = static_cast<Type>(1);

		return *this;
	}

	template <typename Type> inline Type Quat<Type>::Dot(const Quat<Type> q) {

		return x * q.x + y * q.y + z * q.z + w * q.w;
	}

	template <typename Type> inline Type Quat<Type>::LengthSq(void) {

		return x * x + y * y + z * z + w * w;
	}

	template <typename Type> inline Type Quat<Type>::Length(void) {
		Type lenSq = x * x + y * y + z * z + w * w;

		return lenSq == static_cast<Type>(0) ? static_cast<Type>(0) : Mathf.Sqrt(lenSq);
	}

	template <typename Type> inline Type Quat<Type>::Normalize(void) {
		Type lenSq = x * x + y * y + z * z + w * w;

		if (lenSq == static_cast<Type>(0)) {
			return static_cast<Type>(0);
		}

		Type len = Mathf.Sqrt(lenSq),
		     invLen = static_cast<Type>(1) / len;

		x *= invLen;
		y *= invLen;
		z *= invLen;
		w *= invLen;

		return len;
	}

	template <typename Type> inline Quat<Type> Quat<Type>::Lerp(const Quat<Type>& q, float32 t) {
		x = Mathf.Lerp(x, q.x, t);
		y = Mathf.Lerp(y, q.y, t);
		z = Mathf.Lerp(z, q.z, t);
		w = Mathf.Lerp(w, q.w, t);

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::Slerp(const Quat<Type>& q, float32 t) {
		Type ax = x,
		     ay = y,
		     az = z,
		     aw = w,
		     bx = q.x,
		     by = q.y,
		     bz = q.z,
		     bw = q.w,

		     omega, sinom, scale0, scale1,
		     cosom = ax * bx + ay * by + az * bz + aw * bw;

		if (cosom < static_cast<Type>(0)) {
			cosom *= -static_cast<Type>(1);
			bx *= -static_cast<Type>(1);
			by *= -static_cast<Type>(1);
			bz *= -static_cast<Type>(1);
			bw *= -static_cast<Type>(1);
		}

		if (static_cast<Type>(1) - cosom > Mathf.Epsilon) {
			omega = acosf(cosom);
			sinom = static_cast<Type>(1) / Mathf.Sin(omega);
			scale0 = Mathf.Sin((static_cast<Type>(1) - t) * omega) * sinom;
			scale1 = Mathf.Sin(t * omega) * sinom;

		} else {
			scale0 = static_cast<Type>(1) - t;
			scale1 = t;
		}

		x = scale0 * ax + scale1 * bx;
		y = scale0 * ay + scale1 * by;
		z = scale0 * az + scale1 * bz;
		w = scale0 * aw + scale1 * bw;

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::FromMatrix(const Mat3<Type>& m)  {
		Type m11 = m[0],
		     m12 = m[3],
		     m13 = m[6],
		     m21 = m[1],
		     m22 = m[4],
		     m23 = m[7],
		     m31 = m[2],
		     m32 = m[5],
		     m33 = m[8],
		     trace = m11 + m22 + m33,
		     s, invS;

		if (trace > static_cast<Type>(0)) {
			s = static_cast<Type>(0.5) / Mathf.Sqrt(trace + static_cast<Type>(1));

			w = static_cast<Type>(0.25) / s;
			x = (m32 - m23) * s;
			y = (m13 - m31) * s;
			z = (m21 - m12) * s;

		} else if (m11 > m22 && m11 > m33) {
			s = static_cast<Type>(2) * Mathf.Sqrt(static_cast<Type>(1) + m11 - m22 - m33);
			invS = static_cast<Type>(1) / s;

			w = (m32 - m23) * invS;
			x = static_cast<Type>(0.25) * s;
			y = (m12 + m21) * invS;
			z = (m13 + m31) * invS;

		} else if (m22 > m33) {
			s = static_cast<Type>(2) * Mathf.Sqrt(static_cast<Type>(1) + m22 - m11 - m33);
			invS = static_cast<Type>(1) / s;

			w = (m13 - m31) * invS;
			x = (m12 + m21) * invS;
			y = static_cast<Type>(0.25) * s;
			z = (m23 + m32) * invS;

		} else {
			s = static_cast<Type>(2) * Mathf.Sqrt(static_cast<Type>(1) + m33 - m11 - m22);
			invS = static_cast<Type>(1) / s;

			w = (m21 - m12) * invS;
			x = (m13 + m31) * invS;
			y = (m23 + m32) * invS;
			z = static_cast<Type>(0.25) * s;
		}

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::FromMatrix(const Mat4<Type>& m) {
		Type m11 = m[0],
		     m12 = m[4],
		     m13 = m[8],
		     m21 = m[1],
		     m22 = m[5],
		     m23 = m[9],
		     m31 = m[2],
		     m32 = m[6],
		     m33 = m[10],
		     trace = m11 + m22 + m33,
		     s, invS;

		if (trace > static_cast<Type>(0)) {
			s = static_cast<Type>(0.5) / Mathf.Sqrt(trace + static_cast<Type>(1));

			w = static_cast<Type>(0.25) / s;
			x = (m32 - m23) * s;
			y = (m13 - m31) * s;
			z = (m21 - m12) * s;

		} else if (m11 > m22 && m11 > m33) {
			s = static_cast<Type>(2) * Mathf.Sqrt(static_cast<Type>(1) + m11 - m22 - m33);
			invS = static_cast<Type>(1) / s;

			w = (m32 - m23) * invS;
			x = static_cast<Type>(0.25) * s;
			y = (m12 + m21) * invS;
			z = (m13 + m31) * invS;

		} else if (m22 > m33) {
			s = static_cast<Type>(2) * Mathf.Sqrt(static_cast<Type>(1) + m22 - m11 - m33);
			invS = static_cast<Type>(1) / s;

			w = (m13 - m31) * invS;
			x = (m12 + m21) * invS;
			y = static_cast<Type>(0.25) * s;
			z = (m23 + m32) * invS;

		} else {
			s = static_cast<Type>(2) * Mathf.Sqrt(static_cast<Type>(1) + m33 - m11 - m22);
			invS = static_cast<Type>(1) / s;

			w = (m21 - m12) * invS;
			x = (m13 + m31) * invS;
			y = (m23 + m32) * invS;
			z = static_cast<Type>(0.25) * s;
		}

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::FromMatrix(const Mat43<Type>& m) {
		Type m11 = m[0],
		     m12 = m[3],
		     m13 = m[6],
		     m21 = m[1],
		     m22 = m[4],
		     m23 = m[7],
		     m31 = m[2],
		     m32 = m[5],
		     m33 = m[8],
		     trace = m11 + m22 + m33,
		     s, invS;

		if (trace > static_cast<Type>(0)) {
			s = static_cast<Type>(0.5) / Mathf.Sqrt(trace + static_cast<Type>(1));

			w = static_cast<Type>(0.25) / s;
			x = (m32 - m23) * s;
			y = (m13 - m31) * s;
			z = (m21 - m12) * s;

		} else if (m11 > m22 && m11 > m33) {
			s = static_cast<Type>(2) * Mathf.Sqrt(static_cast<Type>(1) + m11 - m22 - m33);
			invS = static_cast<Type>(1) / s;

			w = (m32 - m23) * invS;
			x = static_cast<Type>(0.25) * s;
			y = (m12 + m21) * invS;
			z = (m13 + m31) * invS;

		} else if (m22 > m33) {
			s = static_cast<Type>(2) * Mathf.Sqrt(static_cast<Type>(1) + m22 - m11 - m33);
			invS = static_cast<Type>(1) / s;

			w = (m13 - m31) * invS;
			x = (m12 + m21) * invS;
			y = static_cast<Type>(0.25) * s;
			z = (m23 + m32) * invS;

		} else {
			s = static_cast<Type>(2) * Mathf.Sqrt(static_cast<Type>(1) + m33 - m11 - m22);
			invS = static_cast<Type>(1) / s;

			w = (m21 - m12) * invS;
			x = (m13 + m31) * invS;
			y = (m23 + m32) * invS;
			z = static_cast<Type>(0.25) * s;
		}

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::operator -(void) {
		Type lenSq = x * x + y * y + z * z + w * w;

		if (lenSq == static_cast<Type>(0) || lenSq == static_cast<Type>(1)) {
			x = -x;
			y = -y;
			z = -z;
			return *this;
		}

		Type len = Mathf.Sqrt(lenSq),
		     invLen = static_cast<Type>(1) / len;

		x *= -invLen;
		y *= -invLen;
		z *= -invLen;
		w *= invLen;

		return *this;
	}

	template <typename Type> inline Quat<Type> Quat<Type>::Inverse(void) {
		Type lenSq = x * x + y * y + z * z + w * w;

		if (lenSq == static_cast<Type>(0) || lenSq == static_cast<Type>(1)) {
			return Quat<Type>(-x, -y, -z, w);
		}

		Type len = Mathf.Sqrt(lenSq),
		     invLen = static_cast<Type>(1) / len;

		return Quat<Type>(
		           -x * invLen,
		           -y * invLen,
		           -z * invLen,
		           w * invLen
		       );
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::calculateW(void) {

		w = -Mathf.Sqrt(abs(static_cast<Type>(1) - x * x - y * y - z * z));

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::RotateX(Type angle) {
		Type halfAngle = angle * static_cast<Type>(0.5),
		     ax = x,
		     ay = y,
		     az = z,
		     aw = w,
		     s = Mathf.Sin(halfAngle),
		     c = Mathf.Cos(halfAngle);

		x = ax * c + aw * s;
		y = ay * c + az * s;
		z = az * c - ay * s;
		w = aw * c - ax * s;

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::RotateY(Type angle) {
		Type halfAngle = angle * static_cast<Type>(0.5),
		     ax = x,
		     ay = y,
		     az = z,
		     aw = w,
		     s = Mathf.Sin(halfAngle),
		     c = Mathf.Cos(halfAngle);

		x = ax * c - az * s;
		y = ay * c + aw * s;
		z = az * c + ax * s;
		w = aw * c - ay * s;

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::RotateZ(Type angle) {
		Type halfAngle = angle * static_cast<Type>(0.5),
		     ax = x,
		     ay = y,
		     az = z,
		     aw = w,
		     s = Mathf.Sin(halfAngle),
		     c = Mathf.Cos(halfAngle);

		x = ax * c + ay * s;
		y = ay * c - ax * s;
		z = az * c + aw * s;
		w = aw * c - az * s;

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::Rotate(Type x, Type y, Type z) {

		RotateZ(z);
		RotateX(x);
		RotateY(y);

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::LookRotation(const Vec3<Type>& forward, const Vec3<Type>& up) {
		Type fx = forward.x,
		     fy = forward.y,
		     fz = forward.z,
		     ux = up.x,
		     uy = up.y,
		     uz = up.z,

		     ax = uy * fz - uz * fy,
		     ay = uz * fx - ux * fz,
		     az = ux * fy - uy * fx,

		     d = (static_cast<Type>(1) + ux * fx + uy * fy + uz * fz) * static_cast<Type>(2),
		     dsq = d * d,
		     s = static_cast<Type>(1) / dsq;

		x = ax * s;
		y = ay * s;
		z = az * s;
		w = dsq * static_cast<Type>(0.5);

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::FromAxisAngle(const Vec3<Type>& axis, Type angle) {
		Type halfAngle = angle * static_cast<Type>(0.5),
		     s = Mathf.Sin(halfAngle);

		x = axis.x * s;
		y = axis.y * s;
		z = axis.z * s;
		w = Mathf.Cos(halfAngle);

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::FromVec3s(const Vec3<Type>& u, const Vec3<Type>& v) {
		Vec3<Type> a = Vec3<Type>::Cross(u, v);
		Type ux = u.x,
		     uy = u.y,
		     uz = u.z,

		     vx = v.x,
		     vy = v.y,
		     vz = v.z;

		x = a.x;
		y = a.y;
		z = a.z;
		w = Mathf.Sqrt((ux * ux + uy * uy + uz * uz) * (vx * vx + vy * vy + vz * vz)) + (ux * vx + uy * vy + uz * vz);
		Normalize();

		return *this;
	}

	template <typename Type> inline Type Quat<Type>::operator [] (int32 i) const {
		return (&x)[i];
	}

	template <typename Type> inline Type& Quat<Type>::operator [] (int32 i) {
		return (&x)[i];
	}
	
	template <typename Type> inline Quat<Type> Quat<Type>::operator *(const Mat3<Type>& m) {
		Quat<Type> q;
		return (*this * q.FromMatrix(m));
	}
	template <typename Type> inline Quat<Type>& Quat<Type>::operator *=(const Mat3<Type>& m) {
		Quat<Type> q;
		*this *= q.FromMatrix(m);
		
		return *this;
	}
	
	template <typename Type> inline Quat<Type> Quat<Type>::operator *(const Mat4<Type>& m) {
		Quat<Type> q;
		return (*this * q.FromMatrix(m));
	}
	template <typename Type> inline Quat<Type>& Quat<Type>::operator *=(const Mat4<Type>& m) {
		Quat<Type> q;
		*this *= q.FromMatrix(m);
		
		return *this;
	}
	
	template <typename Type> inline Quat<Type> Quat<Type>::operator *(const Mat43<Type>& m) {
		Quat<Type> q;
		return (*this * q.FromMatrix(m));
	}
	template <typename Type> inline Quat<Type>& Quat<Type>::operator *=(const Mat43<Type>& m) {
		Quat<Type> q;
		*this *= q.FromMatrix(m);
		
		return *this;
	}

	template <typename Type> inline Quat<Type> Quat<Type>::operator +(const Quat<Type>& q) {

		return Quat<Type>(x + q.x, y + q.y, z + q.z, w + q.w);
	}

	template <typename Type> inline Quat<Type> Quat<Type>::operator -(const Quat<Type>& q) {

		return Quat<Type>(x - q.x, y - q.y, z - q.z, w - q.w);
	}

	template <typename Type> inline Quat<Type> Quat<Type>::operator *(const Quat<Type>& q) {
		Type ax = x,
		     ay = y,
		     az = z,
		     aw = w,
		     bx = q.x,
		     by = q.y,
		     bz = q.z,
		     bw = q.w;

		return Quat<Type>(
		           ax * bw + aw * bx + ay * bz - az * by,
		           ay * bw + aw * by + az * bx - ax * bz,
		           az * bw + aw * bz + ax * by - ay * bx,
		           aw * bw - ax * bx - ay * by - az * bz
		       );
	}

	template <typename Type> inline Quat<Type> Quat<Type>::operator /(const Quat<Type>& q) {
		Type ax = x,
		     ay = y,
		     az = z,
		     aw = w,
		     bx = -q.x,
		     by = -q.y,
		     bz = -q.z,
		     bw = q.w;

		return Quat<Type>(
		           ax * bw + aw * bx + ay * bz - az * by,
		           ay * bw + aw * by + az * bx - ax * bz,
		           az * bw + aw * bz + ax * by - ay * bx,
		           -(aw * bw - ax * bx - ay * by - az * bz)
		       );
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::operator +=(const Quat<Type>& q) {
		x += q.x;
		y += q.y;
		z += q.z;
		w += q.w;

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::operator -=(const Quat<Type>& q) {
		x -= q.x;
		y -= q.y;
		z -= q.z;
		w -= q.w;

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::operator *=(const Quat<Type>& q) {
		Type ax = x,
		     ay = y,
		     az = z,
		     aw = w,
		     bx = q.x,
		     by = q.y,
		     bz = q.z,
		     bw = q.w;

		x = ax * bw + aw * bx + ay * bz - az * by;
		y = ay * bw + aw * by + az * bx - ax * bz;
		z = az * bw + aw * bz + ax * by - ay * bx;
		w = aw * bw - ax * bx - ay * by - az * bz;

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::operator /=(const Quat<Type>& q) {
		Type ax = x,
		     ay = y,
		     az = z,
		     aw = w,
		     bx = -q.x,
		     by = -q.y,
		     bz = -q.z,
		     bw = q.w;

		x = ax * bw + aw * bx + ay * bz - az * by;
		y = ay * bw + aw * by + az * bx - ax * bz;
		z = az * bw + aw * bz + ax * by - ay * bx;
		w = -(aw * bw - ax * bx - ay * by - az * bz);
	}


	template <typename Type> inline Quat<Type> Quat<Type>::operator +(Type s) {

		return Quat<Type>(x + s, y + s, z + s, w + s);
	}

	template <typename Type> inline Quat<Type> Quat<Type>::operator -(Type s) {

		return Quat<Type>(x - s, y - s, z - s, w - s);
	}

	template <typename Type> inline Quat<Type> Quat<Type>::operator *(Type s) {

		return Quat<Type>(x * s, y * s, z * s, w * s);
	}

	template <typename Type> inline Quat<Type> Quat<Type>::operator /(Type s) {
		Type d = s != static_cast<Type>(0) ? static_cast<Type>(1) / s : static_cast<Type>(0);

		return Quat<Type>(x * d, y * d, z * d, w * d);
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::operator +=(Type s) {
		x += s;
		y += s;
		z += s;
		w += s;

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::operator -=(Type s) {
		x -= s;
		y -= s;
		z -= s;
		w -= s;

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::operator *=(Type s) {
		x *= s;
		y *= s;
		z *= s;
		w *= s;

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::operator /=(Type s) {
		Type d = s != static_cast<Type>(0) ? static_cast<Type>(1) / s : static_cast<Type>(0);

		x *= d;
		y *= d;
		z *= d;
		w *= d;

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::operator =(const Quat<Type>& q) {
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::operator =(const Quat<Type> && q) {
		x = std::move(q.x);
		y = std::move(q.y);
		z = std::move(q.z);
		w = std::move(q.w);

		return *this;
	}

	template <typename Type> inline bool Quat<Type>::operator ==(const Quat<Type>& q) {

		return !(x != q.x || y != q.y || z != q.z || w != q.w);
	}

	template <typename Type> inline bool Quat<Type>::operator !=(const Quat<Type>& q) {

		return x != q.x || y != q.y || z != q.z || w != q.w;
	}

	template <typename Type> inline std::string Quat<Type>::ToString(int32 p) {

		return "Quat(" + Odin::ToString(x, p) + ", " + Odin::ToString(y, p) + ", " + Odin::ToString(z, p) + ", " + Odin::ToString(w, p) + ")";
	}
};

#endif