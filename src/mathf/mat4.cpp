#ifndef ODIN_MAT4_CPP
#define ODIN_MAT4_CPP

namespace Odin {

	template <typename Type> inline Mat4<Type>::Mat4(void) {
		m_mat[0] = static_cast<Type>(1);
		m_mat[4] = static_cast<Type>(0);
		m_mat[8] = static_cast<Type>(0);
		m_mat[12] = static_cast<Type>(0);
		m_mat[1] = static_cast<Type>(0);
		m_mat[5] = static_cast<Type>(1);
		m_mat[9] = static_cast<Type>(0);
		m_mat[13] = static_cast<Type>(0);
		m_mat[2] = static_cast<Type>(0);
		m_mat[6] = static_cast<Type>(0);
		m_mat[10] = static_cast<Type>(1);
		m_mat[14] = static_cast<Type>(0);
		m_mat[3] = static_cast<Type>(0);
		m_mat[7] = static_cast<Type>(0);
		m_mat[11] = static_cast<Type>(0);
		m_mat[15] = static_cast<Type>(1);
	}

	template <typename Type> inline Mat4<Type>::Mat4(
	    Type m11, Type m21, Type m31, Type m41,
	    Type m12, Type m22, Type m32, Type m42,
	    Type m13, Type m23, Type m33, Type m43,
	    Type m14, Type m24, Type m34, Type m44
	) {
		m_mat[0] = m11;
		m_mat[4] = m21;
		m_mat[8] = m31;
		m_mat[12] = m41;
		m_mat[1] = m12;
		m_mat[5] = m22;
		m_mat[9] = m32;
		m_mat[13] = m42;
		m_mat[2] = m13;
		m_mat[6] = m23;
		m_mat[10] = m33;
		m_mat[14] = m43;
		m_mat[3] = m14;
		m_mat[7] = m24;
		m_mat[11] = m34;
		m_mat[15] = m44;
	}

	template <typename Type> inline Mat4<Type>::Mat4(const Mat4<Type>& m) {
		m_mat[0] = m.m_mat[0];
		m_mat[4] = m.m_mat[4];
		m_mat[8] = m.m_mat[8];
		m_mat[12] = m.m_mat[12];
		m_mat[1] = m.m_mat[1];
		m_mat[5] = m.m_mat[5];
		m_mat[9] = m.m_mat[9];
		m_mat[13] = m.m_mat[13];
		m_mat[2] = m.m_mat[2];
		m_mat[6] = m.m_mat[6];
		m_mat[10] = m.m_mat[10];
		m_mat[14] = m.m_mat[14];
		m_mat[3] = m.m_mat[3];
		m_mat[7] = m.m_mat[7];
		m_mat[11] = m.m_mat[11];
		m_mat[15] = m.m_mat[15];
	}

	template <typename Type> inline Mat4<Type>::Mat4(const Mat4<Type>&& m) {
		m_mat[0] = std::move(m.m_mat[0]);
		m_mat[4] = std::move(m.m_mat[4]);
		m_mat[8] = std::move(m.m_mat[8]);
		m_mat[12] = std::move(m.m_mat[12]);
		m_mat[1] = std::move(m.m_mat[1]);
		m_mat[5] = std::move(m.m_mat[5]);
		m_mat[9] = std::move(m.m_mat[9]);
		m_mat[13] = std::move(m.m_mat[13]);
		m_mat[2] = std::move(m.m_mat[2]);
		m_mat[6] = std::move(m.m_mat[6]);
		m_mat[10] = std::move(m.m_mat[10]);
		m_mat[14] = std::move(m.m_mat[14]);
		m_mat[3] = std::move(m.m_mat[3]);
		m_mat[7] = std::move(m.m_mat[7]);
		m_mat[11] = std::move(m.m_mat[11]);
		m_mat[15] = std::move(m.m_mat[15]);
	}

