#ifndef ODIN_MAT3_CPP
#define ODIN_MAT3_CPP

namespace Odin {

	template <typename Type> inline Mat3<Type>::Mat3(void) {
		m_mat[0] = static_cast<Type>(1);
		m_mat[3] = static_cast<Type>(0);
		m_mat[6] = static_cast<Type>(0);
		m_mat[1] = static_cast<Type>(0);
		m_mat[4] = static_cast<Type>(1);
		m_mat[7] = static_cast<Type>(0);
		m_mat[2] = static_cast<Type>(0);
		m_mat[5] = static_cast<Type>(0);
		m_mat[8] = static_cast<Type>(1);
	}

	template <typename Type> inline Mat3<Type>::Mat3(
	    Type m11, Type m21, Type m31,
	    Type m12, Type m22, Type m32,
	    Type m13, Type m23, Type m33
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

	template <typename Type> inline Mat3<Type>::Mat3(const Mat3<Type>& m) {
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

	template <typename Type> inline Mat3<Type>::Mat3(const Mat3<Type>&& m) {
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

	template <typename Type> inline Mat3<Type>::~Mat3(void) {}

	template <typename Type> inline Mat3<Type>& Mat3<Type>::Identity(void) {
		m_mat[0] = static_cast<Type>(1);
		m_mat[3] = static_cast<Type>(0);
		m_mat[6] = static_cast<Type>(0);
		m_mat[1] = static_cast<Type>(0);
		m_mat[4] = static_cast<Type>(1);
		m_mat[7] = static_cast<Type>(0);
		m_mat[2] = static_cast<Type>(0);
		m_mat[5] = static_cast<Type>(0);
		m_mat[8] = static_cast<Type>(1);

		return *this;
	}

	template <typename Type> inline Mat3<Type>& Mat3<Type>::SetTrace(Type x, Type y, Type z) {
		m_mat[0] = x;
		m_mat[4] = y;
		m_mat[8] = z;

		return *this;
	}

	template <typename Type> inline Mat3<Type>& Mat3<Type>::operator -(void) {
		Type m11 = m_mat[0], m12 = m_mat[3], m13 = m_mat[6],
		     m21 = m_mat[1], m22 = m_mat[4], m23 = m_mat[7],
		     m31 = m_mat[2], m32 = m_mat[5], m33 = m_mat[8],

		     m0 = m22 * m33 - m23 * m32,
		     m3 = m13 * m32 - m12 * m33,
		     m6 = m12 * m23 - m13 * m22,

		     det = m11 * m0 + m21 * m3 + m31 * m6;

		det = det != static_cast<Type>(0) ? static_cast<Type>(1) / det : static_cast<Type>(1);

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

	template <typename Type> inline Mat3<Type>& Mat3<Type>::Inverse(void) {
		Type m11 = m_mat[0], m12 = m_mat[3], m13 = m_mat[6],
		     m21 = m_mat[1], m22 = m_mat[4], m23 = m_mat[7],
		     m31 = m_mat[2], m32 = m_mat[5], m33 = m_mat[8],

		     m0 = m22 * m33 - m23 * m32,
		     m3 = m13 * m32 - m12 * m33,
		     m6 = m12 * m23 - m13 * m22,

		     det = m11 * m0 + m21 * m3 + m31 * m6;

		det = det != static_cast<Type>(0) ? static_cast<Type>(1) / det : static_cast<Type>(1);

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

	template <typename Type> inline Mat3<Type>& Mat3<Type>::Inverse(const Mat3<Type>& m) {
		Type m11 = m.m_mat[0], m12 = m.m_mat[3], m13 = m.m_mat[6],
		     m21 = m.m_mat[1], m22 = m.m_mat[4], m23 = m.m_mat[7],
		     m31 = m.m_mat[2], m32 = m. m_mat[5], m33 = m.m_mat[8],

		     m0 = m22 * m33 - m23 * m32,
		     m3 = m13 * m32 - m12 * m33,
		     m6 = m12 * m23 - m13 * m22,

		     det = m11 * m0 + m21 * m3 + m31 * m6;

		det = det != static_cast<Type>(0) ? static_cast<Type>(1) / det : static_cast<Type>(1);

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

	template <typename Type> inline Mat3<Type>& Mat3<Type>::Inverse(const Mat4<Type>& m) {
		Type m11 = m.m_mat[0], m12 = m.m_mat[4], m13 = m.m_mat[8],
		     m21 = m.m_mat[1], m22 = m.m_mat[5], m23 = m.m_mat[9],
		     m31 = m.m_mat[2], m32 = m.m_mat[6], m33 = m.m_mat[10],

		     m0 = m22 * m33 - m23 * m32,
		     m3 = m13 * m32 - m12 * m33,
		     m6 = m12 * m23 - m13 * m22,

		     det = m11 * m0 + m21 * m3 + m31 * m6;

		det = det != static_cast<Type>(0) ? static_cast<Type>(1) / det : static_cast<Type>(1);

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

	template <typename Type> inline Mat3<Type>& Mat3<Type>::Transpose(void) {
		Type tmp;

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

	template <typename Type> inline Mat3<Type>& Mat3<Type>::ExtractRotation(const Mat3<Type>& m) {
		Vec3<Type> vec;
		Type lx = Vec3LengthSq<Type>(m.m_mat[0], m.m_mat[1], m.m_mat[2]),
		     ly = Vec3LengthSq<Type>(m.m_mat[3], m.m_mat[4], m.m_mat[5]),
		     lz = Vec3LengthSq<Type>(m.m_mat[6], m.m_mat[7], m.m_mat[8]),

		     scaleX = lx > static_cast<Type>(0) ? static_cast<Type>(1) / Mathf.Sqrt(lx) : static_cast<Type>(0),
		     scaleY = ly > static_cast<Type>(0) ? static_cast<Type>(1) / Mathf.Sqrt(ly) : static_cast<Type>(0),
		     scaleZ = lz > static_cast<Type>(0) ? static_cast<Type>(1) / Mathf.Sqrt(lz) : static_cast<Type>(0);

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

	template <typename Type> inline Mat3<Type>& Mat3<Type>::ExtractRotation(const Mat4<Type>& m) {
		Vec3<Type> vec;
		Type lx = Vec3LengthSq<Type>(m[0], m[1], m[2]),
		     ly = Vec3LengthSq<Type>(m[4], m[5], m[6]),
		     lz = Vec3LengthSq<Type>(m[8], m[9], m[10]),

		     scaleX = lx > static_cast<Type>(0) ? static_cast<Type>(1) / Mathf.Sqrt(lx) : static_cast<Type>(0),
		     scaleY = ly > static_cast<Type>(0) ? static_cast<Type>(1) / Mathf.Sqrt(ly) : static_cast<Type>(0),
		     scaleZ = lz > static_cast<Type>(0) ? static_cast<Type>(1) / Mathf.Sqrt(lz) : static_cast<Type>(0);

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

	template <typename Type> inline Mat3<Type>& Mat3<Type>::ExtractRotationWithScale(const Mat4<Type>& m)  {

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

	template <typename Type> inline Mat3<Type>& Mat3<Type>::Scale(const Vec2<Type>& v) {
		Type x = v.x, y = v.y;

		m_mat[0] *= x;
		m_mat[3] *= y;
		m_mat[1] *= x;
		m_mat[4] *= y;
		m_mat[2] *= x;
		m_mat[5] *= y;

		return *this;
	}

	template <typename Type> inline Mat3<Type>& Mat3<Type>::Scale(const Vec3<Type>& v) {
		Type x = v.x, y = v.y, z = v.z;

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

	template <typename Type> inline Mat3<Type>& Mat3<Type>::Scale(const Vec4<Type>& v) {
		Type x = v.x, y = v.y, z = v.z;

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

	template <typename Type> inline Mat3<Type>& Mat3<Type>::FromQuat(const Quat<Type>& q) {
		Type x = q.x,
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

		m_mat[0] = static_cast<Type>(1) - (yy + zz);
		m_mat[3] = xy - wz;
		m_mat[6] = xz + wy;

		m_mat[1] = xy + wz;
		m_mat[4] = static_cast<Type>(1) - (xx + zz);
		m_mat[7] = yz - wx;

		m_mat[2] = xz - wy;
		m_mat[5] = yz + wx;
		m_mat[8] = static_cast<Type>(1) - (xx + yy);

		return *this;
	}

	

	template <typename Type> inline Mat3<Type>& Mat3<Type>::RotateX(Type angle) {
		Type m12 = m_mat[3],
		     m22 = m_mat[4],
		     m32 = m_mat[5],
		     m13 = m_mat[6],
		     m23 = m_mat[7],
		     m33 = m_mat[8],
		     c = Mathf.Cos(angle),
		     s = Mathf.Sin(angle);

		m_mat[3] = c * m12 + s * m13;
		m_mat[4] = c * m22 + s * m23;
		m_mat[5] = c * m32 + s * m33;

		m_mat[6] = c * m13 - s * m12;
		m_mat[7] = c * m23 - s * m22;
		m_mat[8] = c * m33 - s * m32;

		return *this;
	}

	template <typename Type> inline Mat3<Type>& Mat3<Type>::RotateY(Type angle) {
		Type m11 = m_mat[0],
		     m21 = m_mat[1],
		     m31 = m_mat[2],
		     m13 = m_mat[6],
		     m23 = m_mat[7],
		     m33 = m_mat[8],
		     c = Mathf.Cos(angle),
		     s = Mathf.Sin(angle);

		m_mat[0] = c * m11 - s * m13;
		m_mat[1] = c * m21 - s * m23;
		m_mat[2] = c * m31 - s * m33;

		m_mat[6] = c * m13 + s * m11;
		m_mat[7] = c * m23 + s * m21;
		m_mat[8] = c * m33 + s * m31;

		return *this;
	}

	template <typename Type> inline Mat3<Type>& Mat3<Type>::RotateZ(Type angle) {
		Type m11 = m_mat[0],
			 m21 = m_mat[1],
			 m31 = m_mat[2],
			 m12 = m_mat[3],
			 m22 = m_mat[4],
			 m32 = m_mat[5],
		     c = Mathf.Cos(angle),
		     s = Mathf.Sin(angle);

		m_mat[0] = c * m11 + s * m12;
		m_mat[1] = c * m21 + s * m22;
		m_mat[2] = c * m31 + s * m32;

		m_mat[3] = c * m12 - s * m11;
        m_mat[4] = c * m22 - s * m21;
        m_mat[5] = c * m32 - s * m31;

		return *this;
	}

	template <typename Type> inline Mat3<Type>& Mat3<Type>::Rotate(Type x, Type y, Type z) {
		
		RotateZ(z);
		RotateX(x);
		RotateY(y);

		return *this;
	}

	template <typename Type> inline Type Mat3<Type>::operator [] (int32 i) const {
		return m_mat[i];
	}

	template <typename Type> inline Type& Mat3<Type>::operator [] (int32 i) {
		return m_mat[i];
	}

	template <typename Type> inline Mat3<Type> Mat3<Type>::operator *(const Mat3<Type>& m) {
		Type a11 = m_mat[0], a12 = m_mat[3], a13 = m_mat[6],
		     a21 = m_mat[1], a22 = m_mat[4], a23 = m_mat[7],
		     a31 = m_mat[2], a32 = m_mat[5], a33 = m_mat[8],

		     b11 = m.m_mat[0], b12 = m.m_mat[3], b13 = m.m_mat[6],
		     b21 = m.m_mat[1], b22 = m.m_mat[4], b23 = m.m_mat[7],
		     b31 = m.m_mat[2], b32 = m.m_mat[5], b33 = m.m_mat[8];

		return Mat3<Type>(
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

	template <typename Type> inline Mat3<Type>& Mat3<Type>::operator *=(const Mat3<Type>& m) {
		Type a11 = m_mat[0], a12 = m_mat[3], a13 = m_mat[6],
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

		return *this;
	}

	template <typename Type> inline Mat3<Type>& Mat3<Type>::operator *=(Type s) {
		m_mat[0] *= s;
		m_mat[1] *= s;
		m_mat[2] *= s;
		m_mat[3] *= s;
		m_mat[4] *= s;
		m_mat[5] *= s;
		m_mat[6] *= s;
		m_mat[7] *= s;
		m_mat[8] *= s;

		return *this;
	}

	template <typename Type> inline Mat3<Type>& Mat3<Type>::operator /=(Type s) {
		Type d = s != static_cast<Type>(0) ? static_cast<Type>(1) / s : static_cast<Type>(0);

		m_mat[0] *= d;
		m_mat[1] *= d;
		m_mat[2] *= d;
		m_mat[3] *= d;
		m_mat[4] *= d;
		m_mat[5] *= d;
		m_mat[6] *= d;
		m_mat[7] *= d;
		m_mat[8] *= d;

		return *this;
	}

	template <typename Type> inline Mat3<Type>& Mat3<Type>::operator =(const Mat3<Type>& m) {

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

	template <typename Type> inline Mat3<Type>& Mat3<Type>::operator =(const Mat3<Type> && m) {

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

	template <typename Type> inline bool Mat3<Type>::operator ==(const Mat3<Type>& m) {
		return !(
		           m_mat[0] != m.m_mat[0] || m_mat[3] != m.m_mat[3] || m_mat[6] != m.m_mat[6] ||
		           m_mat[1] != m.m_mat[1] || m_mat[4] != m.m_mat[4] || m_mat[7] != m.m_mat[7] ||
		           m_mat[2] != m.m_mat[2] || m_mat[5] != m.m_mat[5] || m_mat[8] != m.m_mat[8]
		       );
	}

	template <typename Type> inline bool Mat3<Type>::operator !=(const Mat3<Type>& m) {
		return (
		           m_mat[0] != m.m_mat[0] || m_mat[3] != m.m_mat[3] || m_mat[6] != m.m_mat[6] ||
		           m_mat[1] != m.m_mat[1] || m_mat[4] != m.m_mat[4] || m_mat[7] != m.m_mat[7] ||
		           m_mat[2] != m.m_mat[2] || m_mat[5] != m.m_mat[5] || m_mat[8] != m.m_mat[8]
		       );
	}

	template <typename Type> inline std::string Mat3<Type>::ToString(int32 p) {

		return (
		           "Mat3[\n"
		           "  " + Odin::ToString(m_mat[0], p) + ", " + Odin::ToString(m_mat[3], p) + ", " + Odin::ToString(m_mat[6], p) + ",\n" +
		           "  " + Odin::ToString(m_mat[1], p) + ", " + Odin::ToString(m_mat[4], p) + ", " + Odin::ToString(m_mat[7], p) + ",\n" +
		           "  " + Odin::ToString(m_mat[2], p) + ", " + Odin::ToString(m_mat[5], p) + ", " + Odin::ToString(m_mat[8], p) + "\n" +
		           "]"
		       );
	}

	template <typename Type> inline Mat3<Type>& Mat3Inverse(const Mat3<Type>& a, Mat3<Type>& out) {
		Type m11 = a.m_mat[0], m12 = a.m_mat[3], m13 = a.m_mat[6],
		     m21 = a.m_mat[1], m22 = a.m_mat[4], m23 = a.m_mat[7],
		     m31 = a.m_mat[2], m32 = a.m_mat[5], m33 = a.m_mat[8],

		     m0 = m22 * m33 - m23 * m32,
		     m3 = m13 * m32 - m12 * m33,
		     m6 = m12 * m23 - m13 * m22,

		     det = m11 * m0 + m21 * m3 + m31 * m6;

		if (det == static_cast<Type>(0)) {
			return out.identity();
		}
		det = static_cast<Type>(1) / det;

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

	template <typename Type> inline Mat3<Type>& Mat3InverseMat4(const Mat4<Type>& a, Mat3<Type>& out) {
		Type m11 = a.m_mat[0], m12 = a.m_mat[4], m13 = a.m_mat[8],
		     m21 = a.m_mat[1], m22 = a.m_mat[5], m23 = a.m_mat[9],
		     m31 = a.m_mat[2], m32 = a.m_mat[6], m33 = a.m_mat[10],

		     m0 = m22 * m33 - m23 * m32,
		     m3 = m13 * m32 - m12 * m33,
		     m6 = m12 * m23 - m13 * m22,

		     det = m11 * m0 + m21 * m3 + m31 * m6;

		det = det != static_cast<Type>(0) ? static_cast<Type>(1) / det : static_cast<Type>(1);

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

	template <typename Type> inline Mat3<Type>& Mat3InverseMat43(const Mat43<Type>& a, Mat3<Type>& out) {
		Type m11 = a.m_mat[0], m12 = a.m_mat[3], m13 = a.m_mat[6],
		     m21 = a.m_mat[1], m22 = a.m_mat[4], m23 = a.m_mat[7],
		     m31 = a.m_mat[2], m32 = a.m_mat[5], m33 = a.m_mat[8],

		     m0 = m22 * m33 - m23 * m32,
		     m3 = m13 * m32 - m12 * m33,
		     m6 = m12 * m23 - m13 * m22,

		     det = m11 * m0 + m21 * m3 + m31 * m6;

		det = det != static_cast<Type>(0) ? static_cast<Type>(1) / det : static_cast<Type>(1);

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

	template <typename Type> inline Mat3<Type>& Mat3Mul(const Mat3<Type>& a, const Mat3<Type>& b, Mat3<Type>& out) {
		Type a11 = a.m_mat[0], a12 = a.m_mat[3], a13 = a.m_mat[6],
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