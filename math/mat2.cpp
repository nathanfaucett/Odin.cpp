#ifndef ODIN_MAT2_CPP
#define ODIN_MAT2_CPP

namespace Odin {

	inline Mat2::Mat2(void) {
		mat[0] = 1;
		mat[2] = 0;
		mat[1] = 0;
		mat[3] = 1;
	}

	inline Mat2::Mat2(const float m11, const float m12, const float m21, const float m22) {
		mat[0] = m11;
		mat[2] = m21;
		mat[1] = m12;
		mat[3] = m22;
	}

	inline Mat2::Mat2(const Mat2& m) {
		mat[0] = m.mat[0];
		mat[2] = m.mat[2];
		mat[1] = m.mat[1];
		mat[3] = m.mat[3];
	}

	inline Mat2::~Mat2(void) {}

	inline Mat2& Mat2::Identity() {
		mat[0] = 1;
		mat[1] = 0;
		mat[1] = 0;
		mat[3] = 1;

		return *this;
	}

	inline Mat2& Mat2::SetTrace(const float x, const float y) {
		mat[0] = x;
		mat[3] = y;

		return *this;
	}

	inline Mat2& Mat2::operator -() {
		float a11 = mat[0],
		      a12 = mat[1],
		      a21 = mat[2],
		      a22 = mat[3],
		      det = a11 * a22 - a21 * a12;

		if (det == 0) {
			return Identity();
		}

		det = 1 / det;

		mat[0] = a22 * det;
		mat[2] = -a12 * det;
		mat[1] = -a21 * det;
		mat[3] = a11 * det;

		return *this;
	}

	inline Mat2& Mat2::Inverse() {
		float a11 = mat[0],
		      a12 = mat[1],
		      a21 = mat[2],
		      a22 = mat[3],
		      det = a11 * a22 - a21 * a12;

		if (det == 0) {
			return Identity();
		}

		det = 1 / det;

		mat[0] = a22 * det;
		mat[2] = -a12 * det;
		mat[1] = -a21 * det;
		mat[3] = a11 * det;

		return *this;
	}

	inline Mat2& Mat2::Inverse(const Mat2& m) {
		float a11 = m.mat[0],
		      a12 = m.mat[1],
		      a21 = m.mat[2],
		      a22 = m.mat[3],
		      det = a11 * a22 - a21 * a12;

		if (det == 0) {
			return Identity();
		}

		det = 1 / det;

		mat[0] = a22 * det;
		mat[2] = -a12 * det;
		mat[1] = -a21 * det;
		mat[3] = a11 * det;

		return *this;
	}

	inline Mat2& Mat2::SetRotation(const float a) {
		float s = std::sin(a), c = std::cos(a);

		mat[0] = c;
		mat[2] = -s;
		mat[1] = s;
		mat[3] = c;

		return *this;
	}

	inline float Mat2::GetRotation() {
		return std::atan2(mat[2], mat[0]);
	}

	inline Mat2& Mat2::Rotate(const float a) {
		float a11 = mat[0],
		      a12 = mat[1],
		      a21 = mat[2],
		      a22 = mat[3],
		      s = std::sin(a), c = std::cos(a);

		mat[0] = a11 * c + a21 * s;
		mat[2] = a12 * c + a22 * s;
		mat[1] = a11 * -s + a21 * c;
		mat[3] = a12 * -s + a22 * c;

		return *this;
	}

	inline const float Mat2::operator [] (int i) const {
		return mat[i];
	}

	inline float& Mat2::operator [] (int i) {
		return mat[i];
	}

	inline Mat2 Mat2::operator *(const Mat2& m) {
		float a11 = mat[0],
		      a12 = mat[1],
		      a21 = mat[2],
		      a22 = mat[3],

		      b11 = m.mat[0],
		      b12 = m.mat[1],
		      b21 = m.mat[2],
		      b22 = m.mat[3];

		return Mat2(
		           a11 * b11 + a12 * b21,
		           a21 * b11 + a22 * b21,

		           a11 * b12 + a12 * b22,
		           a21 * b12 + a22 * b22
		       );
	}

	inline void Mat2::operator *=(const Mat2& m) {
		float a11 = mat[0],
		      a12 = mat[1],
		      a21 = mat[2],
		      a22 = mat[3],

		      b11 = m.mat[0],
		      b12 = m.mat[1],
		      b21 = m.mat[2],
		      b22 = m.mat[3];

		mat[0] = a11 * b11 + a12 * b21;
		mat[2] = a11 * b12 + a12 * b22;
		mat[1] = a21 * b11 + a22 * b21;
		mat[3] = a21 * b12 + a22 * b22;
	}

	inline Mat2 Mat2::operator *=(const float s) {
		mat[0] *= s;
		mat[1] *= s;
		mat[2] *= s;
		mat[3] *= s;
	}

	inline Mat2 Mat2::operator /=(const float s) {
		float d = s != 0 ? 1 / s : 0;

		mat[0] *= d;
		mat[1] *= d;
		mat[2] *= d;
		mat[3] *= d;
	}

	inline Mat2 Mat2::operator =(const Mat2& m) {
		mat[0] = m.mat[0];
		mat[2] = m.mat[2];
		mat[1] = m.mat[1];
		mat[3] = m.mat[3];
	}

	inline bool Mat2::operator ==(const Mat2& m) {
		return !(
		           mat[0] != m.mat[0] || mat[2] != m.mat[2] ||
		           mat[1] != m.mat[1] || mat[3] != m.mat[3]
		       );
	}

	inline bool Mat2::operator !=(const Mat2& m) {
		return (
		           mat[0] != m.mat[0] || mat[2] != m.mat[2] ||
		           mat[1] != m.mat[1] || mat[3] != m.mat[3]
		       );
	}

	inline std::string Mat2::ToString(int p) {

		return (
		           "Mat2[\n"
		           "  " + util.ToString(mat[0], p) + ", " + util.ToString(mat[2], p) + ",\n" +
		           "  " + util.ToString(mat[1], p) + ", " + util.ToString(mat[3], p) + "\n" +
		           "]"
		       );
	}
}

#endif