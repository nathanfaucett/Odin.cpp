#ifndef ODIN_QUAT_CPP
#define ODIN_QUAT_CPP

namespace Odin {

	template <typename Type> inline Quat<Type>::Quat(void) {
		x = 0;
		y = 0;
		z = 0;
		w = 1;
	}

	template <typename Type> inline Quat<Type>::Quat(Type X, Type Y, Type Z) {
		x = X;
		y = Y;
		z = Z;
		w = 1;
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
		w = 1;
	}

	template <typename Type> inline Quat<Type>::Quat(const Vec3<Type>& axis, Type angle) {
		Type halfAngle = angle * 0.5,
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
		x = 0;
		y = 0;
		z = 0;
		w = 0;

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

		return lenSq == 0 ? 0 : sqrtf(lenSq);
	}

	template <typename Type> inline Type Quat<Type>::Normalize(void) {
		Type lenSq = x * x + y * y + z * z + w * w;

		if (lenSq == 0) {
			return 0;
		}

		Type len = sqrtf(lenSq),
		     invLen = 1 / len;

		x *= invLen;
		y *= invLen;
		z *= invLen;
		w *= invLen;

		return len;
	}

	template <typename Type> inline Quat<Type> Quat<Type>::Lerp(const Quat<Type>& q, Type t) {
		x = Mathf.Lerp(x, q.x, t);
		y = Mathf.Lerp(y, q.y, t);
		z = Mathf.Lerp(z, q.z, t);
		w = Mathf.Lerp(w, q.w, t);

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::Slerp(const Quat<Type>& q, Type t) {
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

		if (cosom < 0) {
			cosom *= -1;
			bx *= -1;
			by *= -1;
			bz *= -1;
			bw *= -1;
		}

		if (1 - cosom > Mathf.Epsilon) {
			omega = acosf(cosom);
			sinom = 1 / Mathf.Sin(omega);
			scale0 = Mathf.Sin((1 - t) * omega) * sinom;
			scale1 = Mathf.Sin(t * omega) * sinom;

		} else {
			scale0 = 1 - t;
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

		if (trace > 0) {
			s = 0.5 / sqrt(trace + 1);

			w = 0.25 / s;
			x = (m32 - m23) * s;
			y = (m13 - m31) * s;
			z = (m21 - m12) * s;

		} else if (m11 > m22 && m11 > m33) {
			s = 2 * sqrt(1 + m11 - m22 - m33);
			invS = 1 / s;

			w = (m32 - m23) * invS;
			x = 0.25 * s;
			y = (m12 + m21) * invS;
			z = (m13 + m31) * invS;

		} else if (m22 > m33) {
			s = 2 * sqrt(1 + m22 - m11 - m33);
			invS = 1 / s;

			w = (m13 - m31) * invS;
			x = (m12 + m21) * invS;
			y = 0.25 * s;
			z = (m23 + m32) * invS;

		} else {
			s = 2 * sqrt(1 + m33 - m11 - m22);
			invS = 1 / s;

			w = (m21 - m12) * invS;
			x = (m13 + m31) * invS;
			y = (m23 + m32) * invS;
			z = 0.25 * s;
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

		if (trace > 0) {
			s = 0.5 / sqrt(trace + 1);

			w = 0.25 / s;
			x = (m32 - m23) * s;
			y = (m13 - m31) * s;
			z = (m21 - m12) * s;

		} else if (m11 > m22 && m11 > m33) {
			s = 2 * sqrt(1 + m11 - m22 - m33);
			invS = 1 / s;

			w = (m32 - m23) * invS;
			x = 0.25 * s;
			y = (m12 + m21) * invS;
			z = (m13 + m31) * invS;

		} else if (m22 > m33) {
			s = 2 * sqrt(1 + m22 - m11 - m33);
			invS = 1 / s;

			w = (m13 - m31) * invS;
			x = (m12 + m21) * invS;
			y = 0.25 * s;
			z = (m23 + m32) * invS;

		} else {
			s = 2 * sqrt(1 + m33 - m11 - m22);
			invS = 1 / s;

			w = (m21 - m12) * invS;
			x = (m13 + m31) * invS;
			y = (m23 + m32) * invS;
			z = 0.25 * s;
		}

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::operator -() {
		Type lenSq = x * x + y * y + z * z + w * w;

		if (lenSq == 0 || lenSq == 1) {
			x = -x;
			y = -y;
			z = -z;
			return *this;
		}

		Type len = sqrtf(lenSq),
		     invLen = 1 / len;

		x *= -invLen;
		y *= -invLen;
		z *= -invLen;
		w *= invLen;

		return *this;
	}

	template <typename Type> inline Quat<Type> Quat<Type>::Inverse(void) {
		Type lenSq = x * x + y * y + z * z + w * w;

		if (lenSq == 0 || lenSq == 1) {
			return Quat(-x, -y, -z, w);
		}

		Type len = sqrtf(lenSq),
		     invLen = 1 / len;

		return Quat(
		           -x * invLen,
		           -y * invLen,
		           -z * invLen,
		           w * invLen
		       );
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::calculateW(void) {

		w = -sqrtf(abs(1 - x * x - y * y - z * z));

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::RotateX(Type angle) {
		Type halfAngle = angle * 0.5,
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
		Type halfAngle = angle * 0.5,
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
		Type halfAngle = angle * 0.5,
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

		     d = (1 + ux * fx + uy * fy + uz * fz) * 2,
		     dsq = d * d,
		     s = 1 / dsq;

		x = ax * s;
		y = ay * s;
		z = az * s;
		w = dsq * 0.5;

		return *this;
	}

	template <typename Type> inline Quat<Type>& Quat<Type>::FromAxisAngle(const Vec3<Type>& axis, Type angle) {
		Type halfAngle = angle * 0.5,
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
		w = sqrtf((ux * ux + uy * uy + uz * uz) * (vx * vx + vy * vy + vz * vz)) + (ux * vx + uy * vy + uz * vz);
		Normalize();

		return *this;
	}

	template <typename Type> inline Type Quat<Type>::operator [] (int32 i) const {
		return (&x)[i];
	}

	template <typename Type> inline Type& Quat<Type>::operator [] (int32 i) {
		return (&x)[i];
	}

	template <typename Type> inline Quat<Type> Quat<Type>::operator +(const Quat<Type>& q) {

		return Quat(x + q.x, y + q.y, z + q.z, w + q.w);
	}

	template <typename Type> inline Quat<Type> Quat<Type>::operator -(const Quat<Type>& q) {

		return Quat(x - q.x, y - q.y, z - q.z, w - q.w);
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

		return Quat(
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

		return Quat(
		           ax * bw + aw * bx + ay * bz - az * by,
		           ay * bw + aw * by + az * bx - ax * bz,
		           az * bw + aw * bz + ax * by - ay * bx,
		           -(aw * bw - ax * bx - ay * by - az * bz)
		       );
	}

	template <typename Type> inline void Quat<Type>::operator +=(const Quat<Type>& q) {
		x += q.x;
		y += q.y;
		z += q.z;
		w += q.w;
	}

	template <typename Type> inline void Quat<Type>::operator -=(const Quat<Type>& q) {
		x -= q.x;
		y -= q.y;
		z -= q.z;
		w -= q.w;
	}

	template <typename Type> inline void Quat<Type>::operator *=(const Quat<Type>& q) {
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
	}

	template <typename Type> inline void Quat<Type>::operator /=(const Quat<Type>& q) {
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

		return Quat(x + s, y + s, z + s, w + s);
	}

	template <typename Type> inline Quat<Type> Quat<Type>::operator -(Type s) {

		return Quat(x - s, y - s, z - s, w - s);
	}

	template <typename Type> inline Quat<Type> Quat<Type>::operator *(Type s) {

		return Quat(x * s, y * s, z * s, w * s);
	}

	template <typename Type> inline Quat<Type> Quat<Type>::operator /(Type s) {
		Type d = s != 0 ? 1 / s : 0;

		return Quat(x * d, y * d, z * d, w * d);
	}

	template <typename Type> inline void Quat<Type>::operator +=(Type s) {
		x += s;
		y += s;
		z += s;
		w += s;
	}

	template <typename Type> inline void Quat<Type>::operator -=(Type s) {
		x -= s;
		y -= s;
		z -= s;
		w -= s;
	}

	template <typename Type> inline void Quat<Type>::operator *=(Type s) {
		x *= s;
		y *= s;
		z *= s;
		w *= s;
	}

	template <typename Type> inline void Quat<Type>::operator /=(Type s) {
		Type d = s != 0 ? 1 / s : 0;

		x *= d;
		y *= d;
		z *= d;
		w *= d;
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

		return "Quat(" + Util.ToString(x, p) + ", " + Util.ToString(y, p) + ", " + Util.ToString(z, p) + ", " + Util.ToString(w, p) + ")";
	}
};

#endif