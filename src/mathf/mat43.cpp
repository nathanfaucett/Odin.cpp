#ifndef ODIN_MAT43_CPP
#define ODIN_MAT43_CPP

namespace Odin {

	template <typename Type> inline Mat43<Type>::Mat43(void) {
		m_mat[0] = static_cast<Type>(1);
		m_mat[3] = static_cast<Type>(0);
		m_mat[6] = static_cast<Type>(0);
		m_mat[9] = static_cast<Type>(0);
		m_mat[1] = static_cast<Type>(0);
		m_mat[4] = static_cast<Type>(1);
		m_mat[7] = static_cast<Type>(0);
		m_mat[10] = static_cast<Type>(0);
		m_mat[2] = static_cast<Type>(0);
		m_mat[5] = static_cast<Type>(0);
		m_mat[8] = static_cast<Type>(1);
		m_mat[11] = static_cast<Type>(0);
	}

	template <typename Type> inline Mat43<Type>::Mat43(
	    Type m11, Type m21, Type m31, Type m41,
	    Type m12, Type m22, Type m32, Type m42,
	    Type m13, Type m23, Type m33, Type m43
	) {
		m_mat[0] = m11;
		m_mat[3] = m21;
		m_mat[6] = m31;
		m_mat[9] = m41;
		m_mat[1] = m12;
		m_mat[4] = m22;
		m_mat[7] = m32;
		m_mat[10] = m42;
		m_mat[2] = m13;
		m_mat[5] = m23;
		m_mat[8] = m33;
		m_mat[11] = m43;
	}

	template <typename Type> inline Mat43<Type>::Mat43(const Mat43<Type>& m) {
		m_mat[0] = m.m_mat[0];
		m_mat[3] = m.m_mat[3];
		m_mat[6] = m.m_mat[6];
		m_mat[9] = m.m_mat[9];
		m_mat[1] = m.m_mat[1];
		m_mat[4] = m.m_mat[4];
		m_mat[7] = m.m_mat[7];
		m_mat[10] = m.m_mat[10];
		m_mat[2] = m.m_mat[2];
		m_mat[5] = m.m_mat[5];
		m_mat[8] = m.m_mat[8];
		m_mat[11] = m.m_mat[11];
	}

	template <typename Type> inline Mat43<Type>::Mat43(const Mat43<Type>&& m) {
		m_mat[0] = std::move(m.m_mat[0]);
		m_mat[3] = std::move(m.m_mat[3]);
		m_mat[6] = std::move(m.m_mat[6]);
		m_mat[9] = std::move(m.m_mat[9]);
		m_mat[1] = std::move(m.m_mat[1]);
		m_mat[4] = std::move(m.m_mat[4]);
		m_mat[7] = std::move(m.m_mat[7]);
		m_mat[10] = std::move(m.m_mat[10]);
		m_mat[2] = std::move(m.m_mat[2]);
		m_mat[5] = std::move(m.m_mat[5]);
		m_mat[8] = std::move(m.m_mat[8]);
		m_mat[11] = std::move(m.m_mat[11]);
	}

