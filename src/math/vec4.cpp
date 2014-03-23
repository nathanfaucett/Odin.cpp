#ifndef _ODIN_VEC4_CPP_
#define _ODIN_VEC4_CPP_

namespace Odin {

	template <typename Type> const Vec4<Type> Vec4<Type>::ZERO(0, 0, 0, 0);
	template <typename Type> const Vec4<Type> Vec4<Type>::UNIT_X(1, 0, 0, 0);
	template <typename Type> const Vec4<Type> Vec4<Type>::UNIT_Y(0, 1, 0, 0);
	template <typename Type> const Vec4<Type> Vec4<Type>::UNIT_Z(0, 0, 1, 0);
	template <typename Type> const Vec4<Type> Vec4<Type>::UNIT_W(0, 0, 0, 1);
	template <typename Type> const Vec4<Type> Vec4<Type>::NEGATIVE_UNIT_X(-1, 0, 0, 0);
	template <typename Type> const Vec4<Type> Vec4<Type>::NEGATIVE_UNIT_Y(0, -1, 0, 0);
	template <typename Type> const Vec4<Type> Vec4<Type>::NEGATIVE_UNIT_Z(0, 0, -1, 0);
	template <typename Type> const Vec4<Type> Vec4<Type>::NEGATIVE_UNIT_W(0, 0, 0, -1);
	template <typename Type> const Vec4<Type> Vec4<Type>::UNIT_SCALE(1, 1, 1, 1);

	template <typename Type> inline Vec4<Type>::Vec4(void) {
		x = 0;
		y = 0;
		z = 0;
		w = 1;
	}

	template <typename Type> inline Vec4<Type>::Vec4(Type X) {
		x = X;
		y = X;
		z = X;
		w = X;
	}

	template <typename Type> inline Vec4<Type>::Vec4(Type X, Type Y, Type Z) {
		x = X;
		y = Y;
		z = Z;
		w = 1;
	}

	template <typename Type> inline Vec4<Type>::Vec4(Type X, Type Y, Type Z, Type W) {
		x = X;
		y = Y;
		z = Z;
		w = W;
	}

	template <typename Type> inline Vec4<Type>::Vec4(const Vec2<Type>& v) {
		x = v.x;
		y = v.y;
		z = 0;
		w = 1;
	}

	template <typename Type> inline Vec4<Type>::Vec4(const Vec3<Type>& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = 1;
	}

	template <typename Type> inline Vec4<Type>::Vec4(const Vec4<Type>& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}

	template <typename Type> inline Vec4<Type>::Vec4(const Vec4<Type>&& v) {
		x = std::move(v.x);
		y = std::move(v.y);
		z = std::move(v.z);
		w = std::move(v.w);
	}

	template <typename Type> inline Vec4<Type>::Vec4(const Color<Type>& c) {
		x = c.r;
		y = c.g;
		z = c.b;
		w = 1;
	}

