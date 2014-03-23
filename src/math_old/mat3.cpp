#ifndef _ODIN_MAT3_CPP_
#define _ODIN_MAT3_CPP_

namespace Odin {

	inline Mat3::Mat3(void) {
		m_mat[0] = 1.0f;
		m_mat[3] = 0.0f;
		m_mat[6] = 0.0f;
		m_mat[1] = 0.0f;
		m_mat[4] = 1.0f;
		m_mat[7] = 0.0f;
		m_mat[2] = 0.0f;
		m_mat[5] = 0.0f;
		m_mat[8] = 1.0f;
	}

	inline Mat3::Mat3(
	    float32 m11, float32 m21, float32 m31,
	    float32 m12, float32 m22, float32 m32,
	    float32 m13, float32 m23, float32 m33
	) {
		m_mat[0] = m11;
		m_mat[3] = m21;
		m_mat[6] = m31;
		m_mat[1] = m12;
		m_mat[4] = m22;
		m_mat[7] = m32;
		m_mat[2] = m13;
		m_mat[5] = m23;
		m_mat[8] = m33;
	}

	inline Mat3::Mat3(const Mat3& m) {
		m_mat[0] = m.m_mat[0];
		m_mat[3] = m.m_mat[3];
		m_mat[6] = m.m_mat[6];
		m_mat[1] = m.m_mat[1];
		m_mat[4] = m.m_mat[4];
		m_mat[7] = m.m_mat[7];
		m_mat[2] = m.m_mat[2];
		m_mat[5] = m.m_mat[5];
		m_mat[8] = m.m_mat[8];
	}

	inline Mat3::Mat3(const Mat3&& m) {
		m_mat[0] = std::move(m.m_mat[0]);
		m_mat[3] = std::move(m.m_mat[3]);
		m_mat[6] = std::move(m.m_mat[6]);
		m_mat[1] = std::move(m.m_mat[1]);
		m_mat[4] = std::move(m.m_mat[4]);
		m_mat[7] = std::move(m.m_mat[7]);
		m_mat[2] = std::move(m.m_mat[2]);
		m_mat[5] = std::move(m.m_mat[5]);
		m_mat[8] = std::move(m.m_mat[8]);
	}

	inline Mat3::~Mat3(void) {}

	inline Mat3& Mat3::Identity(void) {
		m_mat[0] = 1.0f;
		m_mat[3] = 0.0f;
		m_mat[6] = 0.0f;
		m_mat[1] = 0.0f;
		m_mat[4] = 1.0f;
		m_mat[7] = 0.0f;
		m_mat[2] = 0.0f;
		m_mat[5] = 0.0f;
		m_mat[8] = 1.0f;

		return *this;
	}

	inline Mat3& Mat3::SetTrace(float32 x, float32 y, float32 z) {
		m_mat[0] = x;
		m_mat[4] = y;
		m_mat[8] = z;

		return *this;
	}

	inline Mat3& Mat3::operator -() {
		float32 m11 = m_mat[0], m12 = m_mat[3], m13 = m_mat[6],
		        m21 = m_mat[1], m22 = m_mat[4], m23 = m_mat[7],
		        m31 = m_mat[2], m32 = m_mat[5], m33 = m_mat[8],

		        m0 = m22 * m33 - m23 * m32,
		        m3 = m13 * m32 - m12 * m33,
		        m6 = m12 * m23 - m13 * m22,

		        det = m11 * m0 + m21 * m3 + m31 * m6;

		det = det != 0.0f ? 1.0f / det : 1.0f;

		m_mat[0] = m0 * det;
		m_mat[1] = (m23 * m31 - m21 * m33) * det;
		m_mat[2] = (m21 * m32 - m22 * m31) * det;

		m_mat[3] = m3 * det;
		m_mat[4] = (m11 * m33 - m13 * m31) * det;
		m_mat[5] = (m12 * m31 - m11 * m32) * det;

		m_mat[6] = m6 * det;
		m_mat[7] = (m13 * m21 - m11 * m23) * det;
		m_mat[8] = (m11 * m22 - m12 * m21) * det;

		return *this;
	}