	template <typename Type> inline Mat43<Type>::~Mat43(void) {}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::Identity(void) {
		m_mat[0] = static_cast<Type>(1);
		m_mat[3] = static_cast<Type>(0);
		m_mat[6] = static_cast<Type>(0);
		m_mat[9] = static_cast<Type>(0);
		m_mat[1] = static_cast<Type>(0);
		m_mat[4] = static_cast<Type>(1);
		m_mat[7] = static_cast<Type>(0);
		m_mat[10] = static_cast<Type>(0);
		m_mat[2] = static_cast<Type>(0);
		m_mat[5] = static_cast<Type>(0);
		m_mat[8] = static_cast<Type>(1);
		m_mat[11] = static_cast<Type>(0);

		return *this;
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::SetTrace(Type x, Type y, Type z) {
		m_mat[0] = x;
		m_mat[4] = y;
		m_mat[8] = z;

		return *this;
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::operator -() {
		Type m11 = m_mat[0], m12 = m_mat[3], m13 = m_mat[6], m14 = m_mat[9],
		     m21 = m_mat[1], m22 = m_mat[4], m23 = m_mat[7], m24 = m_mat[10],
		     m31 = m_mat[2], m32 = m_mat[5], m33 = m_mat[8], m34 = m_mat[11],

		     me0 = -m23 * m32 + m22 * m33,
		     me4 = m13 * m32 - m12 * m33,
		     me8 = -m13 * m22 + m12 * m23,
		     me12 = m14 * m23 * m32 - m13 * m24 * m32 - m14 * m22 * m33 + m12 * m24 * m33 + m13 * m22 * m34 - m12 * m23 * m34,

		     det = m11 * me0 + m21 * me4 + m31 * me8;

		if (det == static_cast<Type>(0)) {
			return Identity();
		}
		det = static_cast<Type>(1) / det;

		m_mat[0] = me0 * det;
		m_mat[3] = me4 * det;
		m_mat[6] = me8 * det;
		m_mat[9] = me12 * det;
		m_mat[1] = (m23 * m31 - m21 * m33) * det;
		m_mat[4] = (-m13 * m31 + m11 * m33) * det;
		m_mat[7] = (m13 * m21 - m11 * m23) * det;
		m_mat[10] = (m13 * m24 * m31 - m14 * m23 * m31 + m14 * m21 * m33 - m11 * m24 * m33 - m13 * m21 * m34 + m11 * m23 * m34) * det;
		m_mat[2] = (-m22 * m31 + m21 * m32) * det;
		m_mat[5] = (m12 * m31 - m11 * m32) * det;
		m_mat[8] = (-m12 * m21 + m11 * m22) * det;
		m_mat[11] = (m14 * m22 * m31 - m12 * m24 * m31 - m14 * m21 * m32 + m11 * m24 * m32 + m12 * m21 * m34 - m11 * m22 * m34) * det;

		return *this;
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::Inverse(void) {
		Type m11 = m_mat[0], m12 = m_mat[3], m13 = m_mat[6], m14 = m_mat[9],
		     m21 = m_mat[1], m22 = m_mat[4], m23 = m_mat[7], m24 = m_mat[10],
		     m31 = m_mat[2], m32 = m_mat[5], m33 = m_mat[8], m34 = m_mat[11],

		     me0 = -m23 * m32 + m22 * m33,
		     me4 = m13 * m32 - m12 * m33,
		     me8 = -m13 * m22 + m12 * m23,
		     me12 = m14 * m23 * m32 - m13 * m24 * m32 - m14 * m22 * m33 + m12 * m24 * m33 + m13 * m22 * m34 - m12 * m23 * m34,

		     det = m11 * me0 + m21 * me4 + m31 * me8;

		if (det == static_cast<Type>(0)) {
			return Identity();
		}
		det = static_cast<Type>(1) / det;

		m_mat[0] = me0 * det;
		m_mat[3] = me4 * det;
		m_mat[6] = me8 * det;
		m_mat[9] = me12 * det;
		m_mat[1] = (m23 * m31 - m21 * m33) * det;
		m_mat[4] = (-m13 * m31 + m11 * m33) * det;
		m_mat[7] = (m13 * m21 - m11 * m23) * det;
		m_mat[10] = (m13 * m24 * m31 - m14 * m23 * m31 + m14 * m21 * m33 - m11 * m24 * m33 - m13 * m21 * m34 + m11 * m23 * m34) * det;
		m_mat[2] = (-m22 * m31 + m21 * m32) * det;
		m_mat[5] = (m12 * m31 - m11 * m32) * det;
		m_mat[8] = (-m12 * m21 + m11 * m22) * det;
		m_mat[11] = (m14 * m22 * m31 - m12 * m24 * m31 - m14 * m21 * m32 + m11 * m24 * m32 + m12 * m21 * m34 - m11 * m22 * m34) * det;

		return *this;
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::Inverse(const Mat43<Type>& m) {
		Type m11 = m.m_mat[0], m12 = m.m_mat[3], m13 = m.m_mat[6], m14 = m.m_mat[9],
		     m21 = m.m_mat[1], m22 = m.m_mat[4], m23 = m.m_mat[7], m24 = m.m_mat[10],
		     m31 = m.m_mat[2], m32 = m.m_mat[5], m33 = m.m_mat[8], m34 = m.m_mat[11],

		     me0 = -m23 * m32 + m22 * m33,
		     me4 = m13 * m32 - m12 * m33,
		     me8 = -m13 * m22 + m12 * m23,
		     me12 = m14 * m23 * m32 - m13 * m24 * m32 - m14 * m22 * m33 + m12 * m24 * m33 + m13 * m22 * m34 - m12 * m23 * m34,

		     det = m11 * me0 + m21 * me4 + m31 * me8;

		if (det == static_cast<Type>(0)) {
			return Identity();
		}
		det = static_cast<Type>(1) / det;

		m_mat[0] = me0 * det;
		m_mat[3] = me4 * det;
		m_mat[6] = me8 * det;
		m_mat[9] = me12 * det;
		m_mat[1] = (m23 * m31 - m21 * m33) * det;
		m_mat[4] = (-m13 * m31 + m11 * m33) * det;
		m_mat[7] = (m13 * m21 - m11 * m23) * det;
		m_mat[10] = (m13 * m24 * m31 - m14 * m23 * m31 + m14 * m21 * m33 - m11 * m24 * m33 - m13 * m21 * m34 + m11 * m23 * m34) * det;
		m_mat[2] = (-m22 * m31 + m21 * m32) * det;
		m_mat[5] = (m12 * m31 - m11 * m32) * det;
		m_mat[8] = (-m12 * m21 + m11 * m22) * det;
		m_mat[11] = (m14 * m22 * m31 - m12 * m24 * m31 - m14 * m21 * m32 + m11 * m24 * m32 + m12 * m21 * m34 - m11 * m22 * m34) * det;

		return *this;
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::Transpose(void) {
		Type tmp;

		tmp = m_mat[1]; m_mat[1] = m_mat[3]; m_mat[3] = tmp;
		tmp = m_mat[2]; m_mat[2] = m_mat[6]; m_mat[6] = tmp;
		tmp = m_mat[5]; m_mat[5] = m_mat[10]; m_mat[10] = tmp;

		return *this;
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::Compose(const Vec3<Type>& position, const Vec3<Type>& scale, const Quat<Type>& rotation) {
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
		m_mat[3] = (xy - wz) * sy;
		m_mat[6] = (xz + wy) * sz;

		m_mat[1] = (xy + wz) * sx;
		m_mat[4] = (static_cast<Type>(1) - (xx + zz)) * sy;
		m_mat[7] = (yz - wx) * sz;

		m_mat[2] = (xz - wy) * sx;
		m_mat[5] = (yz + wx) * sy;
		m_mat[8] = (static_cast<Type>(1) - (xx + yy)) * sz;

		m_mat[9] = position.x;
		m_mat[10] = position.y;
		m_mat[11] = position.z;

		return *this;
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::Compose(const Vec3<Type>& position, const Quat<Type>& rotation) {
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
		m_mat[3] = (xy - wz);
		m_mat[6] = (xz + wy);

		m_mat[1] = (xy + wz);
		m_mat[4] = (static_cast<Type>(1) - (xx + zz));
		m_mat[7] = (yz - wx);

		m_mat[2] = (xz - wy);
		m_mat[5] = (yz + wx);
		m_mat[8] = (static_cast<Type>(1) - (xx + yy));

		m_mat[9] = position.x;
		m_mat[10] = position.y;
		m_mat[11] = position.z;

		return *this;
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::Decompose(Vec3<Type>& position, Vec3<Type>& scale, Quat<Type>& rotation) {
		Type m11 = m_mat[0],
		     m12 = m_mat[3],
		     m13 = m_mat[6],
		     m21 = m_mat[1],
		     m22 = m_mat[4],
		     m23 = m_mat[7],
		     m31 = m_mat[2],
		     m32 = m_mat[5],
		     m33 = m_mat[8],
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

		position.x = m_mat[9];
		position.y = m_mat[10];
		position.z = m_mat[11];

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

	template <typename Type> inline Mat43<Type>& Mat43<Type>::SetPosition(const Vec3<Type>& v) {

		m_mat[9] = v.x;
		m_mat[10] = v.y;
		m_mat[11] = v.z;

		return *this;
	}

	template <typename Type> inline Vec3<Type> Mat43<Type>::GetPosition(void) {

		return Vec3<Type>(m_mat[9], m_mat[10], m_mat[11]);
	}

	template <typename Type> inline Vec3<Type>& Mat43<Type>::GetPosition(Vec3<Type>& v) {

		v.x = m_mat[9];
		v.y = m_mat[10];
		v.z = m_mat[11];
	
		return v;
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::ExtractPosition(const Mat43<Type>& m) {

		m_mat[9] = m.m_mat[9];
		m_mat[10] = m.m_mat[10];
		m_mat[11] = m.m_mat[11];

		return *this;
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::ExtractRotation(const Mat43<Type>& m) {
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

	template <typename Type> inline Mat43<Type>& Mat43<Type>::ExtractRotationWithScale(const Mat43<Type>& m) {

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

	template <typename Type> inline Mat43<Type>& Mat43<Type>::Scale(const Vec2<Type>& v) {
		Type x = v.x, y = v.y;

		m_mat[0] *= x; m_mat[3] *= y;
		m_mat[1] *= x; m_mat[4] *= y;
		m_mat[2] *= x; m_mat[5] *= y;

		return *this;
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::Scale(const Vec3<Type>& v) {
		Type x = v.x, y = v.y, z = v.z;

		m_mat[0] *= x; m_mat[3] *= y; m_mat[6] *= z;
		m_mat[1] *= x; m_mat[4] *= y; m_mat[7] *= z;
		m_mat[2] *= x; m_mat[5] *= y; m_mat[8] *= z;

		return *this;
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::Scale(const Vec4<Type>& v) {
		Type x = v.x, y = v.y, z = v.z;

		m_mat[0] *= x; m_mat[3] *= y; m_mat[6] *= z;
		m_mat[1] *= x; m_mat[4] *= y; m_mat[7] *= z;
		m_mat[2] *= x; m_mat[5] *= y; m_mat[8] *= z;

		return *this;
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::RotateX(Type angle) {
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

	template <typename Type> inline Mat43<Type>& Mat43<Type>::RotateY(Type angle) {
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

	template <typename Type> inline Mat43<Type>& Mat43<Type>::RotateZ(Type angle) {
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

	template <typename Type> inline Mat43<Type>& Mat43<Type>::Rotate(Type x, Type y, Type z) {
		
		RotateZ(z);
		RotateX(x);
		RotateY(y);

		return *this;
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::FromQuat(const Quat<Type>& q) {
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

		m_mat[9] = static_cast<Type>(0);
		m_mat[10] = static_cast<Type>(0);
		m_mat[11] = static_cast<Type>(0);

		return *this;
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::Frustum(Type left, Type right, Type top, Type bottom, Type near, Type far) {
		Type x = static_cast<Type>(2) * near / (right - left),
		     y = static_cast<Type>(2) * near / (top - bottom),

		     a = (right + left) / (right - left),
		     b = (top + bottom) / (top - bottom),
		     c = -(far + near) / (far - near),
		     d = -static_cast<Type>(2) * far * near / (far - near);

		m_mat[0] = x;
		m_mat[3] = static_cast<Type>(0);
		m_mat[6] = a;
		m_mat[1] = static_cast<Type>(0);
		m_mat[4] = y;
		m_mat[7] = b;
		m_mat[2] = static_cast<Type>(0);
		m_mat[5] = static_cast<Type>(0);
		m_mat[8] = c;
		m_mat[9] = static_cast<Type>(0);
		m_mat[10] = static_cast<Type>(0);
		m_mat[11] = d;

		return *this;
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::Perspective(Type fov, Type aspect, Type near, Type far) {
		Type ymax = near * Mathf.Tan(fov * static_cast<Type>(0.5)),
		     ymin = -ymax,
		     xmin = ymin * aspect,
		     xmax = ymax * aspect;

		Frustum(xmin, xmax, ymax, ymin, near, far);
		return *this;
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::Orthographic(Type left, Type right, Type top, Type bottom, Type near, Type far) {
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
		m_mat[4] = static_cast<Type>(2) / h;
		m_mat[5] = static_cast<Type>(0);
		m_mat[6] = static_cast<Type>(0);
		m_mat[7] = static_cast<Type>(0);
		m_mat[8] = -static_cast<Type>(2) / p;
		m_mat[9] = -x;
		m_mat[10] = -y;
		m_mat[11] = -z;

		return *this;
	}

	template <typename Type> inline Type Mat43<Type>::operator [] (int32 i) const {
		return m_mat[i];
	}

	template <typename Type> inline Type& Mat43<Type>::operator [] (int32 i) {
		return m_mat[i];
	}

	template <typename Type> inline Mat43<Type> Mat43<Type>::operator *(const Vec2<Type>& v) {
		Type x = v.x, y = v.y;

		return Mat43<Type>(
		           m_mat[0], m_mat[3], m_mat[6], m_mat[0] * x + m_mat[3] * y + m_mat[9],
		           m_mat[1], m_mat[4], m_mat[7], m_mat[1] * x + m_mat[4] * y + m_mat[10],
		           m_mat[2], m_mat[5], m_mat[8], m_mat[2] * x + m_mat[5] * y + m_mat[11]
		       );
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::operator +=(const Vec2<Type>& v) {
		Type x = v.x, y = v.y;

		m_mat[9] = m_mat[0] * x + m_mat[3] * y + m_mat[9];
		m_mat[10] = m_mat[1] * x + m_mat[4] * y + m_mat[10];
		m_mat[11] = m_mat[2] * x + m_mat[5] * y + m_mat[11];

		return *this;
	}

	template <typename Type> inline Mat43<Type> Mat43<Type>::operator *(const Vec3<Type>& v) {
		Type x = v.x, y = v.y, z = v.z;

		return Mat43<Type>(
		           m_mat[0], m_mat[3], m_mat[6], m_mat[0] * x + m_mat[3] * y + m_mat[6] * z + m_mat[9],
		           m_mat[1], m_mat[4], m_mat[7], m_mat[1] * x + m_mat[4] * y + m_mat[7] * z + m_mat[10],
		           m_mat[2], m_mat[5], m_mat[8], m_mat[2] * x + m_mat[5] * y + m_mat[8] * z + m_mat[11]
		       );
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::operator *=(const Vec3<Type>& v) {
		Type x = v.x, y = v.y, z = v.z;

		m_mat[9] = m_mat[0] * x + m_mat[3] * y + m_mat[6] * z + m_mat[9];
		m_mat[10] = m_mat[1] * x + m_mat[4] * y + m_mat[7] * z + m_mat[10];
		m_mat[11] = m_mat[2] * x + m_mat[5] * y + m_mat[8] * z + m_mat[11];
	}

	template <typename Type> inline Mat43<Type> Mat43<Type>::operator *(const Vec4<Type>& v) {
		Type x = v.x, y = v.y, z = v.z;

		return Mat43<Type>(
		           m_mat[0], m_mat[3], m_mat[6], m_mat[0] * x + m_mat[3] * y + m_mat[6] * z + m_mat[9],
		           m_mat[1], m_mat[4], m_mat[7], m_mat[1] * x + m_mat[4] * y + m_mat[7] * z + m_mat[10],
		           m_mat[2], m_mat[5], m_mat[8], m_mat[2] * x + m_mat[5] * y + m_mat[8] * z + m_mat[11]
		       );
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::operator *=(const Vec4<Type>& v) {
		Type x = v.x, y = v.y, z = v.z;

		m_mat[9] = m_mat[0] * x + m_mat[3] * y + m_mat[6] * z + m_mat[9];
		m_mat[10] = m_mat[1] * x + m_mat[4] * y + m_mat[7] * z + m_mat[10];
		m_mat[11] = m_mat[2] * x + m_mat[5] * y + m_mat[8] * z + m_mat[11];

		return *this;
	}

	template <typename Type> inline Mat43<Type> Mat43<Type>::operator *(const Mat43<Type>& m) {
		Type a11 = m_mat[0], a12 = m_mat[3], a13 = m_mat[6], a14 = m_mat[9],
		     a21 = m_mat[1], a22 = m_mat[4], a23 = m_mat[7], a24 = m_mat[10],
		     a31 = m_mat[2], a32 = m_mat[5], a33 = m_mat[8], a34 = m_mat[11],

		     b11 = m.m_mat[0], b12 = m.m_mat[3], b13 = m.m_mat[6], b14 = m.m_mat[9],
		     b21 = m.m_mat[1], b22 = m.m_mat[4], b23 = m.m_mat[7], b24 = m.m_mat[10],
		     b31 = m.m_mat[2], b32 = m.m_mat[5], b33 = m.m_mat[8], b34 = m.m_mat[11];

		return Mat43<Type>(
		           a11 * b11 + a21 * b12 + a31 * b13,
		           a12 * b11 + a22 * b12 + a32 * b13,
		           a13 * b11 + a23 * b12 + a33 * b13,
				   a11 * b14 + a12 * b24 + a13 * b34 + a14,

		           a11 * b21 + a21 * b22 + a31 * b23,
		           a12 * b21 + a22 * b22 + a32 * b23,
		           a13 * b21 + a23 * b22 + a33 * b23,
				   a21 * b14 + a22 * b24 + a23 * b34 + a24,

		           a11 * b31 + a21 * b32 + a31 * b33,
		           a12 * b31 + a22 * b32 + a32 * b33,
		           a13 * b31 + a23 * b32 + a33 * b33,
				   a31 * b14 + a32 * b24 + a33 * b34 + a34
		       );
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::operator *=(const Mat43<Type>& m) {
		Type a11 = m_mat[0], a12 = m_mat[3], a13 = m_mat[6], a14 = m_mat[9],
		     a21 = m_mat[1], a22 = m_mat[4], a23 = m_mat[7], a24 = m_mat[10],
		     a31 = m_mat[2], a32 = m_mat[5], a33 = m_mat[8], a34 = m_mat[11],

		     b11 = m.m_mat[0], b12 = m.m_mat[3], b13 = m.m_mat[6], b14 = m.m_mat[9],
		     b21 = m.m_mat[1], b22 = m.m_mat[4], b23 = m.m_mat[7], b24 = m.m_mat[10],
		     b31 = m.m_mat[2], b32 = m.m_mat[5], b33 = m.m_mat[8], b34 = m.m_mat[11];

		m_mat[0] = a11 * b11 + a21 * b12 + a31 * b13;
		m_mat[3] = a12 * b11 + a22 * b12 + a32 * b13;
		m_mat[6] = a13 * b11 + a23 * b12 + a33 * b13;

		m_mat[1] = a11 * b21 + a21 * b22 + a31 * b23;
		m_mat[4] = a12 * b21 + a22 * b22 + a32 * b23;
		m_mat[7] = a13 * b21 + a23 * b22 + a33 * b23;

		m_mat[2] = a11 * b31 + a21 * b32 + a31 * b33;
		m_mat[5] = a12 * b31 + a22 * b32 + a32 * b33;
		m_mat[8] = a13 * b31 + a23 * b32 + a33 * b33;

		m_mat[9] = a11 * b14 + a12 * b24 + a13 * b34 + a14;
		m_mat[10] = a21 * b14 + a22 * b24 + a23 * b34 + a24;
		m_mat[11] = a31 * b14 + a32 * b24 + a33 * b34 + a34;

		return *this;
	}

	template <typename Type> inline Mat43<Type> Mat43<Type>::operator *(const Mat4<Type>& m) {
		Type a11 = m_mat[0], a12 = m_mat[3], a13 = m_mat[6], a14 = m_mat[9],
		     a21 = m_mat[1], a22 = m_mat[4], a23 = m_mat[7], a24 = m_mat[10],
		     a31 = m_mat[2], a32 = m_mat[5], a33 = m_mat[8], a34 = m_mat[11],

		     b11 = m.m_mat[0], b12 = m.m_mat[4], b13 = m.m_mat[8], b14 = m.m_mat[12],
		     b21 = m.m_mat[1], b22 = m.m_mat[5], b23 = m.m_mat[9], b24 = m.m_mat[13],
		     b31 = m.m_mat[2], b32 = m.m_mat[6], b33 = m.m_mat[10], b34 = m.m_mat[14],
		     b41 = m.m_mat[3], b42 = m.m_mat[7], b43 = m.m_mat[11], b44 = m.m_mat[15];

		return Mat43<Type>(
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
		           a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44
		       );
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::operator *=(const Mat4<Type>& m) {
		Type a11 = m_mat[0], a12 = m_mat[3], a13 = m_mat[6], a14 = m_mat[9],
		     a21 = m_mat[1], a22 = m_mat[4], a23 = m_mat[7], a24 = m_mat[10],
		     a31 = m_mat[2], a32 = m_mat[5], a33 = m_mat[8], a34 = m_mat[11],

		     b11 = m.m_mat[0], b12 = m.m_mat[4], b13 = m.m_mat[8], b14 = m.m_mat[12],
		     b21 = m.m_mat[1], b22 = m.m_mat[5], b23 = m.m_mat[9], b24 = m.m_mat[13],
		     b31 = m.m_mat[2], b32 = m.m_mat[6], b33 = m.m_mat[10], b34 = m.m_mat[14],
		     b41 = m.m_mat[3], b42 = m.m_mat[7], b43 = m.m_mat[11], b44 = m.m_mat[15];

		m_mat[0] = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41;
		m_mat[3] = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42;
		m_mat[6] = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43;
		m_mat[9] = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44;

		m_mat[1] = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41;
		m_mat[4] = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42;
		m_mat[7] = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43;
		m_mat[10] = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44;

		m_mat[2] = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41;
		m_mat[5] = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42;
		m_mat[8] = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43;
		m_mat[11] = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44;

		return *this;
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::operator *=(Type s) {
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

		return *this;
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::operator /=(Type s) {
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

		return *this;
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::operator =(const Mat43<Type>& m) {
		m_mat[0] = m.m_mat[0];
		m_mat[1] = m.m_mat[1];
		m_mat[2] = m.m_mat[2];
		m_mat[3] = m.m_mat[3];
		m_mat[4] = m.m_mat[4];
		m_mat[5] = m.m_mat[5];
		m_mat[6] = m.m_mat[6];
		m_mat[7] = m.m_mat[7];
		m_mat[8] = m.m_mat[8];
		m_mat[9] = m.m_mat[9];
		m_mat[10] = m.m_mat[10];
		m_mat[11] = m.m_mat[11];

		return *this;
	}

	template <typename Type> inline Mat43<Type>& Mat43<Type>::operator =(const Mat43<Type> && m) {
		m_mat[0] = std::move(m.m_mat[0]);
		m_mat[1] = std::move(m.m_mat[1]);
		m_mat[2] = std::move(m.m_mat[2]);
		m_mat[3] = std::move(m.m_mat[3]);
		m_mat[4] = std::move(m.m_mat[4]);
		m_mat[5] = std::move(m.m_mat[5]);
		m_mat[6] = std::move(m.m_mat[6]);
		m_mat[7] = std::move(m.m_mat[7]);
		m_mat[8] = std::move(m.m_mat[8]);
		m_mat[9] = std::move(m.m_mat[9]);
		m_mat[10] = std::move(m.m_mat[10]);
		m_mat[11] = std::move(m.m_mat[11]);

		return *this;
	}

	template <typename Type> inline bool Mat43<Type>::operator ==(const Mat43<Type>& m) {
		return !(
		           m_mat[0] != m.m_mat[0] || m_mat[3] != m.m_mat[3] || m_mat[6] != m.m_mat[6] || m_mat[9] != m.m_mat[9] ||
		           m_mat[1] != m.m_mat[1] || m_mat[4] != m.m_mat[4] || m_mat[7] != m.m_mat[7] || m_mat[10] != m.m_mat[10] ||
		           m_mat[2] != m.m_mat[2] || m_mat[5] != m.m_mat[5] || m_mat[8] != m.m_mat[8] || m_mat[11] != m.m_mat[11]
		       );
	}

	template <typename Type> inline bool Mat43<Type>::operator != (const Mat43<Type>& m) {
		return (
		           m_mat[0] != m.m_mat[0] || m_mat[3] != m.m_mat[3] || m_mat[6] != m.m_mat[6] || m_mat[9] != m.m_mat[9] ||
		           m_mat[1] != m.m_mat[1] || m_mat[4] != m.m_mat[4] || m_mat[7] != m.m_mat[7] || m_mat[10] != m.m_mat[10] ||
		           m_mat[2] != m.m_mat[2] || m_mat[5] != m.m_mat[5] || m_mat[8] != m.m_mat[8] || m_mat[11] != m.m_mat[11]
		       );
	}

	template <typename Type> inline std::string Mat43<Type>::ToString(int32 p) {

		return (
		           "Mat43[\n"
		           "  " + Odin::ToString(m_mat[0], p) + ", " + Odin::ToString(m_mat[3], p) + ", " + Odin::ToString(m_mat[6], p) + ", " + Odin::ToString(m_mat[9], p) + ",\n" +
		           "  " + Odin::ToString(m_mat[1], p) + ", " + Odin::ToString(m_mat[4], p) + ", " + Odin::ToString(m_mat[7], p) + ", " + Odin::ToString(m_mat[10], p) + ",\n" +
		           "  " + Odin::ToString(m_mat[2], p) + ", " + Odin::ToString(m_mat[5], p) + ", " + Odin::ToString(m_mat[8], p) + ", " + Odin::ToString(m_mat[11], p) + "\n" +
		           "]"
		       );
	}

	template <typename Type> inline Mat43<Type>& Mat43Inverse(const Mat43<Type>& a, Mat43<Type>& out) {
		Type m11 = a.m_mat[0], m12 = a.m_mat[3], m13 = a.m_mat[6], m14 = a.m_mat[9],
		     m21 = a.m_mat[1], m22 = a.m_mat[4], m23 = a.m_mat[7], m24 = a.m_mat[10],
		     m31 = a.m_mat[2], m32 = a.m_mat[5], m33 = a.m_mat[8], m34 = a.m_mat[11],

		     me0 = -m23 * m32 + m22 * m33,
		     me4 = m13 * m32 - m12 * m33,
		     me8 = -m13 * m22 + m12 * m23,
		     me12 = m14 * m23 * m32 - m13 * m24 * m32 - m14 * m22 * m33 + m12 * m24 * m33 + m13 * m22 * m34 - m12 * m23 * m34,

		     det = m11 * me0 + m21 * me4 + m31 * me8;

		if (det == static_cast<Type>(0)) {
			return out.Identity();
		}
		det = static_cast<Type>(1) / det;

		out.m_mat[0] = me0 * det;
		out.m_mat[3] = me4 * det;
		out.m_mat[6] = me8 * det;
		out.m_mat[9] = me12 * det;
		out.m_mat[1] = (m23 * m31 - m21 * m33) * det;
		out.m_mat[4] = (-m13 * m31 + m11 * m33) * det;
		out.m_mat[7] = (m13 * m21 - m11 * m23) * det;
		out.m_mat[10] = (m13 * m24 * m31 - m14 * m23 * m31 + m14 * m21 * m33 - m11 * m24 * m33 - m13 * m21 * m34 + m11 * m23 * m34) * det;
		out.m_mat[2] = (-m22 * m31 + m21 * m32) * det;
		out.m_mat[5] = (m12 * m31 - m11 * m32) * det;
		out.m_mat[8] = (-m12 * m21 + m11 * m22) * det;
		out.m_mat[11] = (m14 * m22 * m31 - m12 * m24 * m31 - m14 * m21 * m32 + m11 * m24 * m32 + m12 * m21 * m34 - m11 * m22 * m34) * det;

		return out;
	}

	template <typename Type> inline Mat43<Type>& Mat43Mul(const Mat43<Type>& a, const Mat43<Type>& b, Mat43<Type>& out) {
		Type a11 = a.m_mat[0], a12 = a.m_mat[3], a13 = a.m_mat[6], a14 = a.m_mat[9],
		     a21 = a.m_mat[1], a22 = a.m_mat[4], a23 = a.m_mat[7], a24 = a.m_mat[10],
		     a31 = a.m_mat[2], a32 = a.m_mat[5], a33 = a.m_mat[8], a34 = a.m_mat[11],

		     b11 = b.m_mat[0], b12 = b.m_mat[3], b13 = b.m_mat[6], b14 = b.m_mat[9],
		     b21 = b.m_mat[1], b22 = b.m_mat[4], b23 = b.m_mat[7], b24 = b.m_mat[10],
		     b31 = b.m_mat[2], b32 = b.m_mat[5], b33 = b.m_mat[8], b34 = b.m_mat[11];

		out.m_mat[0] = a11 * b11 + a21 * b12 + a31 * b13;
		out.m_mat[3] = a12 * b11 + a22 * b12 + a32 * b13;
		out.m_mat[6] = a13 * b11 + a23 * b12 + a33 * b13;

		out.m_mat[1] = a11 * b21 + a21 * b22 + a31 * b23;
		out.m_mat[4] = a12 * b21 + a22 * b22 + a32 * b23;
		out.m_mat[7] = a13 * b21 + a23 * b22 + a33 * b23;

		out.m_mat[2] = a11 * b31 + a21 * b32 + a31 * b33;
		out.m_mat[5] = a12 * b31 + a22 * b32 + a32 * b33;
		out.m_mat[8] = a13 * b31 + a23 * b32 + a33 * b33;

		out.m_mat[9] = a11 * b14 + a12 * b24 + a13 * b34 + a14;
		out.m_mat[10] = a21 * b14 + a22 * b24 + a23 * b34 + a24;
		out.m_mat[11] = a31 * b14 + a32 * b24 + a33 * b34 + a34;

		return out;
	}
}

#endif