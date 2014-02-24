#ifndef ODIN_MAT4_CPP
#define ODIN_MAT4_CPP

namespace Odin {

	inline Mat4::Mat4(void) {
		mat[0] = 1.0f;
		mat[4] = 0.0f;
		mat[8] = 0.0f;
		mat[12] = 0.0f;
		mat[1] = 0.0f;
		mat[5] = 1.0f;
		mat[9] = 0.0f;
		mat[13] = 0.0f;
		mat[2] = 0.0f;
		mat[6] = 0.0f;
		mat[10] = 1.0f;
		mat[14] = 0.0f;
		mat[3] = 0.0f;
		mat[7] = 0.0f;
		mat[11] = 0.0f;
		mat[15] = 1.0f;
	}

	inline Mat4::Mat4(
	    const float m11, const float m21, const float m31, const float m41,
	    const float m12, const float m22, const float m32, const float m42,
	    const float m13, const float m23, const float m33, const float m43,
	    const float m14, const float m24, const float m34, const float m44
	) {
		mat[0] = m11;
		mat[4] = m21;
		mat[8] = m31;
		mat[12] = m41;
		mat[1] = m12;
		mat[5] = m22;
		mat[9] = m32;
		mat[13] = m42;
		mat[2] = m13;
		mat[6] = m23;
		mat[10] = m33;
		mat[14] = m43;
		mat[3] = m14;
		mat[7] = m24;
		mat[11] = m34;
		mat[15] = m44;
	}

	inline Mat4::Mat4(const Mat4& m) {
		mat[0] = m.mat[0];
		mat[4] = m.mat[4];
		mat[8] = m.mat[8];
		mat[12] = m.mat[12];
		mat[1] = m.mat[1];
		mat[5] = m.mat[5];
		mat[9] = m.mat[9];
		mat[13] = m.mat[13];
		mat[2] = m.mat[2];
		mat[6] = m.mat[6];
		mat[10] = m.mat[10];
		mat[14] = m.mat[14];
		mat[3] = m.mat[3];
		mat[7] = m.mat[7];
		mat[11] = m.mat[11];
		mat[15] = m.mat[15];
	}

	inline Mat4::Mat4(const Mat4&& m) {
		mat[0] = std::move(m.mat[0]);
		mat[4] = std::move(m.mat[4]);
		mat[8] = std::move(m.mat[8]);
		mat[12] = std::move(m.mat[12]);
		mat[1] = std::move(m.mat[1]);
		mat[5] = std::move(m.mat[5]);
		mat[9] = std::move(m.mat[9]);
		mat[13] = std::move(m.mat[13]);
		mat[2] = std::move(m.mat[2]);
		mat[6] = std::move(m.mat[6]);
		mat[10] = std::move(m.mat[10]);
		mat[14] = std::move(m.mat[14]);
		mat[3] = std::move(m.mat[3]);
		mat[7] = std::move(m.mat[7]);
		mat[11] = std::move(m.mat[11]);
		mat[15] = std::move(m.mat[15]);
	}

	inline Mat4::~Mat4(void) {}

	inline Mat4& Mat4::Identity(void) {
		mat[0] = 1.0f;
		mat[4] = 0.0f;
		mat[8] = 0.0f;
		mat[12] = 0.0f;
		mat[1] = 0.0f;
		mat[5] = 1.0f;
		mat[9] = 0.0f;
		mat[13] = 0.0f;
		mat[2] = 0.0f;
		mat[6] = 0.0f;
		mat[10] = 1.0f;
		mat[14] = 0.0f;
		mat[3] = 0.0f;
		mat[7] = 0.0f;
		mat[11] = 0.0f;
		mat[15] = 1.0f;

		return *this;
	}

	inline Mat4& Mat4::SetTrace(const float x, const float y, const float z, const float w) {
		mat[0] = x;
		mat[5] = y;
		mat[10] = z;
		mat[15] = w;

		return *this;
	}

