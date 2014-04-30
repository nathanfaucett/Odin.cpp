#ifndef ODIN_MAT32_CPP
#define ODIN_MAT32_CPP

namespace Odin {

	template <typename Type> inline Mat32<Type>::Mat32(void) {
		m_mat[0] = static_cast<Type>(1);
		m_mat[2] = static_cast<Type>(0);
		m_mat[4] = static_cast<Type>(0);
		m_mat[1] = static_cast<Type>(0);
		m_mat[3] = static_cast<Type>(1);
		m_mat[5] = static_cast<Type>(0);
	}

	template <typename Type> inline Mat32<Type>::Mat32(Type m11, Type m21, Type m31, Type m12, Type m22, Type m32) {
		m_mat[0] = m11;
		m_mat[2] = m21;
		m_mat[4] = m31;
		m_mat[1] = m12;
		m_mat[3] = m22;
		m_mat[5] = m32;
	}

	template <typename Type> inline Mat32<Type>::Mat32(const Mat2<Type>& m) {
		m_mat[0] = m[0];
		m_mat[2] = m[1];
		m_mat[4] = static_cast<Type>(0);
		m_mat[1] = m[2];
		m_mat[3] = m[3];
		m_mat[5] = static_cast<Type>(0);
	}

	template <typename Type> inline Mat32<Type>::Mat32(const Mat2<Type>& m, const Vec2<Type>& v) {
		m_mat[0] = m[0];
		m_mat[2] = m[2];
		m_mat[4] = v.x;
		m_mat[1] = m[1];
		m_mat[3] = m[3];
		m_mat[5] = v.y;
	}

	template <typename Type> inline Mat32<Type>::Mat32(const Vec2<Type>& v, Type angle) {
		Type c = Mathf.Cos(angle),
		     s = Mathf.Sin(angle);

		m_mat[0] = c;
		m_mat[2] = -s;
		m_mat[4] = v.x;
		m_mat[1] = s;
		m_mat[3] = c;
		m_mat[5] = v.y;
	}

	template <typename Type> inline Mat32<Type>::Mat32(const Mat32<Type>& m) {
		m_mat[0] = m.m_mat[0];
		m_mat[2] = m.m_mat[2];
		m_mat[4] = m.m_mat[4];
		m_mat[1] = m.m_mat[1];
		m_mat[3] = m.m_mat[3];
		m_mat[5] = m.m_mat[5];
	}

	template <typename Type> inline Mat32<Type>::Mat32(const Mat32<Type>&& m) {
		m_mat[0] = std::move(m.m_mat[0]);
		m_mat[1] = std::move(m.m_mat[1]);
		m_mat[2] = std::move(m.m_mat[2]);
		m_mat[3] = std::move(m.m_mat[3]);
		m_mat[4] = std::move(m.m_mat[4]);
		m_mat[5] = std::move(m.m_mat[5]);
	}

	template <typename Type> inline Mat32<Type>::~Mat32(void) {}

	template <typename Type> inline Mat32<Type>& Mat32<Type>::Identity(void) {
		m_mat[0] = static_cast<Type>(1);
		m_mat[2] = static_cast<Type>(0);
		m_mat[4] = static_cast<Type>(0);
		m_mat[1] = static_cast<Type>(0);
		m_mat[3] = static_cast<Type>(1);
		m_mat[5] = static_cast<Type>(0);

		return *this;
	}

	template <typename Type> inline Mat32<Type>& Mat32<Type>::SetTrace(Type x, Type y) {
		m_mat[0] = x;
		m_mat[3] = y;

		return *this;
	}

	template <typename Type> inline Mat32<Type>& Mat32<Type>::operator -() {
		Type m11 = m_mat[0],
		     m12 = m_mat[1],
		     m21 = m_mat[2],
		     m22 = m_mat[3],
		     m31 = m_mat[4],
		     m32 = m_mat[5],

		     det = m11 * m22 - m12 * m21;

		if (det == static_cast<Type>(0)) {
			return Identity();
		}

		det = static_cast<Type>(1) / det;

		m_mat[0] = m22 * det;
		m_mat[2] = -m12 * det;
		m_mat[1] = -m21 * det;
		m_mat[3] = m11 * det;

		m_mat[4] = (m12 * m32 - m22 * m31) * det;
		m_mat[5] = (m21 * m31 - m11 * m32) * det;

		return *this;
	}