	template <typename Type> inline Vec4<Type>::~Vec4(void) {}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::Set(Type X, Type Y) {
		x = X;
		y = Y;

		return *this;
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::Set(Type X, Type Y, Type Z) {
		x = X;
		y = Y;
		z = Z;

		return *this;
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::Set(Type X, Type Y, Type Z, Type W) {
		x = X;
		y = Y;
		z = Z;
		w = W;

		return *this;
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::Zero(void) {
		x = 0;
		y = 0;
		z = 0;
		w = 0;

		return *this;
	}

	template <typename Type> inline Type Vec4<Type>::Dot(const Vec4<Type> v) {

		return x * v.x + y * v.y + z * v.z + w * v.w;
	}

	template <typename Type> inline Type Vec4<Type>::LengthSq(void) {

		return x * x + y * y + z * z + w * w;
	}

	template <typename Type> inline Type Vec4<Type>::Length(void) {
		Type lenSq = x * x + y * y + z * z + w * w;

		return lenSq == 0 ? 0 : sqrtf(lenSq);
	}

	template <typename Type> inline Type Vec4<Type>::Normalize(void) {
		Type lenSq = x * x + y * y + z * z + w * w;

		if (lenSq == 0) {
			return 0;
		}

		Type len = sqrtf(lenSq),
		     invLen = 1 / len;

		x *= invLen;
		y *= invLen;
		z *= invLen;
		w *= invLen;

		return len;
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::Lerp(const Vec4<Type>& v, Type t) {
		x = Mathf.Lerp(x, v.x, t);
		y = Mathf.Lerp(y, v.y, t);
		z = Mathf.Lerp(z, v.z, t);
		w = Mathf.Lerp(w, v.w, t);

		return *this;
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::Min(const Vec4<Type>& v) {
		Type vx = v.x,
		     vy = v.y,
		     vz = v.z,
		     vw = v.w;

		x = vx < x ? vx : x;
		y = vy < y ? vy : y;
		z = vz < z ? vz : z;
		w = vw > w ? vw : w;

		return *this;
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::Max(const Vec4<Type>& v) {
		Type vx = v.x,
		     vy = v.y,
		     vz = v.z,
		     vw = v.w;

		x = vx > x ? vx : x;
		y = vy > y ? vy : y;
		z = vz > z ? vz : z;
		w = vw > w ? vw : w;

		return *this;
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::operator -() {
		x = -x;
		y = -y;
		z = -z;
		w = -w;

		return *this;
	}

	template <typename Type> inline Type Vec4<Type>::operator [] (int32 i) const {
		return (&x)[i];
	}

	template <typename Type> inline Type& Vec4<Type>::operator [] (int32 i) {
		return (&x)[i];
	}

	template <typename Type> inline Vec4<Type> Vec4<Type>::operator +(const Vec4<Type>& v) {

		return Vec4(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	template <typename Type> inline Vec4<Type> Vec4<Type>::operator -(const Vec4<Type>& v) {

		return Vec4(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	template <typename Type> inline Vec4<Type> Vec4<Type>::operator *(const Vec4<Type>& v) {

		return Vec4(x * v.x, y * v.y, z * v.z, w * v.w);
	}

	template <typename Type> inline Vec4<Type> Vec4<Type>::operator /(const Vec4<Type>& v) {
		Type vx = v.x, vy = v.y, vz = v.y, vw = v.w;

		vx = vx != 0 ? 1 / vx : 0;
		vy = vy != 0 ? 1 / vy : 0;
		vz = vz != 0 ? 1 / vz : 0;
		vw = vw != 0 ? 1 / vw : 0;

		return Vec4(x * vx, y * vy, z * vz, w * vw);
	}

	template <typename Type> inline void Vec4<Type>::operator +=(const Vec4<Type>& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
	}

	template <typename Type> inline void Vec4<Type>::operator -=(const Vec4<Type>& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
	}

	template <typename Type> inline void Vec4<Type>::operator *=(const Vec4<Type>& v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		w *= v.w;
	}

	template <typename Type> inline void Vec4<Type>::operator /=(const Vec4<Type>& v) {
		Type vx = v.x, vy = v.y, vz = v.z, vw = v.w;

		x *= vx != 0 ? 1 / vx : 0;
		y *= vy != 0 ? 1 / vy : 0;
		z *= vz != 0 ? 1 / vz : 0;
		w *= vw != 0 ? 1 / vw : 0;
	}


	template <typename Type> inline Vec4<Type> Vec4<Type>::operator +(Type s) {

		return Vec4(x + s, y + s, z + s, w + s);
	}

	template <typename Type> inline Vec4<Type> Vec4<Type>::operator -(Type s) {

		return Vec4(x - s, y - s, z - s, w - s);
	}

	template <typename Type> inline Vec4<Type> Vec4<Type>::operator *(Type s) {

		return Vec4(x * s, y * s, z * s, w * s);
	}

	template <typename Type> inline Vec4<Type> Vec4<Type>::operator /(Type s) {
		Type d = s != 0 ? 1 / s : 0;

		return Vec4(x * d, y * d, z * d, w * d);
	}

	template <typename Type> inline void Vec4<Type>::operator +=(Type s) {
		x += s;
		y += s;
		z += s;
		w += s;
	}

	template <typename Type> inline void Vec4<Type>::operator -=(Type s) {
		x -= s;
		y -= s;
		z -= s;
		w -= s;
	}

	template <typename Type> inline void Vec4<Type>::operator *=(Type s) {
		x *= s;
		y *= s;
		z *= s;
		w *= s;
	}

	template <typename Type> inline void Vec4<Type>::operator /=(Type s) {
		Type d = s != 0 ? 1 / s : 0;

		x *= d;
		y *= d;
		z *= d;
		w *= d;
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::operator =(const Vec4<Type>& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;

		return *this;
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::operator =(const Vec4<Type> && v) {
		x = std::move(v.x);
		y = std::move(v.y);
		z = std::move(v.z);
		w = std::move(v.w);

		return *this;
	}

	template <typename Type> inline bool Vec4<Type>::operator ==(const Vec4<Type>& v) {

		return !(x != v.x || y != v.y || z != v.z || w != v.w);
	}

	template <typename Type> inline bool Vec4<Type>::operator !=(const Vec4<Type>& v) {

		return x != v.x || y != v.y || z != v.z || w != v.w;
	}

	template <typename Type> inline std::string Vec4<Type>::ToString(int32 p) {

		return "Vec4(" + util.ToString(x, p) + ", " + util.ToString(y, p) + ", " + util.ToString(z, p) + ", " + util.ToString(w, p) + ")";
	}
};

#endif