	inline Mat3& Mat3::Inverse(void) {
		float32 m11 = m_mat[0], m12 = m_mat[3], m13 = m_mat[6],
		        m21 = m_mat[1], m22 = m_mat[4], m23 = m_mat[7],
		        m31 = m_mat[2], m32 = m_mat[5], m33 = m_mat[8],

		        m0 = m22 * m33 - m23 * m32,
		        m3 = m13 * m32 - m12 * m33,
		        m6 = m12 * m23 - m13 * m22,

		        det = m11 * m0 + m21 * m3 + m31 * m6;

		det = det != 0.0f ? 1.0f / det : 1.0f;

		m_mat[0] = m0 * det;
		m_mat[1] = (m23 * m31 - m21 * m33) * det;
		m_mat[2] = (m21 * m32 - m22 * m31) * det;

		m_mat[3] = m3 * det;
		m_mat[4] = (m11 * m33 - m13 * m31) * det;
		m_mat[5] = (m12 * m31 - m11 * m32) * det;

		m_mat[6] = m6 * det;
		m_mat[7] = (m13 * m21 - m11 * m23) * det;
		m_mat[8] = (m11 * m22 - m12 * m21) * det;

		return *this;
	}

	inline Mat3& Mat3::Inverse(const Mat3& m) {
		float32 m11 = m.m_mat[0], m12 = m.m_mat[3], m13 = m.m_mat[6],
		        m21 = m.m_mat[1], m22 = m.m_mat[4], m23 = m.m_mat[7],
		        m31 = m.m_mat[2], m32 = m. m_mat[5], m33 = m.m_mat[8],

		        m0 = m22 * m33 - m23 * m32,
		        m3 = m13 * m32 - m12 * m33,
		        m6 = m12 * m23 - m13 * m22,

		        det = m11 * m0 + m21 * m3 + m31 * m6;

		det = det != 0.0f ? 1.0f / det : 1.0f;

		m_mat[0] = m0 * det;
		m_mat[1] = (m23 * m31 - m21 * m33) * det;
		m_mat[2] = (m21 * m32 - m22 * m31) * det;

		m_mat[3] = m3 * det;
		m_mat[4] = (m11 * m33 - m13 * m31) * det;
		m_mat[5] = (m12 * m31 - m11 * m32) * det;

		m_mat[6] = m6 * det;
		m_mat[7] = (m13 * m21 - m11 * m23) * det;
		m_mat[8] = (m11 * m22 - m12 * m21) * det;

		return *this;
	}

	inline Mat3& Mat3::Inverse(const Mat4& m) {
		float32 m11 = m.m_mat[0], m12 = m.m_mat[4], m13 = m.m_mat[8],
		        m21 = m.m_mat[1], m22 = m.m_mat[5], m23 = m.m_mat[9],
		        m31 = m.m_mat[2], m32 = m.m_mat[6], m33 = m.m_mat[10],

		        m0 = m22 * m33 - m23 * m32,
		        m3 = m13 * m32 - m12 * m33,
		        m6 = m12 * m23 - m13 * m22,

		        det = m11 * m0 + m21 * m3 + m31 * m6;

		det = det != 0.0f ? 1.0f / det : 1.0f;

		m_mat[0] = m0 * det;
		m_mat[1] = (m23 * m31 - m21 * m33) * det;
		m_mat[2] = (m21 * m32 - m22 * m31) * det;

		m_mat[3] = m3 * det;
		m_mat[4] = (m11 * m33 - m13 * m31) * det;
		m_mat[5] = (m12 * m31 - m11 * m32) * det;

		m_mat[6] = m6 * det;
		m_mat[7] = (m13 * m21 - m11 * m23) * det;
		m_mat[8] = (m11 * m22 - m12 * m21) * det;

		return *this;
	}

