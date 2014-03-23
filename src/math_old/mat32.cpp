#ifndef _ODIN_MAT32_CPP_
#define _ODIN_MAT32_CPP_

namespace Odin {

	inline Mat32::Mat32(void) {
		m_mat[0] = 1.0f;
		m_mat[2] = 0.0f;
		m_mat[4] = 0.0f;
		m_mat[1] = 0.0f;
		m_mat[3] = 1.0f;
		m_mat[5] = 0.0f;
	}

	inline Mat32::Mat32(float32 m11, float32 m21, float32 m31, float32 m12, float32 m22, float32 m32) {
		m_mat[0] = m11;
		m_mat[2] = m21;
		m_mat[4] = m31;
		m_mat[1] = m12;
		m_mat[3] = m22;
		m_mat[5] = m32;
	}

	inline Mat32::Mat32(const Mat2& m) {
		m_mat[0] = m[0];
		m_mat[2] = m[1];
		m_mat[4] = 0.0f;
		m_mat[1] = m[2];
		m_mat[3] = m[3];
		m_mat[5] = 0.0f;
	}

	inline Mat32::Mat32(const Mat2& m, const Vec2& v) {
		m_mat[0] = m[0];
		m_mat[2] = m[2];
		m_mat[4] = v.x;
		m_mat[1] = m[1];
		m_mat[3] = m[3];
		m_mat[5] = v.y;
	}

	inline Mat32::Mat32(const Vec2& v, float32 angle) {
		float32 c = cosf(angle),
		        s = sinf(angle);

		m_mat[0] = c;
		m_mat[2] = -s;
		m_mat[4] = v.x;
		m_mat[1] = s;
		m_mat[3] = c;
		m_mat[5] = v.y;
	}

	inline Mat32::Mat32(const Mat32& m) {
		m_mat[0] = m.m_mat[0];
		m_mat[2] = m.m_mat[2];
		m_mat[4] = m.m_mat[4];
		m_mat[1] = m.m_mat[1];
		m_mat[3] = m.m_mat[3];
		m_mat[5] = m.m_mat[5];
	}

	inline Mat32::Mat32(const Mat32&& m) {
		m_mat[0] = std::move(m.m_mat[0]);
		m_mat[1] = std::move(m.m_mat[1]);
		m_mat[2] = std::move(m.m_mat[2]);
		m_mat[3] = std::move(m.m_mat[3]);
		m_mat[4] = std::move(m.m_mat[4]);
		m_mat[5] = std::move(m.m_mat[5]);
	}

	inline Mat32::~Mat32(void) {}

	inline Mat32& Mat32::Identity(void) {
		m_mat[0] = 1.0f;
		m_mat[2] = 0.0f;
		m_mat[4] = 0.0f;
		m_mat[1] = 0.0f;
		m_mat[3] = 1.0f;
		m_mat[5] = 0.0f;

		return *this;
	}

	inline Mat32& Mat32::SetTrace(float32 x, float32 y) {
		m_mat[0] = x;
		m_mat[3] = y;

		return *this;
	}

	inline Mat32& Mat32::operator -() {
		float32 m11 = m_mat[0],
		        m12 = m_mat[1],
		        m21 = m_mat[2],
		        m22 = m_mat[3],
		        m31 = m_mat[4],
		        m32 = m_mat[5],

		        det = m11 * m22 - m12 * m21;

		if (det == 0.0f) {
			return Identity();
		}

		det = 1.0f / det;

		m_mat[0] = m22 * det;
		m_mat[2] = -m12 * det;
		m_mat[1] = -m21 * det;
		m_mat[3] = m11 * det;

		m_mat[4] = (m12 * m32 - m22 * m31) * det;
		m_mat[5] = (m21 * m31 - m11 * m32) * det;

		return *this;
	}

	inline Mat32& Mat32::Inverse(void) {
		float32 m11 = m_mat[0],
		        m12 = m_mat[1],
		        m21 = m_mat[2],
		        m22 = m_mat[3],
		        m31 = m_mat[4],
		        m32 = m_mat[5],

		        det = m11 * m22 - m12 * m21;

		if (det == 0.0f) {
			return Identity();
		}

		det = 1.0f / det;

		m_mat[0] = m22 * det;
		m_mat[2] = -m12 * det;
		m_mat[1] = -m21 * det;
		m_mat[3] = m11 * det;

		m_mat[4] = (m12 * m32 - m22 * m31) * det;
		m_mat[5] = (m21 * m31 - m11 * m32) * det;

		return *this;
	}

