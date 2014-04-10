#ifndef ODIN_MAT2_CPP
#define ODIN_MAT2_CPP

namespace Odin {

	template <typename Type> inline Mat2<Type>::Mat2(void) {
		m_mat[0] = 1;
		m_mat[2] = 0;
		m_mat[1] = 0;
		m_mat[3] = 1;
	}

	template <typename Type> inline Mat2<Type>::Mat2(Type m11, Type m21, Type m12, Type m22) {
		m_mat[0] = m11;
		m_mat[2] = m21;
		m_mat[1] = m12;
		m_mat[3] = m22;
	}

	template <typename Type> inline Mat2<Type>::Mat2(const Mat2<Type>& m) {
		m_mat[0] = m.m_mat[0];
		m_mat[2] = m.m_mat[2];
		m_mat[1] = m.m_mat[1];
		m_mat[3] = m.m_mat[3];
	}

	template <typename Type> inline Mat2<Type>::Mat2(const Mat2<Type>&& m) {
		m_mat[0] = std::move(m.m_mat[0]);
		m_mat[2] = std::move(m.m_mat[2]);
		m_mat[1] = std::move(m.m_mat[1]);
		m_mat[3] = std::move(m.m_mat[3]);
	}

	template <typename Type> inline Mat2<Type>::~Mat2(void) {}

	template <typename Type> inline Mat2<Type>& Mat2<Type>::Identity(void) {
		m_mat[0] = 1;
		m_mat[1] = 0;
		m_mat[1] = 0;
		m_mat[3] = 1;

		return *this;
	}

	template <typename Type> inline Mat2<Type>& Mat2<Type>::SetTrace(Type x, Type y) {
		m_mat[0] = x;
		m_mat[3] = y;

		return *this;
	}

	template <typename Type> inline Mat2<Type>& Mat2<Type>::operator -() {
		Type a11 = m_mat[0],
		     a12 = m_mat[1],
		     a21 = m_mat[2],
		     a22 = m_mat[3],
		     det = a11 * a22 - a21 * a12;

		if (det == 0) {
			return Identity();
		}
		det = 1 / det;

		m_mat[0] = a22 * det;
		m_mat[2] = -a12 * det;
		m_mat[1] = -a21 * det;
		m_mat[3] = a11 * det;

		return *this;
	}

	template <typename Type> inline Mat2<Type>& Mat2<Type>::Inverse(void) {
		Type a11 = m_mat[0],
		     a12 = m_mat[1],
		     a21 = m_mat[2],
		     a22 = m_mat[3],
		     det = a11 * a22 - a21 * a12;

		if (det == 0) {
			return Identity();
		}
		det = 1 / det;

		m_mat[0] = a22 * det;
		m_mat[2] = -a12 * det;
		m_mat[1] = -a21 * det;
		m_mat[3] = a11 * det;

		return *this;
	}

	template <typename Type> inline Mat2<Type>& Mat2<Type>::Inverse(const Mat2<Type>& m) {
		Type a11 = m.m_mat[0],
		     a12 = m.m_mat[1],
		     a21 = m.m_mat[2],
		     a22 = m.m_mat[3],
		     det = a11 * a22 - a21 * a12;

		if (det == 0) {
			return Identity();
		}

		det = 1 / det;

		m_mat[0] = a22 * det;
		m_mat[2] = -a12 * det;
		m_mat[1] = -a21 * det;
		m_mat[3] = a11 * det;

		return *this;
	}

	template <typename Type> inline Mat2<Type>& Mat2<Type>::Transpose(void) {
		Type tmp;

		tmp = m_mat[1];
		m_mat[1] = m_mat[2];
		m_mat[2] = tmp;

		return *this;
	}

	template <typename Type> inline Mat2<Type>& Mat2<Type>::SetRotation(Type a) {
		Type s = Mathf.Sin(a), c = Mathf.Cos(a);

		m_mat[0] = c;
		m_mat[2] = -s;
		m_mat[1] = s;
		m_mat[3] = c;

		return *this;
	}

	template <typename Type> inline Type Mat2<Type>::GetRotation(void) {
		return Mathf.Atan2(m_mat[2], m_mat[0]);
	}

	template <typename Type> inline Mat2<Type>& Mat2<Type>::Rotate(Type a) {
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

	template <typename Type> inline Type Mat2<Type>::operator [] (int32 i) const {
		return m_mat[i];
	}

	template <typename Type> inline Type& Mat2<Type>::operator [] (int32 i) {
		return m_mat[i];
	}

	template <typename Type> inline Mat2<Type> Mat2<Type>::operator *(const Mat2<Type>& m) {
		Type a11 = m_mat[0],
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

	template <typename Type> inline void Mat2<Type>::operator *=(const Mat2<Type>& m) {
		Type a11 = m_mat[0],
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

	template <typename Type> inline void Mat2<Type>::operator *=(Type s) {
		m_mat[0] *= s;
		m_mat[1] *= s;
		m_mat[2] *= s;
		m_mat[3] *= s;
	}

	template <typename Type> inline void Mat2<Type>::operator /=(Type s) {
		Type d = s != 0 ? 1 / s : 0;

		m_mat[0] *= d;
		m_mat[1] *= d;
		m_mat[2] *= d;
		m_mat[3] *= d;
	}

	template <typename Type> inline Mat2<Type>& Mat2<Type>::operator =(const Mat2<Type>& m) {

		m_mat[0] = m.m_mat[0];
		m_mat[1] = m.m_mat[1];
		m_mat[2] = m.m_mat[2];
		m_mat[3] = m.m_mat[3];

		return *this;
	}

	template <typename Type> inline Mat2<Type>& Mat2<Type>::operator =(const Mat2<Type> && m) {

		m_mat[0] = std::move(m.m_mat[0]);
		m_mat[1] = std::move(m.m_mat[1]);
		m_mat[2] = std::move(m.m_mat[2]);
		m_mat[3] = std::move(m.m_mat[3]);

		return *this;
	}

	template <typename Type> inline bool Mat2<Type>::operator ==(const Mat2<Type>& m) {
		return !(
		           m_mat[0] != m.m_mat[0] || m_mat[2] != m.m_mat[2] ||
		           m_mat[1] != m.m_mat[1] || m_mat[3] != m.m_mat[3]
		       );
	}

	template <typename Type> inline bool Mat2<Type>::operator !=(const Mat2<Type>& m) {
		return (
		           m_mat[0] != m.m_mat[0] || m_mat[2] != m.m_mat[2] ||
		           m_mat[1] != m.m_mat[1] || m_mat[3] != m.m_mat[3]
		       );
	}

	template <typename Type> inline std::string Mat2<Type>::ToString(int32 p) {

		return (
		           "Mat2[\n"
		           "  " + Util.ToString(m_mat[0], p) + ", " + Util.ToString(m_mat[2], p) + ",\n" +
		           "  " + Util.ToString(m_mat[1], p) + ", " + Util.ToString(m_mat[3], p) + "\n" +
		           "]"
		       );
	}
}

#endif