	inline Mat3& Mat3::Transpose(void) {
		float32 tmp;

		tmp = m_mat[1];
		m_mat[1] = m_mat[3];
		m_mat[3] = tmp;
		tmp = m_mat[2];
		m_mat[2] = m_mat[6];
		m_mat[6] = tmp;
		tmp = m_mat[5];
		m_mat[5] = m_mat[7];
		m_mat[7] = tmp;

		return *this;
	}

	inline Mat3& Mat3::ExtractRotation(const Mat3& m) {
		Vec3 vec;
		float32 lx = Vec3LengthSq(m.m_mat[0], m.m_mat[1], m.m_mat[2]),
		        ly = Vec3LengthSq(m.m_mat[3], m.m_mat[4], m.m_mat[5]),
		        lz = Vec3LengthSq(m.m_mat[6], m.m_mat[7], m.m_mat[8]),

		        scaleX = lx > 0.0f ? 1.0f / sqrtf(lx) : 0.0f,
		        scaleY = ly > 0.0f ? 1.0f / sqrtf(ly) : 0.0f,
		        scaleZ = lz > 0.0f ? 1.0f / sqrtf(lz) : 0.0f;

		m_mat[0] = m.m_mat[0] * scaleX;
		m_mat[1] = m.m_mat[1] * scaleX;
		m_mat[2] = m.m_mat[2] * scaleX;

		m_mat[3] = m.m_mat[3] * scaleY;
		m_mat[4] = m.m_mat[4] * scaleY;
		m_mat[5] = m.m_mat[5] * scaleY;

		m_mat[6] = m.m_mat[6] * scaleZ;
		m_mat[7] = m.m_mat[7] * scaleZ;
		m_mat[8] = m.m_mat[8] * scaleZ;

		return *this;
	}

	inline Mat3& Mat3::ExtractRotation(const Mat4& m) {
		Vec3 vec;
		float32 lx = Vec3LengthSq(m[0], m[1], m[2]),
		        ly = Vec3LengthSq(m[4], m[5], m[6]),
		        lz = Vec3LengthSq(m[8], m[9], m[10]),

		        scaleX = lx > 0.0f ? 1.0f / sqrtf(lx) : 0.0f,
		        scaleY = ly > 0.0f ? 1.0f / sqrtf(ly) : 0.0f,
		        scaleZ = lz > 0.0f ? 1.0f / sqrtf(lz) : 0.0f;

		m_mat[0] = m[0] * scaleX;
		m_mat[1] = m[1] * scaleX;
		m_mat[2] = m[2] * scaleX;

		m_mat[3] = m[4] * scaleY;
		m_mat[4] = m[5] * scaleY;
		m_mat[5] = m[6] * scaleY;

		m_mat[6] = m[8] * scaleZ;
		m_mat[7] = m[9] * scaleZ;
		m_mat[8] = m[10] * scaleZ;

		return *this;
	}

	inline Mat3& Mat3::ExtractRotationWithScale(const Mat4& m)  {

		m_mat[0] = m[0];
		m_mat[1] = m[1];
		m_mat[2] = m[2];

		m_mat[3] = m[4];
		m_mat[4] = m[5];
		m_mat[5] = m[6];

		m_mat[6] = m[8];
		m_mat[7] = m[9];
		m_mat[8] = m[10];

		return *this;
	}

	inline Mat3& Mat3::Scale(const Vec2& v) {
		float32 x = v.x, y = v.y;

		m_mat[0] *= x;
		m_mat[3] *= y;
		m_mat[1] *= x;
		m_mat[4] *= y;
		m_mat[2] *= x;
		m_mat[5] *= y;

		return *this;
	}

	inline Mat3& Mat3::Scale(const Vec3& v) {
		float32 x = v.x, y = v.y, z = v.z;

		m_mat[0] *= x;
		m_mat[3] *= y;
		m_mat[6] *= z;
		m_mat[1] *= x;
		m_mat[4] *= y;
		m_mat[7] *= z;
		m_mat[2] *= x;
		m_mat[5] *= y;
		m_mat[8] *= z;

		return *this;
	}