	inline Mat4& Mat4::operator -() {
		float m11 = mat[0], m12 = mat[4], m13 = mat[8], m14 = mat[12],
		      m21 = mat[1], m22 = mat[5], m23 = mat[9], m24 = mat[13],
		      m31 = mat[2], m32 = mat[6], m33 = mat[10], m34 = mat[14],
		      m41 = mat[3], m42 = mat[7], m43 = mat[11], m44 = mat[15],

		      me0 = m23 * m34 * m42 - m24 * m33 * m42 + m24 * m32 * m43 - m22 * m34 * m43 - m23 * m32 * m44 + m22 * m33 * m44,
		      me4 = m14 * m33 * m42 - m13 * m34 * m42 - m14 * m32 * m43 + m12 * m34 * m43 + m13 * m32 * m44 - m12 * m33 * m44,
		      me8 = m13 * m24 * m42 - m14 * m23 * m42 + m14 * m22 * m43 - m12 * m24 * m43 - m13 * m22 * m44 + m12 * m23 * m44,
		      me12 = m14 * m23 * m32 - m13 * m24 * m32 - m14 * m22 * m33 + m12 * m24 * m33 + m13 * m22 * m34 - m12 * m23 * m34,

		      det = m11 * me0 + m21 * me4 + m31 * me8 + m41 * me12;

		if (det == 0.0f) {
			return Identity();
		}

		mat[0] = me0 * det;
		mat[4] = me4 * det;
		mat[8] = me8 * det;
		mat[12] = me12 * det;
		mat[1] = (m24 * m33 * m41 - m23 * m34 * m41 - m24 * m31 * m43 + m21 * m34 * m43 + m23 * m31 * m44 - m21 * m33 * m44) * det;
		mat[5] = (m13 * m34 * m41 - m14 * m33 * m41 + m14 * m31 * m43 - m11 * m34 * m43 - m13 * m31 * m44 + m11 * m33 * m44) * det;
		mat[9] = (m14 * m23 * m41 - m13 * m24 * m41 - m14 * m21 * m43 + m11 * m24 * m43 + m13 * m21 * m44 - m11 * m23 * m44) * det;
		mat[13] = (m13 * m24 * m31 - m14 * m23 * m31 + m14 * m21 * m33 - m11 * m24 * m33 - m13 * m21 * m34 + m11 * m23 * m34) * det;
		mat[2] = (m22 * m34 * m41 - m24 * m32 * m41 + m24 * m31 * m42 - m21 * m34 * m42 - m22 * m31 * m44 + m21 * m32 * m44) * det;
		mat[6] = (m14 * m32 * m41 - m12 * m34 * m41 - m14 * m31 * m42 + m11 * m34 * m42 + m12 * m31 * m44 - m11 * m32 * m44) * det;
		mat[10] = (m12 * m24 * m41 - m14 * m22 * m41 + m14 * m21 * m42 - m11 * m24 * m42 - m12 * m21 * m44 + m11 * m22 * m44) * det;
		mat[14] = (m14 * m22 * m31 - m12 * m24 * m31 - m14 * m21 * m32 + m11 * m24 * m32 + m12 * m21 * m34 - m11 * m22 * m34) * det;
		mat[3] = (m23 * m32 * m41 - m22 * m33 * m41 - m23 * m31 * m42 + m21 * m33 * m42 + m22 * m31 * m43 - m21 * m32 * m43) * det;
		mat[7] = (m12 * m33 * m41 - m13 * m32 * m41 + m13 * m31 * m42 - m11 * m33 * m42 - m12 * m31 * m43 + m11 * m32 * m43) * det;
		mat[11] = (m13 * m22 * m41 - m12 * m23 * m41 - m13 * m21 * m42 + m11 * m23 * m42 + m12 * m21 * m43 - m11 * m22 * m43) * det;
		mat[15] = (m12 * m23 * m31 - m13 * m22 * m31 + m13 * m21 * m32 - m11 * m23 * m32 - m12 * m21 * m33 + m11 * m22 * m33) * det;

		return *this;
	}

	inline Mat4& Mat4::Inverse(void) {
		float m11 = mat[0], m12 = mat[4], m13 = mat[8], m14 = mat[12],
		      m21 = mat[1], m22 = mat[5], m23 = mat[9], m24 = mat[13],
		      m31 = mat[2], m32 = mat[6], m33 = mat[10], m34 = mat[14],
		      m41 = mat[3], m42 = mat[7], m43 = mat[11], m44 = mat[15],

		      me0 = m23 * m34 * m42 - m24 * m33 * m42 + m24 * m32 * m43 - m22 * m34 * m43 - m23 * m32 * m44 + m22 * m33 * m44,
		      me4 = m14 * m33 * m42 - m13 * m34 * m42 - m14 * m32 * m43 + m12 * m34 * m43 + m13 * m32 * m44 - m12 * m33 * m44,
		      me8 = m13 * m24 * m42 - m14 * m23 * m42 + m14 * m22 * m43 - m12 * m24 * m43 - m13 * m22 * m44 + m12 * m23 * m44,
		      me12 = m14 * m23 * m32 - m13 * m24 * m32 - m14 * m22 * m33 + m12 * m24 * m33 + m13 * m22 * m34 - m12 * m23 * m34,

		      det = m11 * me0 + m21 * me4 + m31 * me8 + m41 * me12;

		if (det == 0.0f) {
			return Identity();
		}

		mat[0] = me0 * det;
		mat[4] = me4 * det;
		mat[8] = me8 * det;
		mat[12] = me12 * det;
		mat[1] = (m24 * m33 * m41 - m23 * m34 * m41 - m24 * m31 * m43 + m21 * m34 * m43 + m23 * m31 * m44 - m21 * m33 * m44) * det;
		mat[5] = (m13 * m34 * m41 - m14 * m33 * m41 + m14 * m31 * m43 - m11 * m34 * m43 - m13 * m31 * m44 + m11 * m33 * m44) * det;
		mat[9] = (m14 * m23 * m41 - m13 * m24 * m41 - m14 * m21 * m43 + m11 * m24 * m43 + m13 * m21 * m44 - m11 * m23 * m44) * det;
		mat[13] = (m13 * m24 * m31 - m14 * m23 * m31 + m14 * m21 * m33 - m11 * m24 * m33 - m13 * m21 * m34 + m11 * m23 * m34) * det;
		mat[2] = (m22 * m34 * m41 - m24 * m32 * m41 + m24 * m31 * m42 - m21 * m34 * m42 - m22 * m31 * m44 + m21 * m32 * m44) * det;
		mat[6] = (m14 * m32 * m41 - m12 * m34 * m41 - m14 * m31 * m42 + m11 * m34 * m42 + m12 * m31 * m44 - m11 * m32 * m44) * det;
		mat[10] = (m12 * m24 * m41 - m14 * m22 * m41 + m14 * m21 * m42 - m11 * m24 * m42 - m12 * m21 * m44 + m11 * m22 * m44) * det;
		mat[14] = (m14 * m22 * m31 - m12 * m24 * m31 - m14 * m21 * m32 + m11 * m24 * m32 + m12 * m21 * m34 - m11 * m22 * m34) * det;
		mat[3] = (m23 * m32 * m41 - m22 * m33 * m41 - m23 * m31 * m42 + m21 * m33 * m42 + m22 * m31 * m43 - m21 * m32 * m43) * det;
		mat[7] = (m12 * m33 * m41 - m13 * m32 * m41 + m13 * m31 * m42 - m11 * m33 * m42 - m12 * m31 * m43 + m11 * m32 * m43) * det;
		mat[11] = (m13 * m22 * m41 - m12 * m23 * m41 - m13 * m21 * m42 + m11 * m23 * m42 + m12 * m21 * m43 - m11 * m22 * m43) * det;
		mat[15] = (m12 * m23 * m31 - m13 * m22 * m31 + m13 * m21 * m32 - m11 * m23 * m32 - m12 * m21 * m33 + m11 * m22 * m33) * det;

		return *this;
	}