	template <typename Type> inline Mat4<Type>::~Mat4(void) {}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::Identity(void) {
		m_mat[0] = static_cast<Type>(1);
		m_mat[4] = static_cast<Type>(0);
		m_mat[8] = static_cast<Type>(0);
		m_mat[12] = static_cast<Type>(0);
		m_mat[1] = static_cast<Type>(0);
		m_mat[5] = static_cast<Type>(1);
		m_mat[9] = static_cast<Type>(0);
		m_mat[13] = static_cast<Type>(0);
		m_mat[2] = static_cast<Type>(0);
		m_mat[6] = static_cast<Type>(0);
		m_mat[10] = static_cast<Type>(1);
		m_mat[14] = static_cast<Type>(0);
		m_mat[3] = static_cast<Type>(0);
		m_mat[7] = static_cast<Type>(0);
		m_mat[11] = static_cast<Type>(0);
		m_mat[15] = static_cast<Type>(1);

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::SetTrace(Type x, Type y, Type z, Type w) {
		m_mat[0] = x;
		m_mat[5] = y;
		m_mat[10] = z;
		m_mat[15] = w;

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::operator -() {
		Type m11 = m_mat[0], m12 = m_mat[4], m13 = m_mat[8], m14 = m_mat[12],
		     m21 = m_mat[1], m22 = m_mat[5], m23 = m_mat[9], m24 = m_mat[13],
		     m31 = m_mat[2], m32 = m_mat[6], m33 = m_mat[10], m34 = m_mat[14],
		     m41 = m_mat[3], m42 = m_mat[7], m43 = m_mat[11], m44 = m_mat[15],

		     me0 = m23 * m34 * m42 - m24 * m33 * m42 + m24 * m32 * m43 - m22 * m34 * m43 - m23 * m32 * m44 + m22 * m33 * m44,
		     me4 = m14 * m33 * m42 - m13 * m34 * m42 - m14 * m32 * m43 + m12 * m34 * m43 + m13 * m32 * m44 - m12 * m33 * m44,
		     me8 = m13 * m24 * m42 - m14 * m23 * m42 + m14 * m22 * m43 - m12 * m24 * m43 - m13 * m22 * m44 + m12 * m23 * m44,
		     me12 = m14 * m23 * m32 - m13 * m24 * m32 - m14 * m22 * m33 + m12 * m24 * m33 + m13 * m22 * m34 - m12 * m23 * m34,

		     det = m11 * me0 + m21 * me4 + m31 * me8 + m41 * me12;

		if (det == static_cast<Type>(0)) {
			return Identity();
		}
		det = static_cast<Type>(1) / det;

		m_mat[0] = me0 * det;
		m_mat[4] = me4 * det;
		m_mat[8] = me8 * det;
		m_mat[12] = me12 * det;
		m_mat[1] = (m24 * m33 * m41 - m23 * m34 * m41 - m24 * m31 * m43 + m21 * m34 * m43 + m23 * m31 * m44 - m21 * m33 * m44) * det;
		m_mat[5] = (m13 * m34 * m41 - m14 * m33 * m41 + m14 * m31 * m43 - m11 * m34 * m43 - m13 * m31 * m44 + m11 * m33 * m44) * det;
		m_mat[9] = (m14 * m23 * m41 - m13 * m24 * m41 - m14 * m21 * m43 + m11 * m24 * m43 + m13 * m21 * m44 - m11 * m23 * m44) * det;
		m_mat[13] = (m13 * m24 * m31 - m14 * m23 * m31 + m14 * m21 * m33 - m11 * m24 * m33 - m13 * m21 * m34 + m11 * m23 * m34) * det;
		m_mat[2] = (m22 * m34 * m41 - m24 * m32 * m41 + m24 * m31 * m42 - m21 * m34 * m42 - m22 * m31 * m44 + m21 * m32 * m44) * det;
		m_mat[6] = (m14 * m32 * m41 - m12 * m34 * m41 - m14 * m31 * m42 + m11 * m34 * m42 + m12 * m31 * m44 - m11 * m32 * m44) * det;
		m_mat[10] = (m12 * m24 * m41 - m14 * m22 * m41 + m14 * m21 * m42 - m11 * m24 * m42 - m12 * m21 * m44 + m11 * m22 * m44) * det;
		m_mat[14] = (m14 * m22 * m31 - m12 * m24 * m31 - m14 * m21 * m32 + m11 * m24 * m32 + m12 * m21 * m34 - m11 * m22 * m34) * det;
		m_mat[3] = (m23 * m32 * m41 - m22 * m33 * m41 - m23 * m31 * m42 + m21 * m33 * m42 + m22 * m31 * m43 - m21 * m32 * m43) * det;
		m_mat[7] = (m12 * m33 * m41 - m13 * m32 * m41 + m13 * m31 * m42 - m11 * m33 * m42 - m12 * m31 * m43 + m11 * m32 * m43) * det;
		m_mat[11] = (m13 * m22 * m41 - m12 * m23 * m41 - m13 * m21 * m42 + m11 * m23 * m42 + m12 * m21 * m43 - m11 * m22 * m43) * det;
		m_mat[15] = (m12 * m23 * m31 - m13 * m22 * m31 + m13 * m21 * m32 - m11 * m23 * m32 - m12 * m21 * m33 + m11 * m22 * m33) * det;

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::Inverse(void) {
		Type m11 = m_mat[0], m12 = m_mat[4], m13 = m_mat[8], m14 = m_mat[12],
		     m21 = m_mat[1], m22 = m_mat[5], m23 = m_mat[9], m24 = m_mat[13],
		     m31 = m_mat[2], m32 = m_mat[6], m33 = m_mat[10], m34 = m_mat[14],
		     m41 = m_mat[3], m42 = m_mat[7], m43 = m_mat[11], m44 = m_mat[15],

		     me0 = m23 * m34 * m42 - m24 * m33 * m42 + m24 * m32 * m43 - m22 * m34 * m43 - m23 * m32 * m44 + m22 * m33 * m44,
		     me4 = m14 * m33 * m42 - m13 * m34 * m42 - m14 * m32 * m43 + m12 * m34 * m43 + m13 * m32 * m44 - m12 * m33 * m44,
		     me8 = m13 * m24 * m42 - m14 * m23 * m42 + m14 * m22 * m43 - m12 * m24 * m43 - m13 * m22 * m44 + m12 * m23 * m44,
		     me12 = m14 * m23 * m32 - m13 * m24 * m32 - m14 * m22 * m33 + m12 * m24 * m33 + m13 * m22 * m34 - m12 * m23 * m34,

		     det = m11 * me0 + m21 * me4 + m31 * me8 + m41 * me12;

		if (det == static_cast<Type>(0)) {
			return Identity();
		}
		det = static_cast<Type>(1) / det;

		m_mat[0] = me0 * det;
		m_mat[4] = me4 * det;
		m_mat[8] = me8 * det;
		m_mat[12] = me12 * det;
		m_mat[1] = (m24 * m33 * m41 - m23 * m34 * m41 - m24 * m31 * m43 + m21 * m34 * m43 + m23 * m31 * m44 - m21 * m33 * m44) * det;
		m_mat[5] = (m13 * m34 * m41 - m14 * m33 * m41 + m14 * m31 * m43 - m11 * m34 * m43 - m13 * m31 * m44 + m11 * m33 * m44) * det;
		m_mat[9] = (m14 * m23 * m41 - m13 * m24 * m41 - m14 * m21 * m43 + m11 * m24 * m43 + m13 * m21 * m44 - m11 * m23 * m44) * det;
		m_mat[13] = (m13 * m24 * m31 - m14 * m23 * m31 + m14 * m21 * m33 - m11 * m24 * m33 - m13 * m21 * m34 + m11 * m23 * m34) * det;
		m_mat[2] = (m22 * m34 * m41 - m24 * m32 * m41 + m24 * m31 * m42 - m21 * m34 * m42 - m22 * m31 * m44 + m21 * m32 * m44) * det;
		m_mat[6] = (m14 * m32 * m41 - m12 * m34 * m41 - m14 * m31 * m42 + m11 * m34 * m42 + m12 * m31 * m44 - m11 * m32 * m44) * det;
		m_mat[10] = (m12 * m24 * m41 - m14 * m22 * m41 + m14 * m21 * m42 - m11 * m24 * m42 - m12 * m21 * m44 + m11 * m22 * m44) * det;
		m_mat[14] = (m14 * m22 * m31 - m12 * m24 * m31 - m14 * m21 * m32 + m11 * m24 * m32 + m12 * m21 * m34 - m11 * m22 * m34) * det;
		m_mat[3] = (m23 * m32 * m41 - m22 * m33 * m41 - m23 * m31 * m42 + m21 * m33 * m42 + m22 * m31 * m43 - m21 * m32 * m43) * det;
		m_mat[7] = (m12 * m33 * m41 - m13 * m32 * m41 + m13 * m31 * m42 - m11 * m33 * m42 - m12 * m31 * m43 + m11 * m32 * m43) * det;
		m_mat[11] = (m13 * m22 * m41 - m12 * m23 * m41 - m13 * m21 * m42 + m11 * m23 * m42 + m12 * m21 * m43 - m11 * m22 * m43) * det;
		m_mat[15] = (m12 * m23 * m31 - m13 * m22 * m31 + m13 * m21 * m32 - m11 * m23 * m32 - m12 * m21 * m33 + m11 * m22 * m33) * det;

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::Inverse(const Mat4<Type>& m) {
		Type m11 = m.m_mat[0], m12 = m.m_mat[4], m13 = m.m_mat[8], m14 = m.m_mat[12],
		     m21 = m.m_mat[1], m22 = m.m_mat[5], m23 = m.m_mat[9], m24 = m.m_mat[13],
		     m31 = m.m_mat[2], m32 = m.m_mat[6], m33 = m.m_mat[10], m34 = m.m_mat[14],
		     m41 = m.m_mat[3], m42 = m.m_mat[7], m43 = m.m_mat[11], m44 = m.m_mat[15],

		     me0 = m23 * m34 * m42 - m24 * m33 * m42 + m24 * m32 * m43 - m22 * m34 * m43 - m23 * m32 * m44 + m22 * m33 * m44,
		     me4 = m14 * m33 * m42 - m13 * m34 * m42 - m14 * m32 * m43 + m12 * m34 * m43 + m13 * m32 * m44 - m12 * m33 * m44,
		     me8 = m13 * m24 * m42 - m14 * m23 * m42 + m14 * m22 * m43 - m12 * m24 * m43 - m13 * m22 * m44 + m12 * m23 * m44,
		     me12 = m14 * m23 * m32 - m13 * m24 * m32 - m14 * m22 * m33 + m12 * m24 * m33 + m13 * m22 * m34 - m12 * m23 * m34,

		     det = m11 * me0 + m21 * me4 + m31 * me8 + m41 * me12;

		if (det == static_cast<Type>(0)) {
			return Identity();
		}
		det = static_cast<Type>(1) / det;

		m_mat[0] = me0 * det;
		m_mat[4] = me4 * det;
		m_mat[8] = me8 * det;
		m_mat[12] = me12 * det;
		m_mat[1] = (m24 * m33 * m41 - m23 * m34 * m41 - m24 * m31 * m43 + m21 * m34 * m43 + m23 * m31 * m44 - m21 * m33 * m44) * det;
		m_mat[5] = (m13 * m34 * m41 - m14 * m33 * m41 + m14 * m31 * m43 - m11 * m34 * m43 - m13 * m31 * m44 + m11 * m33 * m44) * det;
		m_mat[9] = (m14 * m23 * m41 - m13 * m24 * m41 - m14 * m21 * m43 + m11 * m24 * m43 + m13 * m21 * m44 - m11 * m23 * m44) * det;
		m_mat[13] = (m13 * m24 * m31 - m14 * m23 * m31 + m14 * m21 * m33 - m11 * m24 * m33 - m13 * m21 * m34 + m11 * m23 * m34) * det;
		m_mat[2] = (m22 * m34 * m41 - m24 * m32 * m41 + m24 * m31 * m42 - m21 * m34 * m42 - m22 * m31 * m44 + m21 * m32 * m44) * det;
		m_mat[6] = (m14 * m32 * m41 - m12 * m34 * m41 - m14 * m31 * m42 + m11 * m34 * m42 + m12 * m31 * m44 - m11 * m32 * m44) * det;
		m_mat[10] = (m12 * m24 * m41 - m14 * m22 * m41 + m14 * m21 * m42 - m11 * m24 * m42 - m12 * m21 * m44 + m11 * m22 * m44) * det;
		m_mat[14] = (m14 * m22 * m31 - m12 * m24 * m31 - m14 * m21 * m32 + m11 * m24 * m32 + m12 * m21 * m34 - m11 * m22 * m34) * det;
		m_mat[3] = (m23 * m32 * m41 - m22 * m33 * m41 - m23 * m31 * m42 + m21 * m33 * m42 + m22 * m31 * m43 - m21 * m32 * m43) * det;
		m_mat[7] = (m12 * m33 * m41 - m13 * m32 * m41 + m13 * m31 * m42 - m11 * m33 * m42 - m12 * m31 * m43 + m11 * m32 * m43) * det;
		m_mat[11] = (m13 * m22 * m41 - m12 * m23 * m41 - m13 * m21 * m42 + m11 * m23 * m42 + m12 * m21 * m43 - m11 * m22 * m43) * det;
		m_mat[15] = (m12 * m23 * m31 - m13 * m22 * m31 + m13 * m21 * m32 - m11 * m23 * m32 - m12 * m21 * m33 + m11 * m22 * m33) * det;

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::Transpose(void) {
		Type tmp;

		tmp = m_mat[1];
		m_mat[1] = m_mat[4];
		m_mat[4] = tmp;
		tmp = m_mat[2];
		m_mat[2] = m_mat[8];
		m_mat[8] = tmp;
		tmp = m_mat[6];
		m_mat[6] = m_mat[9];
		m_mat[9] = tmp;

		tmp = m_mat[3];
		m_mat[3] = m_mat[12];
		m_mat[12] = tmp;
		tmp = m_mat[7];
		m_mat[7] = m_mat[13];
		m_mat[13] = tmp;
		tmp = m_mat[11];
		m_mat[11] = m_mat[14];
		m_mat[14] = tmp;

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::Compose(const Vec3<Type>& position, const Vec3<Type>& scale, const Quat<Type>& rotation) {
		Type x = rotation.x,
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

		m_mat[0] = (static_cast<Type>(1) - (yy + zz)) * sx;
		m_mat[4] = (xy - wz) * sy;
		m_mat[8] = (xz + wy) * sz;

		m_mat[1] = (xy + wz) * sx;
		m_mat[5] = (static_cast<Type>(1) - (xx + zz)) * sy;
		m_mat[9] = (yz - wx) * sz;

		m_mat[2] = (xz - wy) * sx;
		m_mat[6] = (yz + wx) * sy;
		m_mat[10] = (static_cast<Type>(1) - (xx + yy)) * sz;

		m_mat[3] = static_cast<Type>(0);
		m_mat[7] = static_cast<Type>(0);
		m_mat[11] = static_cast<Type>(0);

		m_mat[12] = position.x;
		m_mat[13] = position.y;
		m_mat[14] = position.z;
		m_mat[15] = static_cast<Type>(1);

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::Compose(const Vec3<Type>& position, const Quat<Type>& rotation) {
		Type x = rotation.x,
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
		     wz = w * z2;

		m_mat[0] = (static_cast<Type>(1) - (yy + zz));
		m_mat[4] = (xy - wz);
		m_mat[8] = (xz + wy);

		m_mat[1] = (xy + wz);
		m_mat[5] = (static_cast<Type>(1) - (xx + zz));
		m_mat[9] = (yz - wx);

		m_mat[2] = (xz - wy);
		m_mat[6] = (yz + wx);
		m_mat[10] = (static_cast<Type>(1) - (xx + yy));

		m_mat[3] = static_cast<Type>(0);
		m_mat[7] = static_cast<Type>(0);
		m_mat[11] = static_cast<Type>(0);

		m_mat[12] = position.x;
		m_mat[13] = position.y;
		m_mat[14] = position.z;
		m_mat[15] = static_cast<Type>(1);

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::Decompose(Vec3<Type>& position, Vec3<Type>& scale, Quat<Type>& rotation) {
		Type m11 = m_mat[0],
		     m12 = m_mat[4],
		     m13 = m_mat[8],
		     m21 = m_mat[1],
		     m22 = m_mat[5],
		     m23 = m_mat[9],
		     m31 = m_mat[2],
		     m32 = m_mat[6],
		     m33 = m_mat[10],
		     x = static_cast<Type>(0),
		     y = static_cast<Type>(0),
		     z = static_cast<Type>(0),
		     w = static_cast<Type>(1),
		     s,

		     sx = Vec3Length<Type>(m11, m21, m31),
		     sy = Vec3Length<Type>(m12, m22, m32),
		     sz = Vec3Length<Type>(m13, m23, m33),

		     invSx = static_cast<Type>(1) / sx,
		     invSy = static_cast<Type>(1) / sy,
		     invSz = static_cast<Type>(1) / sz,
		     trace;

		scale.x = sx;
		scale.y = sy;
		scale.z = sz;

		position.x = m_mat[12];
		position.y = m_mat[13];
		position.z = m_mat[14];

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

		if (trace > static_cast<Type>(0)) {
			s = static_cast<Type>(0.5) / Mathf.Sqrt(trace + static_cast<Type>(1));

			w = static_cast<Type>(0.25) / s;
			x = (m32 - m23) * s;
			y = (m13 - m31) * s;
			z = (m21 - m12) * s;

		} else if (m11 > m22 && m11 > m33) {
			s = static_cast<Type>(2) * Mathf.Sqrt(static_cast<Type>(1) + m11 - m22 - m33);

			w = (m32 - m23) / s;
			x = static_cast<Type>(0.25) * s;
			y = (m12 + m21) / s;
			z = (m13 + m31) / s;

		} else if (m22 > m33) {
			s = static_cast<Type>(2) * Mathf.Sqrt(static_cast<Type>(1) + m22 - m11 - m33);

			w = (m13 - m31) / s;
			x = (m12 + m21) / s;
			y = static_cast<Type>(0.25) * s;
			z = (m23 + m32) / s;

		} else {
			s = static_cast<Type>(2) * Mathf.Sqrt(static_cast<Type>(1) + m33 - m11 - m22);

			w = (m21 - m12) / s;
			x = (m13 + m31) / s;
			y = (m23 + m32) / s;
			z = static_cast<Type>(0.25) * s;
		}

		rotation.x = x;
		rotation.y = y;
		rotation.z = z;
		rotation.w = w;

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::SetPosition(const Vec3<Type>& v) {

		m_mat[12] = v.x;
		m_mat[13] = v.y;
		m_mat[14] = v.z;

		return *this;
	}

	template <typename Type> inline Vec3<Type> Mat4<Type>::GetPosition(void) {

		return Vec3<Type>(m_mat[12], m_mat[13], m_mat[14]);
	}

	template <typename Type> inline Vec3<Type>& Mat4<Type>::GetPosition(Vec3<Type>& v) {

		v.x = m_mat[12];
		v.y = m_mat[13];
		v.z = m_mat[14];
	
		return v;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::ExtractPosition(const Mat4<Type>& m) {

		m_mat[12] = m.m_mat[12];
		m_mat[13] = m.m_mat[13];
		m_mat[14] = m.m_mat[14];

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::ExtractRotation(const Mat4<Type>& m) {
		Vec3<Type> vec;
		Type lx = Vec3LengthSq<Type>(m.m_mat[0], m.m_mat[1], m.m_mat[2]),
		     ly = Vec3LengthSq<Type>(m.m_mat[4], m.m_mat[5], m.m_mat[6]),
		     lz = Vec3LengthSq<Type>(m.m_mat[8], m.m_mat[9], m.m_mat[10]),

		     scaleX = lx > static_cast<Type>(0) ? static_cast<Type>(1) / Mathf.Sqrt(lx) : static_cast<Type>(0),
		     scaleY = ly > static_cast<Type>(0) ? static_cast<Type>(1) / Mathf.Sqrt(ly) : static_cast<Type>(0),
		     scaleZ = lz > static_cast<Type>(0) ? static_cast<Type>(1) / Mathf.Sqrt(lz) : static_cast<Type>(0);

		m_mat[0] = m.m_mat[0] * scaleX;
		m_mat[1] = m.m_mat[1] * scaleX;
		m_mat[2] = m.m_mat[2] * scaleX;

		m_mat[4] = m.m_mat[4] * scaleY;
		m_mat[5] = m.m_mat[5] * scaleY;
		m_mat[6] = m.m_mat[6] * scaleY;

		m_mat[8] = m.m_mat[8] * scaleZ;
		m_mat[9] = m.m_mat[9] * scaleZ;
		m_mat[10] = m.m_mat[10] * scaleZ;

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::ExtractRotationWithScale(const Mat4<Type>& m) {

		m_mat[0] = m.m_mat[0];
		m_mat[1] = m.m_mat[1];
		m_mat[2] = m.m_mat[2];

		m_mat[4] = m.m_mat[4];
		m_mat[5] = m.m_mat[5];
		m_mat[6] = m.m_mat[6];

		m_mat[8] = m.m_mat[8];
		m_mat[9] = m.m_mat[9];
		m_mat[10] = m.m_mat[10];

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::Scale(const Vec2<Type>& v) {
		Type x = v.x, y = v.y;

		m_mat[0] *= x;
		m_mat[4] *= y;
		m_mat[1] *= x;
		m_mat[5] *= y;
		m_mat[2] *= x;
		m_mat[6] *= y;
		m_mat[3] *= x;
		m_mat[7] *= y;

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::Scale(const Vec3<Type>& v) {
		Type x = v.x, y = v.y, z = v.z;

		m_mat[0] *= x;
		m_mat[4] *= y;
		m_mat[8] *= z;
		m_mat[1] *= x;
		m_mat[5] *= y;
		m_mat[9] *= z;
		m_mat[2] *= x;
		m_mat[6] *= y;
		m_mat[10] *= z;
		m_mat[3] *= x;
		m_mat[7] *= y;
		m_mat[11] *= z;

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::Scale(const Vec4<Type>& v) {
		Type x = v.x, y = v.y, z = v.z, w = v.w;

		m_mat[0] *= x;
		m_mat[4] *= y;
		m_mat[8] *= z;
		m_mat[12] *= w;
		m_mat[1] *= x;
		m_mat[5] *= y;
		m_mat[9] *= z;
		m_mat[13] *= w;
		m_mat[2] *= x;
		m_mat[6] *= y;
		m_mat[10] *= z;
		m_mat[14] *= w;
		m_mat[3] *= x;
		m_mat[7] *= y;
		m_mat[11] *= z;
		m_mat[15] *= w;

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::RotateX(Type angle) {
		Type m12 = m_mat[4],
		     m22 = m_mat[5],
		     m32 = m_mat[6],
		     m42 = m_mat[7],
		     m13 = m_mat[8],
		     m23 = m_mat[9],
		     m33 = m_mat[10],
		     m43 = m_mat[11],
		     c = Mathf.Cos(angle),
		     s = Mathf.Sin(angle);

		m_mat[4] = c * m12 + s * m13;
		m_mat[5] = c * m22 + s * m23;
		m_mat[6] = c * m32 + s * m33;
		m_mat[7] = c * m42 + s * m43;

		m_mat[8] = c * m13 - s * m12;
		m_mat[9] = c * m23 - s * m22;
		m_mat[10] = c * m33 - s * m32;
		m_mat[11] = c * m43 - s * m42;

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::RotateY(Type angle) {
		Type m11 = m_mat[0],
		     m21 = m_mat[1],
		     m31 = m_mat[2],
		     m41 = m_mat[3],
		     m13 = m_mat[8],
		     m23 = m_mat[9],
		     m33 = m_mat[10],
		     m43 = m_mat[11],
		     c = Mathf.Cos(angle),
		     s = Mathf.Sin(angle);

		m_mat[0] = c * m11 - s * m13;
		m_mat[1] = c * m21 - s * m23;
		m_mat[2] = c * m31 - s * m33;
		m_mat[3] = c * m41 - s * m43;

		m_mat[8] = c * m13 + s * m11;
		m_mat[9] = c * m23 + s * m21;
		m_mat[10] = c * m33 + s * m31;
		m_mat[11] = c * m43 + s * m41;

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::RotateZ(Type angle) {
		Type m11 = m_mat[0],
			m21 = m_mat[1],
			m31 = m_mat[2],
			m41 = m_mat[3],
			m12 = m_mat[4],
			m22 = m_mat[5],
			m32 = m_mat[6],
			m42 = m_mat[7],
			c = Mathf.Cos(angle),
			s = Mathf.Sin(angle);

		m_mat[0] = c * m11 + s * m12;
		m_mat[1] = c * m21 + s * m22;
		m_mat[2] = c * m31 + s * m32;
		m_mat[3] = c * m41 + s * m42;

		m_mat[4] = c * m12 - s * m11;
		m_mat[5] = c * m22 - s * m21;
		m_mat[6] = c * m32 - s * m31;
		m_mat[7] = c * m42 - s * m41;

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::Rotate(Type x, Type y, Type z) {
		
		RotateZ(z);
		RotateX(x);
		RotateY(y);

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::FromQuat(const Quat<Type>& q) {
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
		m_mat[4] = xy - wz;
		m_mat[8] = xz + wy;

		m_mat[1] = xy + wz;
		m_mat[5] = static_cast<Type>(1) - (xx + zz);
		m_mat[9] = yz - wx;

		m_mat[2] = xz - wy;
		m_mat[6] = yz + wx;
		m_mat[10] = static_cast<Type>(1) - (xx + yy);

		m_mat[3] = static_cast<Type>(0);
		m_mat[7] = static_cast<Type>(0);
		m_mat[11] = static_cast<Type>(0);

		m_mat[12] = static_cast<Type>(0);
		m_mat[13] = static_cast<Type>(0);
		m_mat[14] = static_cast<Type>(0);
		m_mat[15] = static_cast<Type>(1);

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::Frustum(Type left, Type right, Type top, Type bottom, Type near, Type far) {
		Type x = static_cast<Type>(2) * near / (right - left),
		     y = static_cast<Type>(2) * near / (top - bottom),

		     a = (right + left) / (right - left),
		     b = (top + bottom) / (top - bottom),
		     c = -(far + near) / (far - near),
		     d = -static_cast<Type>(2) * far * near / (far - near);

		m_mat[0] = x;
		m_mat[4] = static_cast<Type>(0);
		m_mat[8] = a;
		m_mat[12] = static_cast<Type>(0);
		m_mat[1] = static_cast<Type>(0);
		m_mat[5] = y;
		m_mat[9] = b;
		m_mat[13] = static_cast<Type>(0);
		m_mat[2] = static_cast<Type>(0);
		m_mat[6] = static_cast<Type>(0);
		m_mat[10] = c;
		m_mat[14] = d;
		m_mat[3] = static_cast<Type>(0);
		m_mat[7] = static_cast<Type>(0);
		m_mat[11] = -static_cast<Type>(1);
		m_mat[15] = static_cast<Type>(0);

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::Perspective(Type fov, Type aspect, Type near, Type far) {
		Type ymax = near * Mathf.Tan(fov * static_cast<Type>(0.5)),
		     ymin = -ymax,
		     xmin = ymin * aspect,
		     xmax = ymax * aspect;

		Frustum(xmin, xmax, ymax, ymin, near, far);
		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::Orthographic(Type left, Type right, Type top, Type bottom, Type near, Type far) {
		Type w = right - left,
		     h = top - bottom,
		     p = far - near,

		     x = (right + left) / w,
		     y = (top + bottom) / h,
		     z = (far + near) / p;

		m_mat[0] = static_cast<Type>(2) / w;
		m_mat[1] = static_cast<Type>(0);
		m_mat[2] = static_cast<Type>(0);
		m_mat[3] = static_cast<Type>(0);
		m_mat[4] = static_cast<Type>(0);
		m_mat[5] = static_cast<Type>(2) / h;
		m_mat[6] = static_cast<Type>(0);
		m_mat[7] = static_cast<Type>(0);
		m_mat[8] = static_cast<Type>(0);
		m_mat[9] = static_cast<Type>(0);
		m_mat[10] = -static_cast<Type>(2) / p;
		m_mat[11] = static_cast<Type>(0);
		m_mat[12] = -x;
		m_mat[13] = -y;
		m_mat[14] = -z;
		m_mat[15] = static_cast<Type>(1);

		return *this;
	}

	template <typename Type> inline Type Mat4<Type>::operator [] (int32 i) const {
		return m_mat[i];
	}

	template <typename Type> inline Type& Mat4<Type>::operator [] (int32 i) {
		return m_mat[i];
	}

	template <typename Type> inline Mat4<Type> Mat4<Type>::operator *(const Vec2<Type>& v) {
		Type x = v.x, y = v.y;

		return Mat4<Type>(
		           m_mat[0], m_mat[4], m_mat[8], m_mat[0] * x + m_mat[4] * y + m_mat[12],
		           m_mat[1], m_mat[5], m_mat[9], m_mat[1] * x + m_mat[5] * y + m_mat[13],
		           m_mat[2], m_mat[6], m_mat[10], m_mat[2] * x + m_mat[6] * y + m_mat[14],
		           m_mat[3], m_mat[7], m_mat[11],  m_mat[3] * x + m_mat[7] * y + m_mat[15]
		       );
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::operator +=(const Vec2<Type>& v) {
		Type x = v.x, y = v.y;

		m_mat[12] = m_mat[0] * x + m_mat[4] * y + m_mat[12];
		m_mat[13] = m_mat[1] * x + m_mat[5] * y + m_mat[13];
		m_mat[14] = m_mat[2] * x + m_mat[6] * y + m_mat[14];
		m_mat[15] = m_mat[3] * x + m_mat[7] * y + m_mat[15];

		return *this;
	}

	template <typename Type> inline Mat4<Type> Mat4<Type>::operator *(const Vec3<Type>& v) {
		Type x = v.x, y = v.y, z = v.z;

		return Mat4<Type>(
		           m_mat[0], m_mat[4], m_mat[8], m_mat[0] * x + m_mat[4] * y + m_mat[8] * z + m_mat[12],
		           m_mat[1], m_mat[5], m_mat[9], m_mat[1] * x + m_mat[5] * y + m_mat[9] * z + m_mat[13],
		           m_mat[2], m_mat[6], m_mat[10], m_mat[2] * x + m_mat[6] * y + m_mat[10] * z + m_mat[14],
		           m_mat[3], m_mat[7], m_mat[11],  m_mat[3] * x + m_mat[7] * y + m_mat[11] * z + m_mat[15]
		       );
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::operator *=(const Vec3<Type>& v) {
		Type x = v.x, y = v.y, z = v.z;

		m_mat[12] = m_mat[0] * x + m_mat[4] * y + m_mat[8] * z + m_mat[12];
		m_mat[13] = m_mat[1] * x + m_mat[5] * y + m_mat[9] * z + m_mat[13];
		m_mat[14] = m_mat[2] * x + m_mat[6] * y + m_mat[10] * z + m_mat[14];
		m_mat[15] = m_mat[3] * x + m_mat[7] * y + m_mat[11] * z + m_mat[15];

		return *this;
	}

	template <typename Type> inline Mat4<Type> Mat4<Type>::operator *(const Vec4<Type>& v) {
		Type x = v.x, y = v.y, z = v.z, w = v.w;

		return Mat4<Type>(
		           m_mat[0], m_mat[4], m_mat[8], m_mat[0] * x + m_mat[4] * y + m_mat[8] * z + m_mat[12] * w,
		           m_mat[1], m_mat[5], m_mat[9], m_mat[1] * x + m_mat[5] * y + m_mat[9] * z + m_mat[13] * w,
		           m_mat[2], m_mat[6], m_mat[10], m_mat[2] * x + m_mat[6] * y + m_mat[10] * z + m_mat[14] * w,
		           m_mat[3], m_mat[7], m_mat[11],  m_mat[3] * x + m_mat[7] * y + m_mat[11] * z + m_mat[15] * w
		       );
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::operator *=(const Vec4<Type>& v) {
		Type x = v.x, y = v.y, z = v.z, w = v.w;

		m_mat[12] = m_mat[0] * x + m_mat[4] * y + m_mat[8] * z + m_mat[12] * w;
		m_mat[13] = m_mat[1] * x + m_mat[5] * y + m_mat[9] * z + m_mat[13] * w;
		m_mat[14] = m_mat[2] * x + m_mat[6] * y + m_mat[10] * z + m_mat[14] * w;
		m_mat[15] = m_mat[3] * x + m_mat[7] * y + m_mat[11] * z + m_mat[15] * w;

		return *this;
	}

	template <typename Type> inline Mat4<Type> Mat4<Type>::operator *(const Mat4<Type>& m) {
		Type a11 = m_mat[0], a12 = m_mat[4], a13 = m_mat[8], a14 = m_mat[12],
		     a21 = m_mat[1], a22 = m_mat[5], a23 = m_mat[9], a24 = m_mat[13],
		     a31 = m_mat[2], a32 = m_mat[6], a33 = m_mat[10], a34 = m_mat[14],
		     a41 = m_mat[3], a42 = m_mat[7], a43 = m_mat[11], a44 = m_mat[15],

		     b11 = m.m_mat[0], b12 = m.m_mat[4], b13 = m.m_mat[8], b14 = m.m_mat[12],
		     b21 = m.m_mat[1], b22 = m.m_mat[5], b23 = m.m_mat[9], b24 = m.m_mat[13],
		     b31 = m.m_mat[2], b32 = m.m_mat[6], b33 = m.m_mat[10], b34 = m.m_mat[14],
		     b41 = m.m_mat[3], b42 = m.m_mat[7], b43 = m.m_mat[11], b44 = m.m_mat[15];

		return Mat4<Type>(
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

	template <typename Type> inline Mat4<Type>& Mat4<Type>::operator *=(const Mat4<Type>& m) {
		Type a11 = m_mat[0], a12 = m_mat[4], a13 = m_mat[8], a14 = m_mat[12],
		     a21 = m_mat[1], a22 = m_mat[5], a23 = m_mat[9], a24 = m_mat[13],
		     a31 = m_mat[2], a32 = m_mat[6], a33 = m_mat[10], a34 = m_mat[14],
		     a41 = m_mat[3], a42 = m_mat[7], a43 = m_mat[11], a44 = m_mat[15],

		     b11 = m.m_mat[0], b12 = m.m_mat[4], b13 = m.m_mat[8], b14 = m.m_mat[12],
		     b21 = m.m_mat[1], b22 = m.m_mat[5], b23 = m.m_mat[9], b24 = m.m_mat[13],
		     b31 = m.m_mat[2], b32 = m.m_mat[6], b33 = m.m_mat[10], b34 = m.m_mat[14],
		     b41 = m.m_mat[3], b42 = m.m_mat[7], b43 = m.m_mat[11], b44 = m.m_mat[15];

		m_mat[0] = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41;
		m_mat[4] = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42;
		m_mat[8] = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43;
		m_mat[12] = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44;

		m_mat[1] = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41;
		m_mat[5] = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42;
		m_mat[9] = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43;
		m_mat[13] = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44;

		m_mat[2] = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41;
		m_mat[6] = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42;
		m_mat[10] = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43;
		m_mat[14] = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44;

		m_mat[3] = a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41;
		m_mat[7] = a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42;
		m_mat[11] = a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43;
		m_mat[15] = a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44;

		return *this;
	}

	template <typename Type> inline Mat4<Type> Mat4<Type>::operator *(const Mat43<Type>& m) {
		Type a11 = m_mat[0], a12 = m_mat[4], a13 = m_mat[8], a14 = m_mat[12],
		     a21 = m_mat[1], a22 = m_mat[5], a23 = m_mat[9], a24 = m_mat[13],
		     a31 = m_mat[2], a32 = m_mat[6], a33 = m_mat[10], a34 = m_mat[14],
		     a41 = m_mat[3], a42 = m_mat[7], a43 = m_mat[11], a44 = m_mat[15],

		     b11 = m.m_mat[0], b12 = m.m_mat[3], b13 = m.m_mat[6], b14 = m.m_mat[9],
		     b21 = m.m_mat[1], b22 = m.m_mat[4], b23 = m.m_mat[7], b24 = m.m_mat[10],
		     b31 = m.m_mat[2], b32 = m.m_mat[5], b33 = m.m_mat[8], b34 = m.m_mat[11];

		return Mat4<Type>(
		           a11 * b11 + a12 * b21 + a13 * b31,
		           a11 * b12 + a12 * b22 + a13 * b32,
		           a11 * b13 + a12 * b23 + a13 * b33,
		           a11 * b14 + a12 * b24 + a13 * b34 + a14,

		           a21 * b11 + a22 * b21 + a23 * b31,
		           a21 * b12 + a22 * b22 + a23 * b32,
		           a21 * b13 + a22 * b23 + a23 * b33,
		           a21 * b14 + a22 * b24 + a23 * b34 + a24,

		           a31 * b11 + a32 * b21 + a33 * b31,
		           a31 * b12 + a32 * b22 + a33 * b32,
		           a31 * b13 + a32 * b23 + a33 * b33,
		           a31 * b14 + a32 * b24 + a33 * b34 + a34,

		           a41 * b11 + a42 * b21 + a43 * b31,
		           a41 * b12 + a42 * b22 + a43 * b32,
		           a41 * b13 + a42 * b23 + a43 * b33,
		           a41 * b14 + a42 * b24 + a43 * b34 + a44
		       );
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::operator *=(const Mat43<Type>& m) {
		Type a11 = m_mat[0], a12 = m_mat[4], a13 = m_mat[8], a14 = m_mat[12],
		     a21 = m_mat[1], a22 = m_mat[5], a23 = m_mat[9], a24 = m_mat[13],
		     a31 = m_mat[2], a32 = m_mat[6], a33 = m_mat[10], a34 = m_mat[14],
		     a41 = m_mat[3], a42 = m_mat[7], a43 = m_mat[11], a44 = m_mat[15],

		     b11 = m.m_mat[0], b12 = m.m_mat[3], b13 = m.m_mat[6], b14 = m.m_mat[9],
		     b21 = m.m_mat[1], b22 = m.m_mat[4], b23 = m.m_mat[7], b24 = m.m_mat[10],
		     b31 = m.m_mat[2], b32 = m.m_mat[5], b33 = m.m_mat[8], b34 = m.m_mat[11];

		m_mat[0] = a11 * b11 + a12 * b21 + a13 * b31;
		m_mat[4] = a11 * b12 + a12 * b22 + a13 * b32 ;
		m_mat[8] = a11 * b13 + a12 * b23 + a13 * b33;
		m_mat[12] = a11 * b14 + a12 * b24 + a13 * b34 + a14;

		m_mat[1] = a21 * b11 + a22 * b21 + a23 * b31;
		m_mat[5] = a21 * b12 + a22 * b22 + a23 * b32;
		m_mat[9] = a21 * b13 + a22 * b23 + a23 * b33;
		m_mat[13] = a21 * b14 + a22 * b24 + a23 * b34 + a24;

		m_mat[2] = a31 * b11 + a32 * b21 + a33 * b31;
		m_mat[6] = a31 * b12 + a32 * b22 + a33 * b32;
		m_mat[10] = a31 * b13 + a32 * b23 + a33 * b33;
		m_mat[14] = a31 * b14 + a32 * b24 + a33 * b34 + a34;

		m_mat[3] = a41 * b11 + a42 * b21 + a43 * b31;
		m_mat[7] = a41 * b12 + a42 * b22 + a43 * b32;
		m_mat[11] = a41 * b13 + a42 * b23 + a43 * b33;
		m_mat[15] = a41 * b14 + a42 * b24 + a43 * b34 + a44;

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::operator *=(Type s) {
		m_mat[0] *= s;
		m_mat[1] *= s;
		m_mat[2] *= s;
		m_mat[3] *= s;
		m_mat[4] *= s;
		m_mat[5] *= s;
		m_mat[6] *= s;
		m_mat[7] *= s;
		m_mat[8] *= s;
		m_mat[9] *= s;
		m_mat[10] *= s;
		m_mat[11] *= s;
		m_mat[12] *= s;
		m_mat[13] *= s;
		m_mat[14] *= s;
		m_mat[15] *= s;

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::operator /=(Type s) {
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
		m_mat[9] *= d;
		m_mat[10] *= d;
		m_mat[11] *= d;
		m_mat[12] *= d;
		m_mat[13] *= d;
		m_mat[14] *= d;
		m_mat[15] *= d;

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::operator =(const Mat4<Type>& m) {
		m_mat[0] = m.m_mat[0];
		m_mat[4] = m.m_mat[4];
		m_mat[8] = m.m_mat[8];
		m_mat[12] = m.m_mat[12];
		m_mat[1] = m.m_mat[1];
		m_mat[5] = m.m_mat[5];
		m_mat[9] = m.m_mat[9];
		m_mat[13] = m.m_mat[13];
		m_mat[2] = m.m_mat[2];
		m_mat[6] = m.m_mat[6];
		m_mat[10] = m.m_mat[10];
		m_mat[14] = m.m_mat[14];
		m_mat[3] = m.m_mat[3];
		m_mat[7] = m.m_mat[7];
		m_mat[11] = m.m_mat[11];
		m_mat[15] = m.m_mat[15];

		return *this;
	}

	template <typename Type> inline Mat4<Type>& Mat4<Type>::operator =(const Mat4<Type> && m) {
		m_mat[0] = std::move(m.m_mat[0]);
		m_mat[4] = std::move(m.m_mat[4]);
		m_mat[8] = std::move(m.m_mat[8]);
		m_mat[12] = std::move(m.m_mat[12]);
		m_mat[1] = std::move(m.m_mat[1]);
		m_mat[5] = std::move(m.m_mat[5]);
		m_mat[9] = std::move(m.m_mat[9]);
		m_mat[13] = std::move(m.m_mat[13]);
		m_mat[2] = std::move(m.m_mat[2]);
		m_mat[6] = std::move(m.m_mat[6]);
		m_mat[10] = std::move(m.m_mat[10]);
		m_mat[14] = std::move(m.m_mat[14]);
		m_mat[3] = std::move(m.m_mat[3]);
		m_mat[7] = std::move(m.m_mat[7]);
		m_mat[11] = std::move(m.m_mat[11]);
		m_mat[15] = std::move(m.m_mat[15]);

		return *this;
	}

	template <typename Type> inline bool Mat4<Type>::operator ==(const Mat4<Type>& m) {
		return !(
		           m_mat[0] != m.m_mat[0] || m_mat[4] != m.m_mat[4] || m_mat[8] != m.m_mat[8] || m_mat[12] != m.m_mat[12] ||
		           m_mat[1] != m.m_mat[1] || m_mat[5] != m.m_mat[5] || m_mat[9] != m.m_mat[9] || m_mat[13] != m.m_mat[13] ||
		           m_mat[2] != m.m_mat[2] || m_mat[6] != m.m_mat[6] || m_mat[10] != m.m_mat[10] || m_mat[14] != m.m_mat[14] ||
		           m_mat[3] != m.m_mat[3] || m_mat[7] != m.m_mat[7] || m_mat[11] != m.m_mat[11] || m_mat[15] != m.m_mat[15]
		       );
	}

	template <typename Type> inline bool Mat4<Type>::operator != (const Mat4<Type>& m) {
		return (
		           m_mat[0] != m.m_mat[0] || m_mat[4] != m.m_mat[4] || m_mat[8] != m.m_mat[8] || m_mat[12] != m.m_mat[12] ||
		           m_mat[1] != m.m_mat[1] || m_mat[5] != m.m_mat[5] || m_mat[9] != m.m_mat[9] || m_mat[13] != m.m_mat[13] ||
		           m_mat[2] != m.m_mat[2] || m_mat[6] != m.m_mat[6] || m_mat[10] != m.m_mat[10] || m_mat[14] != m.m_mat[14] ||
		           m_mat[3] != m.m_mat[3] || m_mat[7] != m.m_mat[7] || m_mat[11] != m.m_mat[11] || m_mat[15] != m.m_mat[15]
		       );
	}

	template <typename Type> inline std::string Mat4<Type>::ToString(int32 p) {

		return (
		           "Mat4[\n"
		           "  " + Odin::ToString(m_mat[0], p) + ", " + Odin::ToString(m_mat[4], p) + ", " + Odin::ToString(m_mat[8], p) + ", " + Odin::ToString(m_mat[12], p) + ",\n" +
		           "  " + Odin::ToString(m_mat[1], p) + ", " + Odin::ToString(m_mat[5], p) + ", " + Odin::ToString(m_mat[9], p) + ", " + Odin::ToString(m_mat[13], p) + ",\n" +
		           "  " + Odin::ToString(m_mat[2], p) + ", " + Odin::ToString(m_mat[6], p) + ", " + Odin::ToString(m_mat[10], p) + ", " + Odin::ToString(m_mat[14], p) + ",\n" +
		           "  " + Odin::ToString(m_mat[3], p) + ", " + Odin::ToString(m_mat[7], p) + ", " + Odin::ToString(m_mat[11], p) + ", " + Odin::ToString(m_mat[15], p) + "\n"
		           "]"
		       );
	}

	template <typename Type> inline Mat4<Type>& Mat4Inverse(const Mat4<Type>& a, Mat4<Type>& out) {
		Type m11 = a.m_mat[0], m12 = a.m_mat[4], m13 = a.m_mat[8], m14 = a.m_mat[12],
		     m21 = a.m_mat[1], m22 = a.m_mat[5], m23 = a.m_mat[9], m24 = a.m_mat[13],
		     m31 = a.m_mat[2], m32 = a.m_mat[6], m33 = a.m_mat[10], m34 = a.m_mat[14],
		     m41 = a.m_mat[3], m42 = a.m_mat[7], m43 = a.m_mat[11], m44 = a.m_mat[15],

		     me0 = m23 * m34 * m42 - m24 * m33 * m42 + m24 * m32 * m43 - m22 * m34 * m43 - m23 * m32 * m44 + m22 * m33 * m44,
		     me4 = m14 * m33 * m42 - m13 * m34 * m42 - m14 * m32 * m43 + m12 * m34 * m43 + m13 * m32 * m44 - m12 * m33 * m44,
		     me8 = m13 * m24 * m42 - m14 * m23 * m42 + m14 * m22 * m43 - m12 * m24 * m43 - m13 * m22 * m44 + m12 * m23 * m44,
		     me12 = m14 * m23 * m32 - m13 * m24 * m32 - m14 * m22 * m33 + m12 * m24 * m33 + m13 * m22 * m34 - m12 * m23 * m34,

		     det = m11 * me0 + m21 * me4 + m31 * me8 + m41 * me12;

		if (det == static_cast<Type>(0)) {
			return out.Identity();
		} 
		det = static_cast<Type>(1) / det;

		out.m_mat[0] = me0 * det;
		out.m_mat[4] = me4 * det;
		out.m_mat[8] = me8 * det;
		out.m_mat[12] = me12 * det;
		out.m_mat[1] = (m24 * m33 * m41 - m23 * m34 * m41 - m24 * m31 * m43 + m21 * m34 * m43 + m23 * m31 * m44 - m21 * m33 * m44) * det;
		out.m_mat[5] = (m13 * m34 * m41 - m14 * m33 * m41 + m14 * m31 * m43 - m11 * m34 * m43 - m13 * m31 * m44 + m11 * m33 * m44) * det;
		out.m_mat[9] = (m14 * m23 * m41 - m13 * m24 * m41 - m14 * m21 * m43 + m11 * m24 * m43 + m13 * m21 * m44 - m11 * m23 * m44) * det;
		out.m_mat[13] = (m13 * m24 * m31 - m14 * m23 * m31 + m14 * m21 * m33 - m11 * m24 * m33 - m13 * m21 * m34 + m11 * m23 * m34) * det;
		out.m_mat[2] = (m22 * m34 * m41 - m24 * m32 * m41 + m24 * m31 * m42 - m21 * m34 * m42 - m22 * m31 * m44 + m21 * m32 * m44) * det;
		out.m_mat[6] = (m14 * m32 * m41 - m12 * m34 * m41 - m14 * m31 * m42 + m11 * m34 * m42 + m12 * m31 * m44 - m11 * m32 * m44) * det;
		out.m_mat[10] = (m12 * m24 * m41 - m14 * m22 * m41 + m14 * m21 * m42 - m11 * m24 * m42 - m12 * m21 * m44 + m11 * m22 * m44) * det;
		out.m_mat[14] = (m14 * m22 * m31 - m12 * m24 * m31 - m14 * m21 * m32 + m11 * m24 * m32 + m12 * m21 * m34 - m11 * m22 * m34) * det;
		out.m_mat[3] = (m23 * m32 * m41 - m22 * m33 * m41 - m23 * m31 * m42 + m21 * m33 * m42 + m22 * m31 * m43 - m21 * m32 * m43) * det;
		out.m_mat[7] = (m12 * m33 * m41 - m13 * m32 * m41 + m13 * m31 * m42 - m11 * m33 * m42 - m12 * m31 * m43 + m11 * m32 * m43) * det;
		out.m_mat[11] = (m13 * m22 * m41 - m12 * m23 * m41 - m13 * m21 * m42 + m11 * m23 * m42 + m12 * m21 * m43 - m11 * m22 * m43) * det;
		out.m_mat[15] = (m12 * m23 * m31 - m13 * m22 * m31 + m13 * m21 * m32 - m11 * m23 * m32 - m12 * m21 * m33 + m11 * m22 * m33) * det;

		return out;
	}

	template <typename Type> inline Mat4<Type>& Mat4Mul(const Mat4<Type>& a, const Mat4<Type>& b, Mat4<Type>& out) {
		Type a11 = a.m_mat[0], a12 = a.m_mat[4], a13 = a.m_mat[8], a14 = a.m_mat[12],
		     a21 = a.m_mat[1], a22 = a.m_mat[5], a23 = a.m_mat[9], a24 = a.m_mat[13],
		     a31 = a.m_mat[2], a32 = a.m_mat[6], a33 = a.m_mat[10], a34 = a.m_mat[14],
		     a41 = a.m_mat[3], a42 = a.m_mat[7], a43 = a.m_mat[11], a44 = a.m_mat[15],

		     b11 = b.m_mat[0], b12 = b.m_mat[4], b13 = b.m_mat[8], b14 = b.m_mat[12],
		     b21 = b.m_mat[1], b22 = b.m_mat[5], b23 = b.m_mat[9], b24 = b.m_mat[13],
		     b31 = b.m_mat[2], b32 = b.m_mat[6], b33 = b.m_mat[10], b34 = b.m_mat[14],
		     b41 = b.m_mat[3], b42 = b.m_mat[7], b43 = b.m_mat[11], b44 = b.m_mat[15];

		out.m_mat[0] = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41;
		out.m_mat[4] = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42;
		out.m_mat[8] = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43;
		out.m_mat[12] = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44;

		out.m_mat[1] = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41;
		out.m_mat[5] = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42;
		out.m_mat[9] = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43;
		out.m_mat[13] = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44;

		out.m_mat[2] = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41;
		out.m_mat[6] = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42;
		out.m_mat[10] = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43;
		out.m_mat[14] = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44;

		out.m_mat[3] = a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41;
		out.m_mat[7] = a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42;
		out.m_mat[11] = a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43;
		out.m_mat[15] = a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44;

		return out;
	}
}

#endif