	inline Mat32& Mat32::Inverse(const Mat32& m) {
		float32 m11 = m.m_mat[0],
		        m12 = m.m_mat[1],
		        m21 = m.m_mat[2],
		        m22 = m.m_mat[3],
		        m31 = m.m_mat[4],
		        m32 = m.m_mat[5],

		        det = m11 * m22 - m12 * m21;

		if (det == 0.0f) {
			return Identity();
		}

		det = 1.0f / det;

		m_mat[0] = m22 * det;
		m_mat[2] = -m12 * det;
		m_mat[1] = -m21 * det;
		m_mat[3] = m11 * det;

		m_mat[4] = (m12 * m32 - m22 * m31) * det;
		m_mat[5] = (m21 * m31 - m11 * m32) * det;

		return *this;
	}

	inline Mat32& Mat32::Transpose(void) {
		float32 tmp;

		tmp = m_mat[1];
		m_mat[1] = m_mat[2];
		m_mat[2] = tmp;

		return *this;
	}

	inline Mat32& Mat32::Compose(const Vec2& position, const Vec2& scale, float32 angle) {
		float32 sx = scale.x,
		        sy = scale.y,
		        c = cosf(angle),
		        s = sinf(angle);

		m_mat[0] = c * sx;
		m_mat[1] = s * sx;
		m_mat[2] = -s * sy;
		m_mat[3] = c * sy;

		m_mat[4] = position.x;
		m_mat[5] = position.y;

		return *this;
	}

	inline Mat32& Mat32::Decompose(Vec2& position, Vec2& scale, float32& angle) {
		float32 m11 = m_mat[0],
		        m12 = m_mat[1],
		        sx = scale.Set(m11, m12).Length(),
		        sy = scale.Set(m_mat[2], m_mat[3]).Length();

		position.x = m_mat[4];
		position.y = m_mat[5];

		scale.x = sx;
		scale.y = sy;

		angle = atan2f(m12, m11);

		return *this;
	}

	inline Mat32& Mat32::SetRotation(float32 a) {
		float32 s = sinf(a), c = cosf(a);

		m_mat[0] = c;
		m_mat[2] = -s;
		m_mat[1] = s;
		m_mat[3] = c;

		return *this;
	}

	inline float32 Mat32::GetRotation(void) {

		return atan2f(m_mat[2], m_mat[0]);
	}

	inline Mat32& Mat32::SetPosition(const Vec2& v) {

		m_mat[4] = v.x;
		m_mat[5] = v.y;

		return *this;
	}

	inline Vec2 Mat32::GetPosition(void) {

		return Vec2(m_mat[4], m_mat[5]);
	}

	inline Mat32& Mat32::Rotate(float32 a) {
		float32 a11 = m_mat[0],
		        a12 = m_mat[1],
		        a21 = m_mat[2],
		        a22 = m_mat[3],
		        s = sinf(a), c = cosf(a);

		m_mat[0] = a11 * c + a21 * s;
		m_mat[2] = a12 * c + a22 * s;
		m_mat[1] = a11 * -s + a21 * c;
		m_mat[3] = a12 * -s + a22 * c;

		return *this;
	}

	inline Mat32& Mat32::Orthographic(float32 left, float32 right, float32 top, float32 bottom) {
		float32 w = right - left,
		        h = top - bottom,

		        x = (right + left) / w,
		        y = (top + bottom) / h;

		m_mat[0] = 2 / w;
		m_mat[1] = 0;
		m_mat[2] = 0;
		m_mat[3] = 2 / h;
		m_mat[4] = -x;
		m_mat[5] = -y;

		return *this;
	}

	inline float32 Mat32::operator [] (int32 i) const {
		return m_mat[i];
	}

	inline float32& Mat32::operator [] (int32 i) {
		return m_mat[i];
	}