	inline Mat4& Mat4::Inverse(const Mat4& m) {
		float m11 = m.mat[0], m12 = m.mat[4], m13 = m.mat[8], m14 = m.mat[12],
		      m21 = m.mat[1], m22 = m.mat[5], m23 = m.mat[9], m24 = m.mat[13],
		      m31 = m.mat[2], m32 = m.mat[6], m33 = m.mat[10], m34 = m.mat[14],
		      m41 = m.mat[3], m42 = m.mat[7], m43 = m.mat[11], m44 = m.mat[15],

		      me0 = m23 * m34 * m42 - m24 * m33 * m42 + m24 * m32 * m43 - m22 * m34 * m43 - m23 * m32 * m44 + m22 * m33 * m44,
		      me4 = m14 * m33 * m42 - m13 * m34 * m42 - m14 * m32 * m43 + m12 * m34 * m43 + m13 * m32 * m44 - m12 * m33 * m44,
		      me8 = m13 * m24 * m42 - m14 * m23 * m42 + m14 * m22 * m43 - m12 * m24 * m43 - m13 * m22 * m44 + m12 * m23 * m44,
		      me12 = m14 * m23 * m32 - m13 * m24 * m32 - m14 * m22 * m33 + m12 * m24 * m33 + m13 * m22 * m34 - m12 * m23 * m34,

		      det = m11 * me0 + m21 * me4 + m31 * me8 + m41 * me12;

		if (det == 0.0f) {
			return Identity();
		}

		mat[0] = me0 * det;
		mat[4] = me4 * det;
		mat[8] = me8 * det;
		mat[12] = me12 * det;
		mat[1] = (m24 * m33 * m41 - m23 * m34 * m41 - m24 * m31 * m43 + m21 * m34 * m43 + m23 * m31 * m44 - m21 * m33 * m44) * det;
		mat[5] = (m13 * m34 * m41 - m14 * m33 * m41 + m14 * m31 * m43 - m11 * m34 * m43 - m13 * m31 * m44 + m11 * m33 * m44) * det;
		mat[9] = (m14 * m23 * m41 - m13 * m24 * m41 - m14 * m21 * m43 + m11 * m24 * m43 + m13 * m21 * m44 - m11 * m23 * m44) * det;
		mat[13] = (m13 * m24 * m31 - m14 * m23 * m31 + m14 * m21 * m33 - m11 * m24 * m33 - m13 * m21 * m34 + m11 * m23 * m34) * det;
		mat[2] = (m22 * m34 * m41 - m24 * m32 * m41 + m24 * m31 * m42 - m21 * m34 * m42 - m22 * m31 * m44 + m21 * m32 * m44) * det;
		mat[6] = (m14 * m32 * m41 - m12 * m34 * m41 - m14 * m31 * m42 + m11 * m34 * m42 + m12 * m31 * m44 - m11 * m32 * m44) * det;
		mat[10] = (m12 * m24 * m41 - m14 * m22 * m41 + m14 * m21 * m42 - m11 * m24 * m42 - m12 * m21 * m44 + m11 * m22 * m44) * det;
		mat[14] = (m14 * m22 * m31 - m12 * m24 * m31 - m14 * m21 * m32 + m11 * m24 * m32 + m12 * m21 * m34 - m11 * m22 * m34) * det;
		mat[3] = (m23 * m32 * m41 - m22 * m33 * m41 - m23 * m31 * m42 + m21 * m33 * m42 + m22 * m31 * m43 - m21 * m32 * m43) * det;
		mat[7] = (m12 * m33 * m41 - m13 * m32 * m41 + m13 * m31 * m42 - m11 * m33 * m42 - m12 * m31 * m43 + m11 * m32 * m43) * det;
		mat[11] = (m13 * m22 * m41 - m12 * m23 * m41 - m13 * m21 * m42 + m11 * m23 * m42 + m12 * m21 * m43 - m11 * m22 * m43) * det;
		mat[15] = (m12 * m23 * m31 - m13 * m22 * m31 + m13 * m21 * m32 - m11 * m23 * m32 - m12 * m21 * m33 + m11 * m22 * m33) * det;

		return *this;
	}

	inline Mat4& Mat4::Transpose(void) {
		float tmp;

		tmp = mat[1];
		mat[1] = mat[4];
		mat[4] = tmp;
		tmp = mat[2];
		mat[2] = mat[8];
		mat[8] = tmp;
		tmp = mat[6];
		mat[6] = mat[9];
		mat[9] = tmp;

		tmp = mat[3];
		mat[3] = mat[12];
		mat[12] = tmp;
		tmp = mat[7];
		mat[7] = mat[13];
		mat[13] = tmp;
		tmp = mat[11];
		mat[11] = mat[14];
		mat[14] = tmp;

		return *this;
	}

	inline Mat4& Mat4::Compose(const Vec3& position, const Vec3& scale, const Quat& rotation) {
		float x = rotation.x,
		      y = rotation.y,
		      z = rotation.z,
		      w = rotation.w,
		      x2 = x + x,
		      y2 = y + y,
		      z2 = z + z,
		      xx = x * x2,
		      xy = x * y2,
		      xz = x * z2,
		      yy = y * y2,
		      yz = y * z2,
		      zz = z * z2,
		      wx = w * x2,
		      wy = w * y2,
		      wz = w * z2,

		      sx = scale.x,
		      sy = scale.y,
		      sz = scale.z;

		mat[0] = (1 - (yy + zz)) * sx;
		mat[4] = (xy - wz) * sy;
		mat[8] = (xz + wy) * sz;

		mat[1] = (xy + wz) * sx;
		mat[5] = (1 - (xx + zz)) * sy;
		mat[9] = (yz - wx) * sz;

		mat[2] = (xz - wy) * sx;
		mat[6] = (yz + wx) * sy;
		mat[10] = (1 - (xx + yy)) * sz;

		mat[3] = 0.0f;
		mat[7] = 0.0f;
		mat[11] = 0.0f;

		mat[12] = position.x;
		mat[13] = position.y;
		mat[14] = position.z;
		mat[15] = 1.0f;

		return *this;
	}

