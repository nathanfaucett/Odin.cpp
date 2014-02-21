#ifndef ODIN_MAT32_CPP
#define ODIN_MAT32_CPP

namespace Odin {

	inline Mat32::Mat32(void) {
		mat[0] = 1;
		mat[2] = 0;
		mat[4] = 0;
		mat[1] = 0;
		mat[3] = 1;
		mat[5] = 0;
	}

	inline Mat32::Mat32(const float m11, const float m12, const float m21, const float m22, const float m31, const float m32) {
		mat[0] = m11;
		mat[2] = m21;
		mat[4] = m31;
		mat[1] = m12;
		mat[3] = m22;
		mat[5] = m32;
	}

	inline Mat32::Mat32(const Mat2& m) {
		mat[0] = m[0];
		mat[2] = m[1];
		mat[4] = 0;
		mat[1] = m[2];
		mat[3] = m[3];
		mat[5] = 0;
	}

	inline Mat32::Mat32(const Mat2& m, const Vec2& v) {
		mat[0] = m[0];
		mat[2] = m[2];
		mat[4] = v.x;
		mat[1] = m[1];
		mat[3] = m[3];
		mat[5] = v.y;
	}

	inline Mat32::Mat32(const Vec2& v, const float angle) {
		float c = std::cos(angle),
		      s = std::sin(angle);

		mat[0] = c;
		mat[2] = -s;
		mat[4] = v.x;
		mat[1] = s;
		mat[3] = c;
		mat[5] = v.y;
	}

	inline Mat32::Mat32(const Mat32& m) {
		mat[0] = m.mat[0];
		mat[2] = m.mat[2];
		mat[4] = m.mat[4];
		mat[1] = m.mat[1];
		mat[3] = m.mat[3];
		mat[5] = m.mat[5];
	}

	inline Mat32::~Mat32(void) {}

	inline Mat32& Mat32::Identity() {
		mat[0] = 1;
		mat[2] = 0;
		mat[4] = 0;
		mat[1] = 0;
		mat[3] = 1;
		mat[5] = 0;

		return *this;
	}

	inline Mat32& Mat32::SetTrace(const float x, const float y) {
		mat[0] = x;
		mat[3] = y;

		return *this;
	}

	inline Mat32& Mat32::operator -() {
		float m11 = mat[0],
		      m12 = mat[1],
		      m21 = mat[2],
		      m22 = mat[3],
		      m31 = mat[4],
		      m32 = mat[5],

		      det = m11 * m22 - m12 * m21;

		if (det == 0) {
			return Identity();
		}

		det = 1 / det;

		mat[0] = m22 * det;
		mat[2] = -m12 * det;
		mat[1] = -m21 * det;
		mat[3] = m11 * det;

		mat[4] = (m12 * m32 - m22 * m31) * det;
		mat[5] = (m21 * m31 - m11 * m32) * det;

		return *this;
	}

	inline Mat32& Mat32::Inverse() {
		float m11 = mat[0],
		      m12 = mat[1],
		      m21 = mat[2],
		      m22 = mat[3],
		      m31 = mat[4],
		      m32 = mat[5],

		      det = m11 * m22 - m12 * m21;

		if (det == 0) {
			return Identity();
		}

		det = 1 / det;

		mat[0] = m22 * det;
		mat[2] = -m12 * det;
		mat[1] = -m21 * det;
		mat[3] = m11 * det;

		mat[4] = (m12 * m32 - m22 * m31) * det;
		mat[5] = (m21 * m31 - m11 * m32) * det;

		return *this;
	}

	inline Mat32& Mat32::Inverse(const Mat32& m) {
		float m11 = m.mat[0],
		      m12 = m.mat[1],
		      m21 = m.mat[2],
		      m22 = m.mat[3],
		      m31 = m.mat[4],
		      m32 = m.mat[5],

		      det = m11 * m22 - m12 * m21;

		if (det == 0) {
			return Identity();
		}

		det = 1 / det;

		mat[0] = m22 * det;
		mat[2] = -m12 * det;
		mat[1] = -m21 * det;
		mat[3] = m11 * det;

		mat[4] = (m12 * m32 - m22 * m31) * det;
		mat[5] = (m21 * m31 - m11 * m32) * det;

		return *this;
	}

	inline Mat32& Mat32::Compose(const Vec2& position, const Vec2& scale, const float angle) {
		float sx = scale.x,
		      sy = scale.y,
		      c = std::cos(angle),
		      s = std::sin(angle);

		mat[0] = c * sx;
		mat[1] = s * sx;
		mat[2] = -s * sy;
		mat[3] = c * sy;

		mat[4] = position.x;
		mat[5] = position.y;

		return *this;
	}