	template <typename Type> inline Mat32<Type>& Mat32<Type>::Inverse(void) {
		Type m11 = m_mat[0],
		     m12 = m_mat[1],
		     m21 = m_mat[2],
		     m22 = m_mat[3],
		     m31 = m_mat[4],
		     m32 = m_mat[5],

		     det = m11 * m22 - m12 * m21;

		if (det == static_cast<Type>(0)) {
			return Identity();
		}

		det = static_cast<Type>(1) / det;

		m_mat[0] = m22 * det;
		m_mat[2] = -m12 * det;
		m_mat[1] = -m21 * det;
		m_mat[3] = m11 * det;

		m_mat[4] = (m12 * m32 - m22 * m31) * det;
		m_mat[5] = (m21 * m31 - m11 * m32) * det;

		return *this;
	}

	template <typename Type> inline Mat32<Type>& Mat32<Type>::Inverse(const Mat32<Type>& m) {
		Type m11 = m.m_mat[0],
		     m12 = m.m_mat[1],
		     m21 = m.m_mat[2],
		     m22 = m.m_mat[3],
		     m31 = m.m_mat[4],
		     m32 = m.m_mat[5],

		     det = m11 * m22 - m12 * m21;

		if (det == static_cast<Type>(0)) {
			return Identity();
		}

		det = static_cast<Type>(1) / det;

		m_mat[0] = m22 * det;
		m_mat[2] = -m12 * det;
		m_mat[1] = -m21 * det;
		m_mat[3] = m11 * det;

		m_mat[4] = (m12 * m32 - m22 * m31) * det;
		m_mat[5] = (m21 * m31 - m11 * m32) * det;

		return *this;
	}

	template <typename Type> inline Mat32<Type>& Mat32<Type>::Transpose(void) {
		Type tmp;

		tmp = m_mat[1];
		m_mat[1] = m_mat[2];
		m_mat[2] = tmp;

		return *this;
	}

	template <typename Type> inline Mat32<Type>& Mat32<Type>::Compose(const Vec2<Type>& position, const Vec2<Type>& scale, Type angle) {
		Type sx = scale.x,
		     sy = scale.y,
		     c = Mathf.Cos(angle),
		     s = Mathf.Sin(angle);

		m_mat[0] = c * sx;
		m_mat[1] = s * sx;
		m_mat[2] = -s * sy;
		m_mat[3] = c * sy;

		m_mat[4] = position.x;
		m_mat[5] = position.y;

		return *this;
	}

	template <typename Type> inline Mat32<Type>& Mat32<Type>::Compose(const Vec2<Type>& position, Type angle) {
		Type c = Mathf.Cos(angle),
		     s = Mathf.Sin(angle);

		m_mat[0] = c;
		m_mat[1] = s;
		m_mat[2] = -s;
		m_mat[3] = c;

		m_mat[4] = position.x;
		m_mat[5] = position.y;

		return *this;
	}

	template <typename Type> inline Mat32<Type>& Mat32<Type>::Decompose(Vec2<Type>& position, Vec2<Type>& scale, Type& angle) {
		Type m11 = m_mat[0],
		     m12 = m_mat[1],
		     sx = scale.Set(m11, m12).Length(),
		     sy = scale.Set(m_mat[2], m_mat[3]).Length();

		position.x = m_mat[4];
		position.y = m_mat[5];

		scale.x = sx;
		scale.y = sy;

		angle = Mathf.Atan2(m12, m11);

		return *this;
	}

	template <typename Type> inline Mat32<Type>& Mat32<Type>::SetRotation(Type a) {
		Type s = Mathf.Sin(a), c = Mathf.Cos(a);

		m_mat[0] = c;
		m_mat[2] = -s;
		m_mat[1] = s;
		m_mat[3] = c;

		return *this;
	}