	inline Mat4& Mat4::Decompose(Vec3& position, Vec3& scale, Quat& rotation) {
		float m11 = mat[0],
		      m12 = mat[4],
		      m13 = mat[8],
		      m21 = mat[1],
		      m22 = mat[5],
		      m23 = mat[9],
		      m31 = mat[2],
		      m32 = mat[6],
		      m33 = mat[10],
		      x = 0.0f,
		      y = 0.0f,
		      z = 0.0f,
		      w = 1.0f,
		      s,

		      sx = Vec3Length(m11, m21, m31),
		      sy = Vec3Length(m12, m22, m32),
		      sz = Vec3Length(m13, m23, m33),

		      invSx = 1.0f / sx,
		      invSy = 1.0f / sy,
		      invSz = 1.0f / sz,
		      trace;

		scale.x = sx;
		scale.y = sy;
		scale.z = sz;

		position.x = mat[12];
		position.y = mat[13];
		position.z = mat[14];

		m11 *= invSx;
		m12 *= invSy;
		m13 *= invSz;
		m21 *= invSx;
		m22 *= invSy;
		m23 *= invSz;
		m31 *= invSx;
		m32 *= invSy;
		m33 *= invSz;

		trace = m11 + m22 + m33;

		if (trace > 0.0f) {
			s = 0.5f / sqrtf(trace + 1.0f);

			w = 0.25f / s;
			x = (m32 - m23) * s;
			y = (m13 - m31) * s;
			z = (m21 - m12) * s;

		} else if (m11 > m22 && m11 > m33) {
			s = 2.0f * sqrtf(1.0f + m11 - m22 - m33);

			w = (m32 - m23) / s;
			x = 0.25f * s;
			y = (m12 + m21) / s;
			z = (m13 + m31) / s;

		} else if (m22 > m33) {
			s = 2.0f * sqrtf(1.0f + m22 - m11 - m33);

			w = (m13 - m31) / s;
			x = (m12 + m21) / s;
			y = 0.25f * s;
			z = (m23 + m32) / s;

		} else {
			s = 2.0f * sqrtf(1.0f + m33 - m11 - m22);

			w = (m21 - m12) / s;
			x = (m13 + m31) / s;
			y = (m23 + m32) / s;
			z = 0.25f * s;
		}

		rotation.x = x;
		rotation.y = y;
		rotation.z = z;
		rotation.w = w;

		return *this;
	}

	inline Mat4& Mat4::SetPosition(const Vec3& v) {

		mat[12] = v.x;
		mat[13] = v.y;
		mat[14] = v.z;

		return *this;
	}

	inline Vec3 Mat4::GetPosition(void) {

		return Vec3(mat[12], mat[13], mat[14]);
	}

	inline Mat4& Mat4::ExtractPosition(const Mat4& m) {

		mat[12] = m.mat[12];
		mat[13] = m.mat[13];
		mat[14] = m.mat[14];

		return *this;
	}

	inline Mat4& Mat4::ExtractRotation(const Mat4& m) {
		Vec3 vec;
		float lx = Vec3LengthSq(m.mat[0], m.mat[1], m.mat[2]),
		      ly = Vec3LengthSq(m.mat[4], m.mat[5], m.mat[6]),
		      lz = Vec3LengthSq(m.mat[8], m.mat[9], m.mat[10]),

		      scaleX = lx > 0.0f ? 1.0f / sqrtf(lx) : 0.0f,
		      scaleY = ly > 0.0f ? 1.0f / sqrtf(ly) : 0.0f,
		      scaleZ = lz > 0.0f ? 1.0f / sqrtf(lz) : 0.0f;

		mat[0] = m.mat[0] * scaleX;
		mat[1] = m.mat[1] * scaleX;
		mat[2] = m.mat[2] * scaleX;

		mat[4] = m.mat[4] * scaleY;
		mat[5] = m.mat[5] * scaleY;
		mat[6] = m.mat[6] * scaleY;

		mat[8] = m.mat[8] * scaleZ;
		mat[9] = m.mat[9] * scaleZ;
		mat[10] = m.mat[10] * scaleZ;

		return *this;
	}

	inline Mat4& Mat4::ExtractRotationWithScale(const Mat4& m) {

		mat[0] = m.mat[0];
		mat[1] = m.mat[1];
		mat[2] = m.mat[2];

		mat[4] = m.mat[4];
		mat[5] = m.mat[5];
		mat[6] = m.mat[6];

		mat[8] = m.mat[8];
		mat[9] = m.mat[9];
		mat[10] = m.mat[10];

		return *this;
	}

	inline Mat4& Mat4::Scale(const Vec2& v) {
		float x = v.x, y = v.y;

		mat[0] *= x;
		mat[4] *= y;
		mat[1] *= x;
		mat[5] *= y;
		mat[2] *= x;
		mat[6] *= y;
		mat[3] *= x;
		mat[7] *= y;

		return *this;
	}

	inline Mat4& Mat4::Scale(const Vec3& v) {
		float x = v.x, y = v.y, z = v.z;

		mat[0] *= x;
		mat[4] *= y;
		mat[8] *= z;
		mat[1] *= x;
		mat[5] *= y;
		mat[9] *= z;
		mat[2] *= x;
		mat[6] *= y;
		mat[10] *= z;
		mat[3] *= x;
		mat[7] *= y;
		mat[11] *= z;

		return *this;
	}