	inline Mat32 Mat32::operator *(const Mat32& m) {
		float32 a11 = m_mat[0],
		        a12 = m_mat[1],
		        a13 = m_mat[2],
		        a21 = m_mat[3],
		        a22 = m_mat[4],
		        a23 = m_mat[5],

		        b11 = m.m_mat[0],
		        b12 = m.m_mat[1],
		        b13 = m.m_mat[2],
		        b21 = m.m_mat[3],
		        b22 = m.m_mat[4],
		        b23 = m.m_mat[5];

		return Mat32(
		           a11 * b11 + a21 * b12,
		           a12 * b11 + a22 * b12,

		           a11 * b21 + a21 * b22,
		           a12 * b21 + a22 * b22,

		           a11 * b13 + a12 * b23 + a13,
		           a21 * b13 + a22 * b23 + a23
		       );
	}

	inline void Mat32::operator *=(const Mat32& m) {
		float32 a11 = m_mat[0],
		        a12 = m_mat[1],
		        a13 = m_mat[2],
		        a21 = m_mat[3],
		        a22 = m_mat[4],
		        a23 = m_mat[5],

		        b11 = m.m_mat[0],
		        b12 = m.m_mat[1],
		        b13 = m.m_mat[2],
		        b21 = m.m_mat[3],
		        b22 = m.m_mat[4],
		        b23 = m.m_mat[5];

		m_mat[0] = a11 * b11 + a21 * b12;
		m_mat[1] = a12 * b11 + a22 * b12;

		m_mat[3] = a11 * b21 + a21 * b22;
		m_mat[4] = a12 * b21 + a22 * b22;

		m_mat[2] = a11 * b13 + a12 * b23 + a13;
		m_mat[5] = a21 * b13 + a22 * b23 + a23;
	}

	inline void Mat32::operator *=(float32 s) {
		m_mat[0] *= s;
		m_mat[1] *= s;
		m_mat[2] *= s;
		m_mat[3] *= s;
		m_mat[4] *= s;
		m_mat[5] *= s;
	}

	inline void Mat32::operator /=(float32 s) {
		float32 d = s != 0.0f ? 1.0f / s : 0.0f;

		m_mat[0] *= d;
		m_mat[1] *= d;
		m_mat[2] *= d;
		m_mat[3] *= d;
		m_mat[4] *= d;
		m_mat[5] *= d;
	}

	inline Mat32& Mat32::operator =(const Mat32& m) {
		m_mat[0] = m.m_mat[0];
		m_mat[1] = m.m_mat[1];
		m_mat[2] = m.m_mat[2];
		m_mat[3] = m.m_mat[3];
		m_mat[4] = m.m_mat[4];
		m_mat[5] = m.m_mat[5];

		return *this;
	}

	inline Mat32& Mat32::operator =(const Mat32 && m) {
		m_mat[0] = std::move(m.m_mat[0]);
		m_mat[1] = std::move(m.m_mat[1]);
		m_mat[2] = std::move(m.m_mat[2]);
		m_mat[3] = std::move(m.m_mat[3]);
		m_mat[4] = std::move(m.m_mat[4]);
		m_mat[5] = std::move(m.m_mat[5]);

		return *this;
	}

	inline bool Mat32::operator ==(const Mat32& m) {
		return !(
		           m_mat[0] != m.m_mat[0] || m_mat[2] != m.m_mat[2] || m_mat[4] != m.m_mat[4] ||
		           m_mat[1] != m.m_mat[1] || m_mat[3] != m.m_mat[3] || m_mat[5] != m.m_mat[5]
		       );
	}

	inline bool Mat32::operator !=(const Mat32& m) {
		return (
		           m_mat[0] != m.m_mat[0] || m_mat[2] != m.m_mat[2] || m_mat[4] != m.m_mat[4] ||
		           m_mat[1] != m.m_mat[1] || m_mat[3] != m.m_mat[3] || m_mat[5] != m.m_mat[5]
		       );
	}

	inline std::string Mat32::ToString(int32 p) {

		return (
		           "Mat32[\n"
		           "  " + util.ToString(m_mat[0], p) + ", " + util.ToString(m_mat[2], p) + ", " + util.ToString(m_mat[4], p) + ",\n" +
		           "  " + util.ToString(m_mat[1], p) + ", " + util.ToString(m_mat[3], p) + ", " + util.ToString(m_mat[5], p) + ",\n" +
		           "]"
		       );
	}
}

#endif