	inline Mat3& Mat3::Scale(const Vec4& v) {
		float32 x = v.x, y = v.y, z = v.z;

		m_mat[0] *= x;
		m_mat[3] *= y;
		m_mat[6] *= z;
		m_mat[1] *= x;
		m_mat[4] *= y;
		m_mat[7] *= z;
		m_mat[2] *= x;
		m_mat[5] *= y;
		m_mat[8] *= z;

		return *this;
	}

	inline Mat3& Mat3::FromQuat(const Quat& q) {
		float32 x = q.x,
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

		m_mat[0] = 1.0f - (yy + zz);
		m_mat[3] = xy - wz;
		m_mat[6] = xz + wy;

		m_mat[1] = xy + wz;
		m_mat[4] = 1.0f - (xx + zz);
		m_mat[7] = yz - wx;

		m_mat[2] = xz - wy;
		m_mat[5] = yz + wx;
		m_mat[8] = 1.0f - (xx + yy);

		return *this;
	}

	inline float32 Mat3::operator [] (int32 i) const {
		return m_mat[i];
	}

	inline float32& Mat3::operator [] (int32 i) {
		return m_mat[i];
	}

	inline Mat3 Mat3::operator *(const Mat3& m) {
		float32 a11 = m_mat[0], a12 = m_mat[3], a13 = m_mat[6],
		        a21 = m_mat[1], a22 = m_mat[4], a23 = m_mat[7],
		        a31 = m_mat[2], a32 = m_mat[5], a33 = m_mat[8],

		        b11 = m.m_mat[0], b12 = m.m_mat[3], b13 = m.m_mat[6],
		        b21 = m.m_mat[1], b22 = m.m_mat[4], b23 = m.m_mat[7],
		        b31 = m.m_mat[2], b32 = m.m_mat[5], b33 = m.m_mat[8];

		return Mat3(
		           a11 * b11 + a21 * b12 + a31 * b13,
		           a12 * b11 + a22 * b12 + a32 * b13,
		           a13 * b11 + a23 * b12 + a33 * b13,

		           a11 * b21 + a21 * b22 + a31 * b23,
		           a12 * b21 + a22 * b22 + a32 * b23,
		           a13 * b21 + a23 * b22 + a33 * b23,

		           a11 * b31 + a21 * b32 + a31 * b33,
		           a12 * b31 + a22 * b32 + a32 * b33,
		           a13 * b31 + a23 * b32 + a33 * b33
		       );
	}

	inline void Mat3::operator *=(const Mat3& m) {
		float32 a11 = m_mat[0], a12 = m_mat[3], a13 = m_mat[6],
		        a21 = m_mat[1], a22 = m_mat[4], a23 = m_mat[7],
		        a31 = m_mat[2], a32 = m_mat[5], a33 = m_mat[8],

		        b11 = m.m_mat[0], b12 = m.m_mat[3], b13 = m.m_mat[6],
		        b21 = m.m_mat[1], b22 = m.m_mat[4], b23 = m.m_mat[7],
		        b31 = m.m_mat[2], b32 = m.m_mat[5], b33 = m.m_mat[8];

		m_mat[0] = a11 * b11 + a21 * b12 + a31 * b13;
		m_mat[3] = a12 * b11 + a22 * b12 + a32 * b13;
		m_mat[6] = a13 * b11 + a23 * b12 + a33 * b13;

		m_mat[1] = a11 * b21 + a21 * b22 + a31 * b23;
		m_mat[4] = a12 * b21 + a22 * b22 + a32 * b23;
		m_mat[7] = a13 * b21 + a23 * b22 + a33 * b23;

		m_mat[2] = a11 * b31 + a21 * b32 + a31 * b33;
		m_mat[5] = a12 * b31 + a22 * b32 + a32 * b33;
		m_mat[8] = a13 * b31 + a23 * b32 + a33 * b33;
	}