	inline Mat4& Mat4::Scale(const Vec4& v) {
		float x = v.x, y = v.y, z = v.z, w = v.w;

		mat[0] *= x;
		mat[4] *= y;
		mat[8] *= z;
		mat[12] *= w;
		mat[1] *= x;
		mat[5] *= y;
		mat[9] *= z;
		mat[13] *= w;
		mat[2] *= x;
		mat[6] *= y;
		mat[10] *= z;
		mat[14] *= w;
		mat[3] *= x;
		mat[7] *= y;
		mat[11] *= z;
		mat[15] *= w;

		return *this;
	}

	inline Mat4& Mat4::RotateX(const float angle) {
		float m12 = mat[4],
		      m22 = mat[5],
		      m32 = mat[6],
		      m42 = mat[7],
		      m13 = mat[8],
		      m23 = mat[9],
		      m33 = mat[10],
		      m43 = mat[11],
		      c = cosf(angle),
		      s = sinf(angle);

		mat[4] = c * m12 + s * m13;
		mat[5] = c * m22 + s * m23;
		mat[6] = c * m32 + s * m33;
		mat[7] = c * m42 + s * m43;

		mat[8] = c * m13 - s * m12;
		mat[9] = c * m23 - s * m22;
		mat[10] = c * m33 - s * m32;
		mat[11] = c * m43 - s * m42;

		return *this;
	}

	inline Mat4& Mat4::RotateY(const float angle) {
		float m11 = mat[0],
		      m21 = mat[1],
		      m31 = mat[2],
		      m41 = mat[3],
		      m13 = mat[8],
		      m23 = mat[9],
		      m33 = mat[10],
		      m43 = mat[11],
		      c = cosf(angle),
		      s = sinf(angle);

		mat[0] = c * m11 - s * m13;
		mat[1] = c * m21 - s * m23;
		mat[2] = c * m31 - s * m33;
		mat[3] = c * m41 - s * m43;

		mat[8] = c * m13 + s * m11;
		mat[9] = c * m23 + s * m21;
		mat[10] = c * m33 + s * m31;
		mat[11] = c * m43 + s * m41;

		return *this;
	}

	inline Mat4& Mat4::RotateZ(const float angle) {
		float m11 = mat[0],
		      m21 = mat[1],
		      m31 = mat[2],
		      m41 = mat[3],
		      m13 = mat[8],
		      m23 = mat[9],
		      m33 = mat[10],
		      m43 = mat[11],
		      c = cosf(angle),
		      s = sinf(angle);

		mat[0] = c * m11 - s * m13;
		mat[1] = c * m21 - s * m23;
		mat[2] = c * m31 - s * m33;
		mat[3] = c * m41 - s * m43;

		mat[8] = c * m13 + s * m11;
		mat[9] = c * m23 + s * m21;
		mat[10] = c * m33 + s * m31;
		mat[11] = c * m43 + s * m41;

		return *this;
	}

	inline Mat4& Mat4::FromQuat(const Quat& q) {
		float x = q.x,
		      y = q.y,
		      z = q.z,
		      w = q.w,
		      x2 = x + x,
		      y2 = y + y,
		      z2 = z + z,
		      xx = x * x2,
		      xy = x * y2,
		      xz = x * z2,
		      yy = y * y2,
		      yz = y * z2,
		      zz = z * z2,
		      wx = w * x2,
		      wy = w * y2,
		      wz = w * z2;

		mat[0] = 1.0f - (yy + zz);
		mat[4] = xy - wz;
		mat[8] = xz + wy;

		mat[1] = xy + wz;
		mat[5] = 1.0f - (xx + zz);
		mat[9] = yz - wx;

		mat[2] = xz - wy;
		mat[6] = yz + wx;
		mat[10] = 1.0f - (xx + yy);

		mat[3] = 0.0f;
		mat[7] = 0.0f;
		mat[11] = 0.0f;

		mat[12] = 0.0f;
		mat[13] = 0.0f;
		mat[14] = 0.0f;
		mat[15] = 1.0f;

		return *this;
	}

	inline Mat4& Mat4::Frustum(const float left, const float right, const float top, const float bottom, const float near, const float far) {
		float x = 2.0f * near / (right - left),
		      y = 2.0f * near / (top - bottom),

		      a = (right + left) / (right - left),
		      b = (top + bottom) / (top - bottom),
		      c = -(far + near) / (far - near),
		      d = -2.0f * far * near / (far - near);

		mat[0] = x;
		mat[4] = 0.0f;
		mat[8] = a;
		mat[12] = 0.0f;
		mat[1] = 0.0f;
		mat[5] = y;
		mat[9] = b;
		mat[13] = 0.0f;
		mat[2] = 0.0f;
		mat[6] = 0.0f;
		mat[10] = c;
		mat[14] = d;
		mat[3] = 0.0f;
		mat[7] = 0.0f;
		mat[11] = -1.0f;
		mat[15] = 0.0f;

		return *this;
	}

	inline Mat4& Mat4::Perspective(const float fov, const float aspect, const float near, const float far) {
		float ymax = near * tanf(fov * 0.5f),
		      ymin = -ymax,
		      xmin = ymin * aspect,
		      xmax = ymax * aspect;

		Frustum(xmin, xmax, ymax, ymin, near, far);
		return *this;
	}