	template <typename Type> inline Type Mat32<Type>::GetRotation(void) {
		return Mathf.Atan2(m_mat[2], m_mat[0]);
	}
	template <typename Type> inline Type& Mat32<Type>::GetRotation(Type& rotation) {
		rotation = Mathf.Atan2(m_mat[2], m_mat[0]);
		
		return rotation;
	}

	template <typename Type> inline Mat32<Type>& Mat32<Type>::SetPosition(const Vec2<Type>& v) {

		m_mat[4] = v.x;
		m_mat[5] = v.y;

		return *this;
	}

	template <typename Type> inline Vec2<Type> Mat32<Type>::GetPosition(void) {
		return Vec2<Type>(m_mat[4], m_mat[5]);
	}
	template <typename Type> inline Vec2<Type>& Mat32<Type>::GetPosition(Vec2<Type>& position) {
		position.x = m_mat[4];
		position.y = m_mat[5];
		
		return position;
	}

	template <typename Type> inline Mat32<Type>& Mat32<Type>::Rotate(Type a) {
		Type a11 = m_mat[0],
		     a12 = m_mat[1],
		     a21 = m_mat[2],
		     a22 = m_mat[3],
		     s = Mathf.Sin(a), c = Mathf.Cos(a);

		m_mat[0] = a11 * c + a21 * s;
		m_mat[2] = a12 * c + a22 * s;
		m_mat[1] = a11 * -s + a21 * c;
		m_mat[3] = a12 * -s + a22 * c;

		return *this;
	}

	template <typename Type> inline Mat32<Type>& Mat32<Type>::Orthographic(Type left, Type right, Type top, Type bottom) {
		Type w = right - left,
		     h = top - bottom,

		     x = (right + left) / w,
		     y = (top + bottom) / h;

		m_mat[0] = static_cast<Type>(2) / w;
		m_mat[1] = static_cast<Type>(0);
		m_mat[2] = static_cast<Type>(0);
		m_mat[3] = static_cast<Type>(2) / h;
		m_mat[4] = -x;
		m_mat[5] = -y;

		return *this;
	}

	template <typename Type> inline Type Mat32<Type>::operator [] (int32 i) const {
		return m_mat[i];
	}

	template <typename Type> inline Type& Mat32<Type>::operator [] (int32 i) {
		return m_mat[i];
	}

	template <typename Type> inline Mat32<Type> Mat32<Type>::operator *(const Mat32<Type>& m) {
		Type a11 = m_mat[0],
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

		return Mat32<Type>(
		           a11 * b11 + a21 * b12,
		           a12 * b11 + a22 * b12,
		           a11 * b13 + a12 * b23 + a13,

		           a11 * b21 + a21 * b22,
		           a12 * b21 + a22 * b22,
		           a21 * b13 + a22 * b23 + a23
		       );
	}

	template <typename Type> inline Mat32<Type>& Mat32<Type>::operator *=(const Mat32<Type>& m) {
		Type a11 = m_mat[0],
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

		return *this;
	}

	template <typename Type> inline Mat32<Type>& Mat32<Type>::operator *=(Type s) {
		m_mat[0] *= s;
		m_mat[1] *= s;
		m_mat[2] *= s;
		m_mat[3] *= s;
		m_mat[4] *= s;
		m_mat[5] *= s;

		return *this;
	}

	template <typename Type> inline Mat32<Type>& Mat32<Type>::operator /=(Type s) {
		Type d = s != static_cast<Type>(0) ? static_cast<Type>(1) / s : static_cast<Type>(0);

		m_mat[0] *= d;
		m_mat[1] *= d;
		m_mat[2] *= d;
		m_mat[3] *= d;
		m_mat[4] *= d;
		m_mat[5] *= d;

		return *this;
	}

	template <typename Type> inline Mat32<Type>& Mat32<Type>::operator =(const Mat32<Type>& m) {
		m_mat[0] = m.m_mat[0];
		m_mat[1] = m.m_mat[1];
		m_mat[2] = m.m_mat[2];
		m_mat[3] = m.m_mat[3];
		m_mat[4] = m.m_mat[4];
		m_mat[5] = m.m_mat[5];

		return *this;
	}