	inline void Mat3::operator *=(float32 s) {
		m_mat[0] *= s;
		m_mat[1] *= s;
		m_mat[2] *= s;
		m_mat[3] *= s;
		m_mat[4] *= s;
		m_mat[5] *= s;
		m_mat[6] *= s;
		m_mat[7] *= s;
		m_mat[8] *= s;
	}

	inline void Mat3::operator /=(float32 s) {
		float32 d = s != 0.0f ? 1.0f / s : 0.0f;

		m_mat[0] *= d;
		m_mat[1] *= d;
		m_mat[2] *= d;
		m_mat[3] *= d;
		m_mat[4] *= d;
		m_mat[5] *= d;
		m_mat[6] *= d;
		m_mat[7] *= d;
		m_mat[8] *= d;
	}

	inline Mat3& Mat3::operator =(const Mat3& m) {

		m_mat[0] = m.m_mat[0];
		m_mat[1] = m.m_mat[1];
		m_mat[2] = m.m_mat[2];
		m_mat[3] = m.m_mat[3];
		m_mat[4] = m.m_mat[4];
		m_mat[5] = m.m_mat[5];
		m_mat[6] = m.m_mat[6];
		m_mat[7] = m.m_mat[7];
		m_mat[8] = m.m_mat[8];

		return *this;
	}

	inline Mat3& Mat3::operator =(const Mat3 && m) {

		m_mat[0] = std::move(m.m_mat[0]);
		m_mat[1] = std::move(m.m_mat[1]);
		m_mat[2] = std::move(m.m_mat[2]);
		m_mat[3] = std::move(m.m_mat[3]);
		m_mat[4] = std::move(m.m_mat[4]);
		m_mat[5] = std::move(m.m_mat[5]);
		m_mat[6] = std::move(m.m_mat[6]);
		m_mat[7] = std::move(m.m_mat[7]);
		m_mat[8] = std::move(m.m_mat[8]);

		return *this;
	}

	inline bool Mat3::operator ==(const Mat3& m) {
		return !(
		           m_mat[0] != m.m_mat[0] || m_mat[3] != m.m_mat[3] || m_mat[6] != m.m_mat[6] ||
		           m_mat[1] != m.m_mat[1] || m_mat[4] != m.m_mat[4] || m_mat[7] != m.m_mat[7] ||
		           m_mat[2] != m.m_mat[2] || m_mat[5] != m.m_mat[5] || m_mat[8] != m.m_mat[8]
		       );
	}

	inline bool Mat3::operator !=(const Mat3& m) {
		return (
		           m_mat[0] != m.m_mat[0] || m_mat[3] != m.m_mat[3] || m_mat[6] != m.m_mat[6] ||
		           m_mat[1] != m.m_mat[1] || m_mat[4] != m.m_mat[4] || m_mat[7] != m.m_mat[7] ||
		           m_mat[2] != m.m_mat[2] || m_mat[5] != m.m_mat[5] || m_mat[8] != m.m_mat[8]
		       );
	}

	inline std::string Mat3::ToString(int32 p) {

		return (
		           "Mat3[\n"
		           "  " + util.ToString(m_mat[0], p) + ", " + util.ToString(m_mat[3], p) + ", " + util.ToString(m_mat[6], p) + ",\n" +
		           "  " + util.ToString(m_mat[1], p) + ", " + util.ToString(m_mat[4], p) + ", " + util.ToString(m_mat[7], p) + ",\n" +
		           "  " + util.ToString(m_mat[2], p) + ", " + util.ToString(m_mat[5], p) + ", " + util.ToString(m_mat[8], p) + "\n" +
		           "]"
		       );
	}