	inline Mat4& Mat4::Orthographic(const float left, const float right, const float top, const float bottom, const float near, const float far) {
		float w = right - left,
		      h = top - bottom,
		      p = far - near,

		      x = (right + left) / w,
		      y = (top + bottom) / h,
		      z = (far + near) / p;

		mat[0] = 2.0f / w;
		mat[1] = 0.0f;
		mat[2] = 0.0f;
		mat[3] = 0.0f;
		mat[4] = 0.0f;
		mat[5] = 2.0f / h;
		mat[6] = 0.0f;
		mat[7] = 0.0f;
		mat[8] = 0.0f;
		mat[9] = 0.0f;
		mat[10] = -2.0f / p;
		mat[11] = 0.0f;
		mat[12] = -x;
		mat[13] = -y;
		mat[14] = -z;
		mat[15] = 1.0f;

		return *this;
	}

	inline const float Mat4::operator [] (int i) const {
		return mat[i];
	}

	inline float& Mat4::operator [] (int i) {
		return mat[i];
	}

	inline Mat4 Mat4::operator *(const Vec2& v) {
		float x = v.x, y = v.y;

		return Mat4(
		           mat[0], mat[4], mat[8], mat[0] * x + mat[4] * y + mat[12],
		           mat[1], mat[5], mat[9], mat[1] * x + mat[5] * y + mat[13],
		           mat[2], mat[6], mat[10], mat[2] * x + mat[6] * y + mat[14],
		           mat[3], mat[7], mat[11],  mat[3] * x + mat[7] * y + mat[15]
		       );
	}

	inline Mat4& Mat4::operator +=(const Vec2& v) {
		float x = v.x, y = v.y;

		mat[12] = mat[0] * x + mat[4] * y + mat[12];
		mat[13] = mat[1] * x + mat[5] * y + mat[13];
		mat[14] = mat[2] * x + mat[6] * y + mat[14];
		mat[15] = mat[3] * x + mat[7] * y + mat[15];

		return *this;
	}

	inline Mat4 Mat4::operator *(const Vec3& v) {
		float x = v.x, y = v.y, z = v.z;

		return Mat4(
		           mat[0], mat[4], mat[8], mat[0] * x + mat[4] * y + mat[8] * z + mat[12],
		           mat[1], mat[5], mat[9], mat[1] * x + mat[5] * y + mat[9] * z + mat[13],
		           mat[2], mat[6], mat[10], mat[2] * x + mat[6] * y + mat[10] * z + mat[14],
		           mat[3], mat[7], mat[11],  mat[3] * x + mat[7] * y + mat[11] * z + mat[15]
		       );
	}

	inline Mat4& Mat4::operator *=(const Vec3& v) {
		float x = v.x, y = v.y, z = v.z;

		mat[12] = mat[0] * x + mat[4] * y + mat[8] * z + mat[12];
		mat[13] = mat[1] * x + mat[5] * y + mat[9] * z + mat[13];
		mat[14] = mat[2] * x + mat[6] * y + mat[10] * z + mat[14];
		mat[15] = mat[3] * x + mat[7] * y + mat[11] * z + mat[15];

		return *this;
	}

	inline Mat4 Mat4::operator *(const Vec4& v) {
		float x = v.x, y = v.y, z = v.z, w = v.w;

		return Mat4(
		           mat[0], mat[4], mat[8], mat[0] * x + mat[4] * y + mat[8] * z + mat[12] * w,
		           mat[1], mat[5], mat[9], mat[1] * x + mat[5] * y + mat[9] * z + mat[13] * w,
		           mat[2], mat[6], mat[10], mat[2] * x + mat[6] * y + mat[10] * z + mat[14] * w,
		           mat[3], mat[7], mat[11],  mat[3] * x + mat[7] * y + mat[11] * z + mat[15] * w
		       );
	}

	inline Mat4& Mat4::operator *=(const Vec4& v) {
		float x = v.x, y = v.y, z = v.z, w = v.w;

		mat[12] = mat[0] * x + mat[4] * y + mat[8] * z + mat[12] * w;
		mat[13] = mat[1] * x + mat[5] * y + mat[9] * z + mat[13] * w;
		mat[14] = mat[2] * x + mat[6] * y + mat[10] * z + mat[14] * w;
		mat[15] = mat[3] * x + mat[7] * y + mat[11] * z + mat[15] * w;

		return *this;
	}

	inline Mat4 Mat4::operator *(const Mat4& m) {
		float a11 = mat[0], a12 = mat[4], a13 = mat[8], a14 = mat[12],
		      a21 = mat[1], a22 = mat[5], a23 = mat[9], a24 = mat[13],
		      a31 = mat[2], a32 = mat[6], a33 = mat[10], a34 = mat[14],
		      a41 = mat[3], a42 = mat[7], a43 = mat[11], a44 = mat[15],

		      b11 = m.mat[0], b12 = m.mat[4], b13 = m.mat[8], b14 = m.mat[12],
		      b21 = m.mat[1], b22 = m.mat[5], b23 = m.mat[9], b24 = m.mat[13],
		      b31 = m.mat[2], b32 = m.mat[6], b33 = m.mat[10], b34 = m.mat[14],
		      b41 = m.mat[3], b42 = m.mat[7], b43 = m.mat[11], b44 = m.mat[15];

		return Mat4(
		           a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41,
		           a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42,
		           a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43,
		           a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44,

		           a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41,
		           a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42,
		           a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43,
		           a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44,

		           a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41,
		           a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42,
		           a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43,
		           a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44,

		           a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41,
		           a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42,
		           a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43,
		           a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44
		       );
	}