	inline Mat32& Mat32::Decompose(Vec2& position, Vec2& scale, float& angle) {
		float m11 = mat[0],
		      m12 = mat[1],
		      sx = scale.Set(m11, m12).Length(),
		      sy = scale.Set(mat[2], mat[3]).Length();

		position.x = mat[4];
		position.y = mat[5];

		scale.x = sx;
		scale.y = sy;

		angle = std::atan2(m12, m11);

		return *this;
	}

	inline Mat32& Mat32::SetRotation(const float a) {
		float s = std::sin(a), c = std::cos(a);

		mat[0] = c;
		mat[2] = -s;
		mat[1] = s;
		mat[3] = c;

		return *this;
	}

	inline float Mat32::GetRotation() {
		return std::atan2(mat[2], mat[0]);
	}

	inline Mat32& Mat32::SetPosition(const Vec2& v) {

		mat[4] = v.x;
		mat[5] = v.y;

		return *this;
	}

	inline Vec2 Mat32::GetPosition() {

		return Vec2(mat[4], mat[5]);
	}

	inline Mat32& Mat32::Rotate(const float a) {
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

	inline const float Mat32::operator [] (int i) const {
		return mat[i];
	}

	inline float& Mat32::operator [] (int i) {
		return mat[i];
	}

	inline Mat32 Mat32::operator *(const Mat32& m) {
		float a11 = mat[0],
		      a12 = mat[1],
		      a13 = mat[2],
		      a21 = mat[3],
		      a22 = mat[4],
		      a23 = mat[5],

		      b11 = m.mat[0],
		      b12 = m.mat[1],
		      b13 = m.mat[2],
		      b21 = m.mat[3],
		      b22 = m.mat[4],
		      b23 = m.mat[5];

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
		float a11 = mat[0],
		      a12 = mat[1],
		      a13 = mat[2],
		      a21 = mat[3],
		      a22 = mat[4],
		      a23 = mat[5],

		      b11 = m.mat[0],
		      b12 = m.mat[1],
		      b13 = m.mat[2],
		      b21 = m.mat[3],
		      b22 = m.mat[4],
		      b23 = m.mat[5];

		mat[0] = a11 * b11 + a21 * b12;
		mat[1] = a12 * b11 + a22 * b12;

		mat[3] = a11 * b21 + a21 * b22;
		mat[4] = a12 * b21 + a22 * b22;

		mat[2] = a11 * b13 + a12 * b23 + a13;
		mat[5] = a21 * b13 + a22 * b23 + a23;
	}

	inline Mat32 Mat32::operator *=(const float s) {
		mat[0] *= s;
		mat[1] *= s;
		mat[2] *= s;
		mat[3] *= s;
		mat[4] *= s;
		mat[5] *= s;
	}

	inline Mat32 Mat32::operator /=(const float s) {
		float d = s != 0 ? 1 / s : 0;

		mat[0] *= d;
		mat[1] *= d;
		mat[2] *= d;
		mat[3] *= d;
		mat[4] *= d;
		mat[5] *= d;
	}

	inline Mat32 Mat32::operator =(const Mat32& m) {
		mat[0] = m.mat[0];
		mat[1] = m.mat[1];
		mat[2] = m.mat[2];
		mat[3] = m.mat[3];
		mat[4] = m.mat[4];
		mat[5] = m.mat[5];
	}

	inline bool Mat32::operator ==(const Mat32& m) {
		return !(
		           mat[0] != m.mat[0] || mat[2] != m.mat[2] || mat[4] != m.mat[4] ||
		           mat[1] != m.mat[1] || mat[3] != m.mat[3] || mat[5] != m.mat[5]
		       );
	}

	inline bool Mat32::operator !=(const Mat32& m) {
		return (
		           mat[0] != m.mat[0] || mat[2] != m.mat[2] || mat[4] != m.mat[4] ||
		           mat[1] != m.mat[1] || mat[3] != m.mat[3] || mat[5] != m.mat[5]
		       );
	}

	inline std::string Mat32::ToString(int p) {

		return (
		           "Mat32[\n"
		           "  " + util.ToString(mat[0], p) + ", " + util.ToString(mat[2], p) + ", " + util.ToString(mat[4], p) + ",\n" +
		           "  " + util.ToString(mat[1], p) + ", " + util.ToString(mat[3], p) + ", " + util.ToString(mat[5], p) + ",\n" +
		           "]"
		       );
	}
}

#endif