	template <typename Type> inline Mat32<Type>& Mat32<Type>::operator =(const Mat32<Type> && m) {
		m_mat[0] = std::move(m.m_mat[0]);
		m_mat[1] = std::move(m.m_mat[1]);
		m_mat[2] = std::move(m.m_mat[2]);
		m_mat[3] = std::move(m.m_mat[3]);
		m_mat[4] = std::move(m.m_mat[4]);
		m_mat[5] = std::move(m.m_mat[5]);

		return *this;
	}

	template <typename Type> inline bool Mat32<Type>::operator ==(const Mat32<Type>& m) {
		return !(
		           m_mat[0] != m.m_mat[0] || m_mat[2] != m.m_mat[2] || m_mat[4] != m.m_mat[4] ||
		           m_mat[1] != m.m_mat[1] || m_mat[3] != m.m_mat[3] || m_mat[5] != m.m_mat[5]
		       );
	}

	template <typename Type> inline bool Mat32<Type>::operator !=(const Mat32<Type>& m) {
		return (
		           m_mat[0] != m.m_mat[0] || m_mat[2] != m.m_mat[2] || m_mat[4] != m.m_mat[4] ||
		           m_mat[1] != m.m_mat[1] || m_mat[3] != m.m_mat[3] || m_mat[5] != m.m_mat[5]
		       );
	}

	template <typename Type> inline std::string Mat32<Type>::ToString(int32 p) {

		return (
		           "Mat32[\n"
		           "  " + Odin::ToString(m_mat[0], p) + ", " + Odin::ToString(m_mat[2], p) + ", " + Odin::ToString(m_mat[4], p) + ",\n" +
		           "  " + Odin::ToString(m_mat[1], p) + ", " + Odin::ToString(m_mat[3], p) + ", " + Odin::ToString(m_mat[5], p) + ",\n" +
		           "]"
		       );
	}

	template <typename Type> inline Mat32<Type>& Mat32Inverse(const Mat32<Type>& a, Mat32<Type>& out) {
		Type m11 = a.m_mat[0],
		     m12 = a.m_mat[1],
		     m21 = a.m_mat[2],
		     m22 = a.m_mat[3],
		     m31 = a.m_mat[4],
		     m32 = a.m_mat[5],

		     det = m11 * m22 - m12 * m21;

		if (det == static_cast<Type>(0)) {
			return out.Identity();
		}

		det = static_cast<Type>(1) / det;

		out.m_mat[0] = m22 * det;
		out.m_mat[2] = -m12 * det;
		out.m_mat[1] = -m21 * det;
		out.m_mat[3] = m11 * det;

		out.m_mat[4] = (m12 * m32 - m22 * m31) * det;
		out.m_mat[5] = (m21 * m31 - m11 * m32) * det;

		return out;
	}

	template <typename Type> inline Mat32<Type>& Mat32Mul(const Mat32<Type>& a, const Mat32<Type>& b, Mat32<Type>& out) {
		Type a11 = a.m_mat[0],
		     a12 = a.m_mat[1],
		     a13 = a.m_mat[2],
		     a21 = a.m_mat[3],
		     a22 = a.m_mat[4],
		     a23 = a.m_mat[5],

		     b11 = b.m_mat[0],
		     b12 = b.m_mat[1],
		     b13 = b.m_mat[2],
		     b21 = b.m_mat[3],
		     b22 = b.m_mat[4],
		     b23 = b.m_mat[5];

		out.m_mat[0] = a11 * b11 + a21 * b12;
		out.m_mat[1] = a12 * b11 + a22 * b12;

		out.m_mat[3] = a11 * b21 + a21 * b22;
		out.m_mat[4] = a12 * b21 + a22 * b22;

		out.m_mat[2] = a11 * b13 + a12 * b23 + a13;
		out.m_mat[5] = a21 * b13 + a22 * b23 + a23;
		
		return out;
	}
}

#endif