	inline void Mat4::operator *=(const Mat4& m) {
		float a11 = mat[0], a12 = mat[4], a13 = mat[8], a14 = mat[12],
		      a21 = mat[1], a22 = mat[5], a23 = mat[9], a24 = mat[13],
		      a31 = mat[2], a32 = mat[6], a33 = mat[10], a34 = mat[14],
		      a41 = mat[3], a42 = mat[7], a43 = mat[11], a44 = mat[15],

		      b11 = m.mat[0], b12 = m.mat[4], b13 = m.mat[8], b14 = m.mat[12],
		      b21 = m.mat[1], b22 = m.mat[5], b23 = m.mat[9], b24 = m.mat[13],
		      b31 = m.mat[2], b32 = m.mat[6], b33 = m.mat[10], b34 = m.mat[14],
		      b41 = m.mat[3], b42 = m.mat[7], b43 = m.mat[11], b44 = m.mat[15];

		mat[0] = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41;
		mat[4] = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42;
		mat[8] = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43;
		mat[12] = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44;

		mat[1] = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41;
		mat[5] = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42;
		mat[9] = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43;
		mat[13] = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44;

		mat[2] = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41;
		mat[6] = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42;
		mat[10] = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43;
		mat[14] = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44;

		mat[3] = a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41;
		mat[7] = a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42;
		mat[11] = a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43;
		mat[15] = a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44;
	}

	inline Mat4 Mat4::operator *=(const float s) {
		mat[0] *= s;
		mat[1] *= s;
		mat[2] *= s;
		mat[3] *= s;
		mat[4] *= s;
		mat[5] *= s;
		mat[6] *= s;
		mat[7] *= s;
		mat[8] *= s;
		mat[9] *= s;
		mat[10] *= s;
		mat[11] *= s;
		mat[12] *= s;
		mat[13] *= s;
		mat[14] *= s;
		mat[15] *= s;
	}

	inline Mat4 Mat4::operator /=(const float s) {
		float d = s != 0.0f ? 1.0f / s : 0.0f;

		mat[0] *= d;
		mat[1] *= d;
		mat[2] *= d;
		mat[3] *= d;
		mat[4] *= d;
		mat[5] *= d;
		mat[6] *= d;
		mat[7] *= d;
		mat[8] *= d;
		mat[9] *= d;
		mat[10] *= d;
		mat[11] *= d;
		mat[12] *= d;
		mat[13] *= d;
		mat[14] *= d;
		mat[15] *= d;
	}

	inline Mat4& Mat4::operator =(const Mat4& m) {
		mat[0] = m.mat[0];
		mat[4] = m.mat[4];
		mat[8] = m.mat[8];
		mat[12] = m.mat[12];
		mat[1] = m.mat[1];
		mat[5] = m.mat[5];
		mat[9] = m.mat[9];
		mat[13] = m.mat[13];
		mat[2] = m.mat[2];
		mat[6] = m.mat[6];
		mat[10] = m.mat[10];
		mat[14] = m.mat[14];
		mat[3] = m.mat[3];
		mat[7] = m.mat[7];
		mat[11] = m.mat[11];
		mat[15] = m.mat[15];
	}

	inline Mat4& Mat4::operator =(const Mat4 && m) {
		mat[0] = std::move(m.mat[0]);
		mat[4] = std::move(m.mat[4]);
		mat[8] = std::move(m.mat[8]);
		mat[12] = std::move(m.mat[12]);
		mat[1] = std::move(m.mat[1]);
		mat[5] = std::move(m.mat[5]);
		mat[9] = std::move(m.mat[9]);
		mat[13] = std::move(m.mat[13]);
		mat[2] = std::move(m.mat[2]);
		mat[6] = std::move(m.mat[6]);
		mat[10] = std::move(m.mat[10]);
		mat[14] = std::move(m.mat[14]);
		mat[3] = std::move(m.mat[3]);
		mat[7] = std::move(m.mat[7]);
		mat[11] = std::move(m.mat[11]);
		mat[15] = std::move(m.mat[15]);
	}

	inline bool Mat4::operator ==(const Mat4& m) {
		return !(
		           mat[0] != m.mat[0] || mat[4] != m.mat[4] || mat[8] != m.mat[8] || mat[12] != m.mat[12] ||
		           mat[1] != m.mat[1] || mat[5] != m.mat[5] || mat[9] != m.mat[9] || mat[13] != m.mat[13] ||
		           mat[2] != m.mat[2] || mat[6] != m.mat[6] || mat[10] != m.mat[10] || mat[14] != m.mat[14] ||
		           mat[3] != m.mat[3] || mat[7] != m.mat[7] || mat[11] != m.mat[11] || mat[15] != m.mat[15]
		       );
	}

	inline bool Mat4::operator != (const Mat4& m) {
		return (
		           mat[0] != m.mat[0] || mat[4] != m.mat[4] || mat[8] != m.mat[8] || mat[12] != m.mat[12] ||
		           mat[1] != m.mat[1] || mat[5] != m.mat[5] || mat[9] != m.mat[9] || mat[13] != m.mat[13] ||
		           mat[2] != m.mat[2] || mat[6] != m.mat[6] || mat[10] != m.mat[10] || mat[14] != m.mat[14] ||
		           mat[3] != m.mat[3] || mat[7] != m.mat[7] || mat[11] != m.mat[11] || mat[15] != m.mat[15]
		       );
	}

	inline std::string Mat4::ToString(int p) {

		return (
		           "Mat4[\n"
		           "  " + util.ToString(mat[0], p) + ", " + util.ToString(mat[4], p) + ", " + util.ToString(mat[8], p) + ", " + util.ToString(mat[12], p) + ",\n" +
		           "  " + util.ToString(mat[1], p) + ", " + util.ToString(mat[5], p) + ", " + util.ToString(mat[9], p) + ", " + util.ToString(mat[13], p) + ",\n" +
		           "  " + util.ToString(mat[2], p) + ", " + util.ToString(mat[6], p) + ", " + util.ToString(mat[10], p) + ", " + util.ToString(mat[14], p) + ",\n" +
		           "  " + util.ToString(mat[3], p) + ", " + util.ToString(mat[7], p) + ", " + util.ToString(mat[11], p) + ", " + util.ToString(mat[15], p) + "\n"
		           "]"
		       );
	}