	inline Mat3& Mat3Inverse(const Mat3& a, Mat3& out) {
		float32 m11 = a.m_mat[0], m12 = a.m_mat[3], m13 = a.m_mat[6],
		        m21 = a.m_mat[1], m22 = a.m_mat[4], m23 = a.m_mat[7],
		        m31 = a.m_mat[2], m32 = a.m_mat[5], m33 = a.m_mat[8],

		        m0 = m22 * m33 - m23 * m32,
		        m3 = m13 * m32 - m12 * m33,
		        m6 = m12 * m23 - m13 * m22,

		        det = m11 * m0 + m21 * m3 + m31 * m6;

		det = det != 0.0f ? 1.0f / det : 1.0f;

		out.m_mat[0] = m0 * det;
		out.m_mat[1] = (m23 * m31 - m21 * m33) * det;
		out.m_mat[2] = (m21 * m32 - m22 * m31) * det;

		out.m_mat[3] = m3 * det;
		out.m_mat[4] = (m11 * m33 - m13 * m31) * det;
		out.m_mat[5] = (m12 * m31 - m11 * m32) * det;

		out.m_mat[6] = m6 * det;
		out.m_mat[7] = (m13 * m21 - m11 * m23) * det;
		out.m_mat[8] = (m11 * m22 - m12 * m21) * det;

		return out;
	}

	inline Mat3& Mat3InverseMat4(const Mat4& a, Mat3& out) {
		float32 m11 = a.m_mat[0], m12 = a.m_mat[4], m13 = a.m_mat[8],
		        m21 = a.m_mat[1], m22 = a.m_mat[5], m23 = a.m_mat[9],
		        m31 = a.m_mat[2], m32 = a.m_mat[6], m33 = a.m_mat[10],

		        m0 = m22 * m33 - m23 * m32,
		        m3 = m13 * m32 - m12 * m33,
		        m6 = m12 * m23 - m13 * m22,

		        det = m11 * m0 + m21 * m3 + m31 * m6;

		det = det != 0.0f ? 1.0f / det : 1.0f;

		out.m_mat[0] = m0 * det;
		out.m_mat[1] = (m23 * m31 - m21 * m33) * det;
		out.m_mat[2] = (m21 * m32 - m22 * m31) * det;

		out.m_mat[3] = m3 * det;
		out.m_mat[4] = (m11 * m33 - m13 * m31) * det;
		out.m_mat[5] = (m12 * m31 - m11 * m32) * det;

		out.m_mat[6] = m6 * det;
		out.m_mat[7] = (m13 * m21 - m11 * m23) * det;
		out.m_mat[8] = (m11 * m22 - m12 * m21) * det;

		return out;
	}

	inline Mat3& Mat3Mul(const Mat3& a, const Mat3& b, Mat3& out) {
		float32 a11 = a.m_mat[0], a12 = a.m_mat[3], a13 = a.m_mat[6],
		        a21 = a.m_mat[1], a22 = a.m_mat[4], a23 = a.m_mat[7],
		        a31 = a.m_mat[2], a32 = a.m_mat[5], a33 = a.m_mat[8],

		        b11 = b.m_mat[0], b12 = b.m_mat[3], b13 = b.m_mat[6],
		        b21 = b.m_mat[1], b22 = b.m_mat[4], b23 = b.m_mat[7],
		        b31 = b.m_mat[2], b32 = b.m_mat[5], b33 = b.m_mat[8];

		out.m_mat[0] = a11 * b11 + a21 * b12 + a31 * b13;
		out.m_mat[3] = a12 * b11 + a22 * b12 + a32 * b13;
		out.m_mat[6] = a13 * b11 + a23 * b12 + a33 * b13;

		out.m_mat[1] = a11 * b21 + a21 * b22 + a31 * b23;
		out.m_mat[4] = a12 * b21 + a22 * b22 + a32 * b23;
		out.m_mat[7] = a13 * b21 + a23 * b22 + a33 * b23;

		out.m_mat[2] = a11 * b31 + a21 * b32 + a31 * b33;
		out.m_mat[5] = a12 * b31 + a22 * b32 + a32 * b33;
		out.m_mat[8] = a13 * b31 + a23 * b32 + a33 * b33;

		return out;
	}
}

#endif