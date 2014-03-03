#ifndef _ODIN_QUAT_CPP
#define _ODIN_QUAT_CPP

namespace Odin {

	inline Quat::Quat(void) {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 1.0f;
	}

	inline Quat::Quat(float32 X, float32 Y, float32 Z) {
		x = X;
		y = Y;
		z = Z;
		w = 1.0f;
	}

	inline Quat::Quat(float32 X, float32 Y, float32 Z, float32 W) {
		x = X;
		y = Y;
		z = Z;
		w = W;
	}

	inline Quat::Quat(const Vec3& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = 1.0f;
	}

	inline Quat::Quat(const Vec3& axis, float32 angle) {
		float32 halfAngle = angle * 0.5f,
		        s = sinf(halfAngle);

		x = axis.x * s;
		y = axis.y * s;
		z = axis.z * s;
		w = cosf(halfAngle);
	}

	inline Quat::Quat(const Vec4& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}

	inline Quat::Quat(const Quat& q) {
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;
	}

	inline Quat::Quat(const Quat&& q) {
		x = std::move(q.x);
		y = std::move(q.y);
		z = std::move(q.z);
		w = std::move(q.w);
	}

	inline Quat::~Quat(void) {}

	inline Quat& Quat::Set(float32 X, float32 Y, float32 Z) {
		x = X;
		y = Y;
		z = Z;

		return *this;
	}

	inline Quat& Quat::Set(float32 X, float32 Y, float32 Z, float32 W) {
		x = X;
		y = Y;
		z = Z;
		w = W;

		return *this;
	}

	inline Quat& Quat::Zero(void) {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;

		return *this;
	}

	inline float32 Quat::Dot(const Quat q) {

		return x * q.x + y * q.y + z * q.z + w * q.w;
	}

	inline float32 Quat::LengthSq(void) {

		return x * x + y * y + z * z + w * w;
	}

	inline float32 Quat::Length(void) {
		float32 lenSq = x * x + y * y + z * z + w * w;

		return lenSq == 0.0f ? 0.0f : sqrtf(lenSq);
	}

	inline float32 Quat::Normalize(void) {
		float32 lenSq = x * x + y * y + z * z + w * w;

		if (lenSq == 0.0f) {
			return 0.0f;
		}

		float32 len = sqrtf(lenSq),
		        invLen = 1.0f / len;

		x *= invLen;
		y *= invLen;
		z *= invLen;
		w *= invLen;

		return len;
	}

	inline Quat Quat::Lerp(const Quat& q, float32 t) {
		x = Mathf.Lerp(x, q.x, t);
		y = Mathf.Lerp(y, q.y, t);
		z = Mathf.Lerp(z, q.z, t);
		w = Mathf.Lerp(w, q.w, t);

		return *this;
	}

	inline Quat& Quat::Slerp(const Quat& q, float32 t) {
		float32 ax = x,
		        ay = y,
		        az = z,
		        aw = w,
		        bx = q.x,
		        by = q.y,
		        bz = q.z,
		        bw = q.w,

		        omega, sinom, scale0, scale1,
		        cosom = ax * bx + ay * by + az * bz + aw * bw;

		if (cosom < 0.0f) {
			cosom *= -1.0f;
			bx *= -1.0f;
			by *= -1.0f;
			bz *= -1.0f;
			bw *= -1.0f;
		}

		if (1.0f - cosom > Mathf.Epsilon) {
			omega = acosf(cosom);
			sinom = 1.0f / sinf(omega);
			scale0 = sinf((1.0f - t) * omega) * sinom;
			scale1 = sinf(t * omega) * sinom;

		} else {
			scale0 = 1.0f - t;
			scale1 = t;
		}

		x = scale0 * ax + scale1 * bx;
		y = scale0 * ay + scale1 * by;
		z = scale0 * az + scale1 * bz;
		w = scale0 * aw + scale1 * bw;

		return *this;
	}