	inline Mat4& Mat4Inverse(const Mat4& a, Mat4& out) {
		float m11 = a.mat[0], m12 = a.mat[4], m13 = a.mat[8], m14 = a.mat[12],
		      m21 = a.mat[1], m22 = a.mat[5], m23 = a.mat[9], m24 = a.mat[13],
		      m31 = a.mat[2], m32 = a.mat[6], m33 = a.mat[10], m34 = a.mat[14],
		      m41 = a.mat[3], m42 = a.mat[7], m43 = a.mat[11], m44 = a.mat[15],

		      me0 = m23 * m34 * m42 - m24 * m33 * m42 + m24 * m32 * m43 - m22 * m34 * m43 - m23 * m32 * m44 + m22 * m33 * m44,
		      me4 = m14 * m33 * m42 - m13 * m34 * m42 - m14 * m32 * m43 + m12 * m34 * m43 + m13 * m32 * m44 - m12 * m33 * m44,
		      me8 = m13 * m24 * m42 - m14 * m23 * m42 + m14 * m22 * m43 - m12 * m24 * m43 - m13 * m22 * m44 + m12 * m23 * m44,
		      me12 = m14 * m23 * m32 - m13 * m24 * m32 - m14 * m22 * m33 + m12 * m24 * m33 + m13 * m22 * m34 - m12 * m23 * m34,

		      det = m11 * me0 + m21 * me4 + m31 * me8 + m41 * me12;

		if (det == 0.0f) {
			return out.Identity();
		}

		out.mat[0] = me0 * det;
		out.mat[4] = me4 * det;
		out.mat[8] = me8 * det;
		out.mat[12] = me12 * det;
		out.mat[1] = (m24 * m33 * m41 - m23 * m34 * m41 - m24 * m31 * m43 + m21 * m34 * m43 + m23 * m31 * m44 - m21 * m33 * m44) * det;
		out.mat[5] = (m13 * m34 * m41 - m14 * m33 * m41 + m14 * m31 * m43 - m11 * m34 * m43 - m13 * m31 * m44 + m11 * m33 * m44) * det;
		out.mat[9] = (m14 * m23 * m41 - m13 * m24 * m41 - m14 * m21 * m43 + m11 * m24 * m43 + m13 * m21 * m44 - m11 * m23 * m44) * det;
		out.mat[13] = (m13 * m24 * m31 - m14 * m23 * m31 + m14 * m21 * m33 - m11 * m24 * m33 - m13 * m21 * m34 + m11 * m23 * m34) * det;
		out.mat[2] = (m22 * m34 * m41 - m24 * m32 * m41 + m24 * m31 * m42 - m21 * m34 * m42 - m22 * m31 * m44 + m21 * m32 * m44) * det;
		out.mat[6] = (m14 * m32 * m41 - m12 * m34 * m41 - m14 * m31 * m42 + m11 * m34 * m42 + m12 * m31 * m44 - m11 * m32 * m44) * det;
		out.mat[10] = (m12 * m24 * m41 - m14 * m22 * m41 + m14 * m21 * m42 - m11 * m24 * m42 - m12 * m21 * m44 + m11 * m22 * m44) * det;
		out.mat[14] = (m14 * m22 * m31 - m12 * m24 * m31 - m14 * m21 * m32 + m11 * m24 * m32 + m12 * m21 * m34 - m11 * m22 * m34) * det;
		out.mat[3] = (m23 * m32 * m41 - m22 * m33 * m41 - m23 * m31 * m42 + m21 * m33 * m42 + m22 * m31 * m43 - m21 * m32 * m43) * det;
		out.mat[7] = (m12 * m33 * m41 - m13 * m32 * m41 + m13 * m31 * m42 - m11 * m33 * m42 - m12 * m31 * m43 + m11 * m32 * m43) * det;
		out.mat[11] = (m13 * m22 * m41 - m12 * m23 * m41 - m13 * m21 * m42 + m11 * m23 * m42 + m12 * m21 * m43 - m11 * m22 * m43) * det;
		out.mat[15] = (m12 * m23 * m31 - m13 * m22 * m31 + m13 * m21 * m32 - m11 * m23 * m32 - m12 * m21 * m33 + m11 * m22 * m33) * det;

		return out;
	}

	inline Mat4& Mat4Mul(const Mat4& a, const Mat4& b, Mat4& out) {
		float a11 = a.mat[0], a12 = a.mat[4], a13 = a.mat[8], a14 = a.mat[12],
		      a21 = a.mat[1], a22 = a.mat[5], a23 = a.mat[9], a24 = a.mat[13],
		      a31 = a.mat[2], a32 = a.mat[6], a33 = a.mat[10], a34 = a.mat[14],
		      a41 = a.mat[3], a42 = a.mat[7], a43 = a.mat[11], a44 = a.mat[15],

		      b11 = b.mat[0], b12 = b.mat[4], b13 = b.mat[8], b14 = b.mat[12],
		      b21 = b.mat[1], b22 = b.mat[5], b23 = b.mat[9], b24 = b.mat[13],
		      b31 = b.mat[2], b32 = b.mat[6], b33 = b.mat[10], b34 = b.mat[14],
		      b41 = b.mat[3], b42 = b.mat[7], b43 = b.mat[11], b44 = b.mat[15];

		out.mat[0] = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41;
		out.mat[4] = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42;
		out.mat[8] = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43;
		out.mat[12] = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44;

		out.mat[1] = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41;
		out.mat[5] = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42;
		out.mat[9] = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43;
		out.mat[13] = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44;

		out.mat[2] = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41;
		out.mat[6] = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42;
		out.mat[10] = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43;
		out.mat[14] = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44;

		out.mat[3] = a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41;
		out.mat[7] = a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42;
		out.mat[11] = a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43;
		out.mat[15] = a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44;

		return out;
	}
}

#endif