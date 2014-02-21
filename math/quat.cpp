#ifndef ODIN_QUAT_CPP
#define ODIN_QUAT_CPP

namespace Odin {

	inline Quat::Quat(void) {
		x = 0;
		y = 0;
		z = 0;
		w = 1;
	}

	inline Quat::Quat(const float X, const float Y, const float Z) {
		x = X;
		y = Y;
		z = Z;
		w = 1;
	}

	inline Quat::Quat(const float X, const float Y, const float Z, const float W) {
		x = X;
		y = Y;
		z = Z;
		w = W;
	}

	inline Quat::Quat(const Vec3& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = 1;
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

	inline Quat::~Quat(void) {}

	inline Quat& Quat::Set(const float X, const float Y, const float Z) {
		x = X;
		y = Y;
		z = Z;

		return *this;
	}

	inline Quat& Quat::Set(const float X, const float Y, const float Z, const float W) {
		x = X;
		y = Y;
		z = Z;
		w = W;

		return *this;
	}

	inline Quat& Quat::Zero() {
		x = 0;
		y = 0;
		z = 0;
		w = 0;

		return *this;
	}

	inline float Quat::Dot(const Quat q) {

		return x * q.x + y * q.y + z * q.z + w * q.w;
	}

	inline float Quat::LengthSq() {

		return x * x + y * y + z * z + w * w;
	}

	inline float Quat::Length() {
		float lenSq = x * x + y * y + z * z + w * w;

		return lenSq == 0 ? 0 : std::sqrt(lenSq);
	}

	inline float Quat::Normalize() {
		float lenSq = x * x + y * y + z * z + w * w;

		if (lenSq == 0) {
			return 0;
		}

		float len = std::sqrt(lenSq),
			  invLen = 1 / len;

		x *= invLen;
		y *= invLen;
		z *= invLen;
		w *= invLen;

		return len;
	}

	inline Quat Quat::Lerp(const Quat& q, const float t) {
		x = Mathf.Lerp(x, q.x, t);
		y = Mathf.Lerp(y, q.y, t);
		z = Mathf.Lerp(z, q.z, t);
		w = Mathf.Lerp(w, q.w, t);

		return *this;
	}

	inline Quat& Quat::Slerp(const Quat& q, const float t) {
		float ax = x,
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
			omega = std::acos(cosom);
			sinom = 1 / std::sin(omega);
			scale0 = std::sin((1 - t) * omega) * sinom;
			scale1 = std::sin(t * omega) * sinom;

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

	inline Quat& Quat::FromMatrix(const Mat3& m)  {
		float m11 = m.mat[0],
			  m12 = m.mat[3],
			  m13 = m.mat[6],
			  m21 = m.mat[1],
			  m22 = m.mat[4],
			  m23 = m.mat[7],
			  m31 = m.mat[2],
			  m32 = m.mat[5],
			  m33 = m.mat[8],
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

	inline Quat& Quat::FromMatrix(const Mat4& m) {
		float m11 = m.mat[0],
			  m12 = m.mat[4],
			  m13 = m.mat[8],
			  m21 = m.mat[1],
			  m22 = m.mat[5],
			  m23 = m.mat[9],
			  m31 = m.mat[2],
			  m32 = m.mat[6],
			  m33 = m.mat[10],
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

	inline Quat& Quat::operator -() {
		float lenSq = x * x + y * y + z * z + w * w;

		if (lenSq == 0 || lenSq == 1) {
			x = -x;
			y = -y;
			z = -z;
			return *this;
		}

		float len = std::sqrt(lenSq),
			  invLen = 1 / len;

		x *= -invLen;
		y *= -invLen;
		z *= -invLen;
		w *= invLen;

		return *this;
	}

	inline Quat Quat::Inverse() {
		float lenSq = x * x + y * y + z * z + w * w;

		if (lenSq == 0 || lenSq == 1) {
			return Quat(-x, -y, -z, w);
		}

		float len = std::sqrt(lenSq),
			  invLen = 1 / len;

		return Quat(
				   -x * invLen,
				   -y * invLen,
				   -z * invLen,
				   w * invLen
			   );
	}

	inline Quat& Quat::calculateW() {

		w = -std::sqrt(abs(1 - x * x - y * y - z * z));

		return *this;
	}

	inline Quat& Quat::RotateX(const float angle) {
		float halfAngle = angle * 0.5,
			  ax = x,
			  ay = y,
			  az = z,
			  aw = w,
			  s = std::sin(halfAngle),
			  c = std::cos(halfAngle);

		x = ax * c + aw * s;
		y = ay * c + az * s;
		z = az * c - ay * s;
		w = aw * c - ax * s;

		return *this;
	}

	inline Quat& Quat::RotateY(const float angle) {
		float halfAngle = angle * 0.5,
			  ax = x,
			  ay = y,
			  az = z,
			  aw = w,
			  s = std::sin(halfAngle),
			  c = std::cos(halfAngle);

		x = ax * c - az * s;
		y = ay * c + aw * s;
		z = az * c + ax * s;
		w = aw * c - ay * s;

		return *this;
	}

	inline Quat& Quat::RotateZ(const float angle) {
		float halfAngle = angle * 0.5,
			  ax = x,
			  ay = y,
			  az = z,
			  aw = w,
			  s = std::sin(halfAngle),
			  c = std::cos(halfAngle);

		x = ax * c + ay * s;
		y = ay * c - ax * s;
		z = az * c + aw * s;
		w = aw * c - az * s;

		return *this;
	}

	inline Quat& Quat::Rotate(const float x, const float y, const float z) {

		RotateZ(z);
		RotateX(x);
		RotateY(y);

		return *this;
	}

	inline Quat& Quat::LookRotation(const Vec3& forward, const Vec3& up) {
		float fx = forward.x,
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

	inline Quat& Quat::fromAxisAngle(const Vec3& axis, const float angle) {
		float halfAngle = angle * 0.5,
			  s = std::sin(halfAngle);

		x = axis.x * s;
		y = axis.y * s;
		z = axis.z * s;
		w = cos(halfAngle);

		return *this;
	}

	inline Quat& Quat::fromVec3s(const Vec3& u, const Vec3& v) {
		Vec3 a = Vec3::Cross(u, v);
		float ux = u.x,
			  uy = u.y,
			  uz = u.z,

			  vx = v.x,
			  vy = v.y,
			  vz = v.z,

			  x = a.x;
		y = a.y;
		z = a.z;
		w = std::sqrt((ux * ux + uy * uy + uz * uz) * (vx * vx + vy * vy + vz * vz)) + (ux * vx + uy * vy + uz * vz);
		Normalize();

		return *this;
	}

	inline float Quat::operator [] (int i) const {
		return (&x)[i];
	}

	inline float& Quat::operator [] (int i) {
		return (&x)[i];
	}

	inline Quat Quat::operator +(const Quat& q) {

		return Quat(x + q.x, y + q.y, z + q.z, w + q.w);
	}

	inline Quat Quat::operator -(const Quat& q) {

		return Quat(x - q.x, y - q.y, z - q.z, w - q.w);
	}

	inline Quat Quat::operator *(const Quat& q) {
		float ax = x,
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
		float ax = x,
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
		float ax = x,
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
		float ax = x,
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


	inline Quat Quat::operator +(const float s) {

		return Quat(x + s, y + s, z + s, w + s);
	}

	inline Quat Quat::operator -(const float s) {

		return Quat(x - s, y - s, z - s, w - s);
	}

	inline Quat Quat::operator *(const float s) {

		return Quat(x * s, y * s, z * s, w * s);
	}

	inline Quat Quat::operator /(const float s) {
		float d = s != 0 ? 1 / s : 0;

		return Quat(x * d, y * d, z * d, w * d);
	}

	inline void Quat::operator +=(const float s) {
		x += s;
		y += s;
		z += s;
		w += s;
	}

	inline void Quat::operator -=(const float s) {
		x -= s;
		y -= s;
		z -= s;
		w -= s;
	}

	inline void Quat::operator *=(const float s) {
		x *= s;
		y *= s;
		z *= s;
		w *= s;
	}

	inline void Quat::operator /=(const float s) {
		float d = s != 0 ? 1 / s : 0;

		x *= d;
		y *= d;
		z *= d;
		w *= d;
	}

	inline void Quat::operator =(const Quat& q) {
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;
	}

	inline bool Quat::operator ==(const Quat& q) {

		return !(x != q.x || y != q.y || z != q.z || w != q.w);
	}

	inline bool Quat::operator !=(const Quat& q) {

		return x != q.x || y != q.y || z != q.z || w != q.w;
	}

	inline std::string Quat::ToString(int p) {

		return "Quat(" + util.ToString(x, p) + ", " + util.ToString(y, p) + ", " + util.ToString(z, p) + ", " + util.ToString(w, p) + ")";
	}
};

#endif