	inline Quat& Quat::FromMatrix(const Mat3& m)  {
		float32 m11 = m[0],
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

		if (trace > 0.0f) {
			s = 0.5f / sqrt(trace + 1.0f);

			w = 0.25f / s;
			x = (m32 - m23) * s;
			y = (m13 - m31) * s;
			z = (m21 - m12) * s;

		} else if (m11 > m22 && m11 > m33) {
			s = 2.0f * sqrt(1.0f + m11 - m22 - m33);
			invS = 1.0f / s;

			w = (m32 - m23) * invS;
			x = 0.25f * s;
			y = (m12 + m21) * invS;
			z = (m13 + m31) * invS;

		} else if (m22 > m33) {
			s = 2.0f * sqrt(1.0f + m22 - m11 - m33);
			invS = 1.0f / s;

			w = (m13 - m31) * invS;
			x = (m12 + m21) * invS;
			y = 0.25f * s;
			z = (m23 + m32) * invS;

		} else {
			s = 2.0f * sqrt(1.0f + m33 - m11 - m22);
			invS = 1.0f / s;

			w = (m21 - m12) * invS;
			x = (m13 + m31) * invS;
			y = (m23 + m32) * invS;
			z = 0.25f * s;
		}

		return *this;
	}

	inline Quat& Quat::FromMatrix(const Mat4& m) {
		float32 m11 = m[0],
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

		if (trace > 0.0f) {
			s = 0.5f / sqrt(trace + 1.0f);

			w = 0.25f / s;
			x = (m32 - m23) * s;
			y = (m13 - m31) * s;
			z = (m21 - m12) * s;

		} else if (m11 > m22 && m11 > m33) {
			s = 2.0f * sqrt(1.0f + m11 - m22 - m33);
			invS = 1.0f / s;

			w = (m32 - m23) * invS;
			x = 0.25f * s;
			y = (m12 + m21) * invS;
			z = (m13 + m31) * invS;

		} else if (m22 > m33) {
			s = 2.0f * sqrt(1.0f + m22 - m11 - m33);
			invS = 1.0f / s;

			w = (m13 - m31) * invS;
			x = (m12 + m21) * invS;
			y = 0.25f * s;
			z = (m23 + m32) * invS;

		} else {
			s = 2.0f * sqrt(1.0f + m33 - m11 - m22);
			invS = 1.0f / s;

			w = (m21 - m12) * invS;
			x = (m13 + m31) * invS;
			y = (m23 + m32) * invS;
			z = 0.25f * s;
		}

		return *this;
	}

	inline Quat& Quat::operator -() {
		float32 lenSq = x * x + y * y + z * z + w * w;

		if (lenSq == 0.0f || lenSq == 1.0f) {
			x = -x;
			y = -y;
			z = -z;
			return *this;
		}

		float32 len = sqrtf(lenSq),
		        invLen = 1.0f / len;

		x *= -invLen;
		y *= -invLen;
		z *= -invLen;
		w *= invLen;

		return *this;
	}

	inline Quat Quat::Inverse(void) {
		float32 lenSq = x * x + y * y + z * z + w * w;

		if (lenSq == 0.0f || lenSq == 1.0f) {
			return Quat(-x, -y, -z, w);
		}

		float32 len = sqrtf(lenSq),
		        invLen = 1.0f / len;

		return Quat(
		           -x * invLen,
		           -y * invLen,
		           -z * invLen,
		           w * invLen
		       );
	}

	inline Quat& Quat::calculateW(void) {

		w = -sqrtf(abs(1.0f - x * x - y * y - z * z));

		return *this;
	}

	inline Quat& Quat::RotateX(float32 angle) {
		float32 halfAngle = angle * 0.5f,
		        ax = x,
		        ay = y,
		        az = z,
		        aw = w,
		        s = sinf(halfAngle),
		        c = cosf(halfAngle);

		x = ax * c + aw * s;
		y = ay * c + az * s;
		z = az * c - ay * s;
		w = aw * c - ax * s;

		return *this;
	}

	inline Quat& Quat::RotateY(float32 angle) {
		float32 halfAngle = angle * 0.5f,
		        ax = x,
		        ay = y,
		        az = z,
		        aw = w,
		        s = sinf(halfAngle),
		        c = cosf(halfAngle);

		x = ax * c - az * s;
		y = ay * c + aw * s;
		z = az * c + ax * s;
		w = aw * c - ay * s;

		return *this;
	}

	inline Quat& Quat::RotateZ(float32 angle) {
		float32 halfAngle = angle * 0.5f,
		        ax = x,
		        ay = y,
		        az = z,
		        aw = w,
		        s = sinf(halfAngle),
		        c = cosf(halfAngle);

		x = ax * c + ay * s;
		y = ay * c - ax * s;
		z = az * c + aw * s;
		w = aw * c - az * s;

		return *this;
	}

