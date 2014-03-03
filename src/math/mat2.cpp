#ifndef _ODIN_MAT2_CPP
#define _ODIN_MAT2_CPP

namespace Odin {

	inline Mat2::Mat2(void) {
		m_mat[0] = 1.0f;
		m_mat[2] = 0.0f;
		m_mat[1] = 0.0f;
		m_mat[3] = 1.0f;
	}

	inline Mat2::Mat2(float32 m11, float32 m21, float32 m12, float32 m22) {
		m_mat[0] = m11;
		m_mat[2] = m21;
		m_mat[1] = m12;
		m_mat[3] = m22;
	}

	inline Mat2::Mat2(const Mat2& m) {
		m_mat[0] = m.m_mat[0];
		m_mat[2] = m.m_mat[2];
		m_mat[1] = m.m_mat[1];
		m_mat[3] = m.m_mat[3];
	}

	inline Mat2::Mat2(const Mat2&& m) {
		m_mat[0] = std::move(m.m_mat[0]);
		m_mat[2] = std::move(m.m_mat[2]);
		m_mat[1] = std::move(m.m_mat[1]);
		m_mat[3] = std::move(m.m_mat[3]);
	}

	inline Mat2::~Mat2(void) {}

	inline Mat2& Mat2::Identity(void) {
		m_mat[0] = 1.0f;
		m_mat[1] = 0.0f;
		m_mat[1] = 0.0f;
		m_mat[3] = 1.0f;

		return *this;
	}

	inline Mat2& Mat2::SetTrace(float32 x, float32 y) {
		m_mat[0] = x;
		m_mat[3] = y;

		return *this;
	}

	inline Mat2& Mat2::operator -() {
		float32 a11 = m_mat[0],
		        a12 = m_mat[1],
		        a21 = m_mat[2],
		        a22 = m_mat[3],
		        det = a11 * a22 - a21 * a12;

		if (det == 0.0f) {
			return Identity();
		}

		det = 1 / det;

		m_mat[0] = a22 * det;
		m_mat[2] = -a12 * det;
		m_mat[1] = -a21 * det;
		m_mat[3] = a11 * det;

		return *this;
	}

	inline Mat2& Mat2::Inverse(void) {
		float32 a11 = m_mat[0],
		        a12 = m_mat[1],
		        a21 = m_mat[2],
		        a22 = m_mat[3],
		        det = a11 * a22 - a21 * a12;

		if (det == 0.0f) {
			return Identity();
		}

		det = 1.0f / det;

		m_mat[0] = a22 * det;
		m_mat[2] = -a12 * det;
		m_mat[1] = -a21 * det;
		m_mat[3] = a11 * det;

		return *this;
	}

	inline Mat2& Mat2::Inverse(const Mat2& m) {
		float32 a11 = m.m_mat[0],
		        a12 = m.m_mat[1],
		        a21 = m.m_mat[2],
		        a22 = m.m_mat[3],
		        det = a11 * a22 - a21 * a12;

		if (det == 0.0f) {
			return Identity();
		}

		det = 1.0f / det;

		m_mat[0] = a22 * det;
		m_mat[2] = -a12 * det;
		m_mat[1] = -a21 * det;
		m_mat[3] = a11 * det;

		return *this;
	}

	inline Mat2& Mat2::Transpose(void) {
		float32 tmp;

		tmp = m_mat[1];
		m_mat[1] = m_mat[2];
		m_mat[2] = tmp;

		return *this;
	}

	inline Mat2& Mat2::SetRotation(float32 a) {
		float32 s = sinf(a), c = cosf(a);

		m_mat[0] = c;
		m_mat[2] = -s;
		m_mat[1] = s;
		m_mat[3] = c;

		return *this;
	}

	inline float32 Mat2::GetRotation(void) {
		return atan2f(m_mat[2], m_mat[0]);
	}

	inline Mat2& Mat2::Rotate(float32 a) {
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

	inline float32 Mat2::operator [] (int32 i) const {
		return m_mat[i];
	}

	inline float32& Mat2::operator [] (int32 i) {
		return m_mat[i];
	}

	inline Mat2 Mat2::operator *(const Mat2& m) {
		float32 a11 = m_mat[0],
		        a12 = m_mat[1],
		        a21 = m_mat[2],
		        a22 = m_mat[3],

		        b11 = m.m_mat[0],
		        b12 = m.m_mat[1],
		        b21 = m.m_mat[2],
		        b22 = m.m_mat[3];

		return Mat2(
		           a11 * b11 + a12 * b21,
		           a21 * b11 + a22 * b21,

		           a11 * b12 + a12 * b22,
		           a21 * b12 + a22 * b22
		       );
	}

	inline void Mat2::operator *=(const Mat2& m) {
		float32 a11 = m_mat[0],
		        a12 = m_mat[1],
		        a21 = m_mat[2],
		        a22 = m_mat[3],

		        b11 = m.m_mat[0],
		        b12 = m.m_mat[1],
		        b21 = m.m_mat[2],
		        b22 = m.m_mat[3];

		m_mat[0] = a11 * b11 + a12 * b21;
		m_mat[2] = a11 * b12 + a12 * b22;
		m_mat[1] = a21 * b11 + a22 * b21;
		m_mat[3] = a21 * b12 + a22 * b22;
	}

	inline void Mat2::operator *=(float32 s) {
		m_mat[0] *= s;
		m_mat[1] *= s;
		m_mat[2] *= s;
		m_mat[3] *= s;
	}

	inline void Mat2::operator /=(float32 s) {
		float32 d = s != 0.0f ? 1.0f / s : 0.0f;

		m_mat[0] *= d;
		m_mat[1] *= d;
		m_mat[2] *= d;
		m_mat[3] *= d;
	}

	inline Mat2& Mat2::operator =(const Mat2& m) {

		m_mat[0] = m.m_mat[0];
		m_mat[1] = m.m_mat[1];
		m_mat[2] = m.m_mat[2];
		m_mat[3] = m.m_mat[3];

		return *this;
	}

	inline Mat2& Mat2::operator =(const Mat2 && m) {

		m_mat[0] = std::move(m.m_mat[0]);
		m_mat[1] = std::move(m.m_mat[1]);
		m_mat[2] = std::move(m.m_mat[2]);
		m_mat[3] = std::move(m.m_mat[3]);

		return *this;
	}

	inline bool Mat2::operator ==(const Mat2& m) {
		return !(
		           m_mat[0] != m.m_mat[0] || m_mat[2] != m.m_mat[2] ||
		           m_mat[1] != m.m_mat[1] || m_mat[3] != m.m_mat[3]
		       );
	}

	inline bool Mat2::operator !=(const Mat2& m) {
		return (
		           m_mat[0] != m.m_mat[0] || m_mat[2] != m.m_mat[2] ||
		           m_mat[1] != m.m_mat[1] || m_mat[3] != m.m_mat[3]
		       );
	}

	inline std::string Mat2::ToString(int32 p) {

		return (
		           "Mat2[\n"
		           "  " + util.ToString(m_mat[0], p) + ", " + util.ToString(m_mat[2], p) + ",\n" +
		           "  " + util.ToString(m_mat[1], p) + ", " + util.ToString(m_mat[3], p) + "\n" +
		           "]"
		       );
	}
}

#endif