	inline Quat& Quat::Rotate(float32 x, float32 y, float32 z) {

		RotateZ(z);
		RotateX(x);
		RotateY(y);

		return *this;
	}

	inline Quat& Quat::LookRotation(const Vec3& forward, const Vec3& up) {
		float32 fx = forward.x,
		        fy = forward.y,
		        fz = forward.z,
		        ux = up.x,
		        uy = up.y,
		        uz = up.z,

		        ax = uy * fz - uz * fy,
		        ay = uz * fx - ux * fz,
		        az = ux * fy - uy * fx,

		        d = (1.0f + ux * fx + uy * fy + uz * fz) * 2.0f,
		        dsq = d * d,
		        s = 1.0f / dsq;

		x = ax * s;
		y = ay * s;
		z = az * s;
		w = dsq * 0.5f;

		return *this;
	}

	inline Quat& Quat::FromAxisAngle(const Vec3& axis, float32 angle) {
		float32 halfAngle = angle * 0.5f,
		        s = sinf(halfAngle);

		x = axis.x * s;
		y = axis.y * s;
		z = axis.z * s;
		w = cosf(halfAngle);

		return *this;
	}

	inline Quat& Quat::FromVec3s(const Vec3& u, const Vec3& v) {
		Vec3 a = Vec3::Cross(u, v);
		float32 ux = u.x,
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

	inline float32 Quat::operator [] (int32 i) const {
		return (&x)[i];
	}

	inline float32& Quat::operator [] (int32 i) {
		return (&x)[i];
	}

	inline Quat Quat::operator +(const Quat& q) {

		return Quat(x + q.x, y + q.y, z + q.z, w + q.w);
	}

	inline Quat Quat::operator -(const Quat& q) {

		return Quat(x - q.x, y - q.y, z - q.z, w - q.w);
	}

	inline Quat Quat::operator *(const Quat& q) {
		float32 ax = x,
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

	inline Quat Quat::operator /(const Quat& q) {
		float32 ax = x,
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

	inline void Quat::operator +=(const Quat& q) {
		x += q.x;
		y += q.y;
		z += q.z;
		w += q.w;
	}

	inline void Quat::operator -=(const Quat& q) {
		x -= q.x;
		y -= q.y;
		z -= q.z;
		w -= q.w;
	}

	inline void Quat::operator *=(const Quat& q) {
		float32 ax = x,
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

	inline void Quat::operator /=(const Quat& q) {
		float32 ax = x,
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


	inline Quat Quat::operator +(float32 s) {

		return Quat(x + s, y + s, z + s, w + s);
	}

	inline Quat Quat::operator -(float32 s) {

		return Quat(x - s, y - s, z - s, w - s);
	}

	inline Quat Quat::operator *(float32 s) {

		return Quat(x * s, y * s, z * s, w * s);
	}

	inline Quat Quat::operator /(float32 s) {
		float32 d = s != 0.0f ? 1.0f / s : 0.0f;

		return Quat(x * d, y * d, z * d, w * d);
	}

	inline void Quat::operator +=(float32 s) {
		x += s;
		y += s;
		z += s;
		w += s;
	}

	inline void Quat::operator -=(float32 s) {
		x -= s;
		y -= s;
		z -= s;
		w -= s;
	}

	inline void Quat::operator *=(float32 s) {
		x *= s;
		y *= s;
		z *= s;
		w *= s;
	}

	inline void Quat::operator /=(float32 s) {
		float32 d = s != 0.0f ? 1.0f / s : 0.0f;

		x *= d;
		y *= d;
		z *= d;
		w *= d;
	}

	inline Quat& Quat::operator =(const Quat& q) {
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;

		return *this;
	}

	inline Quat& Quat::operator =(const Quat && q) {
		x = std::move(q.x);
		y = std::move(q.y);
		z = std::move(q.z);
		w = std::move(q.w);

		return *this;
	}

	inline bool Quat::operator ==(const Quat& q) {

		return !(x != q.x || y != q.y || z != q.z || w != q.w);
	}

	inline bool Quat::operator !=(const Quat& q) {

		return x != q.x || y != q.y || z != q.z || w != q.w;
	}

	inline std::string Quat::ToString(int32 p) {

		return "Quat(" + util.ToString(x, p) + ", " + util.ToString(y, p) + ", " + util.ToString(z, p) + ", " + util.ToString(w, p) + ")";
	}
};

#endif