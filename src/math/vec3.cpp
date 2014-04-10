#ifndef ODIN_VEC3_CPP
#define ODIN_VEC3_CPP

namespace Odin {

	template <typename Type> const Vec3<Type> Vec3<Type>::ZERO(0, 0, 0);
	template <typename Type> const Vec3<Type> Vec3<Type>::UNIT_X(1, 0, 0);
	template <typename Type> const Vec3<Type> Vec3<Type>::UNIT_Y(0, 1, 0);
	template <typename Type> const Vec3<Type> Vec3<Type>::UNIT_Z(0, 0, 1);
	template <typename Type> const Vec3<Type> Vec3<Type>::NEGATIVE_UNIT_X(-1, 0, 0);
	template <typename Type> const Vec3<Type> Vec3<Type>::NEGATIVE_UNIT_Y(0, -1, 0);
	template <typename Type> const Vec3<Type> Vec3<Type>::NEGATIVE_UNIT_Z(0, 0, -1);
	template <typename Type> const Vec3<Type> Vec3<Type>::UNIT_SCALE(1, 1, 1);

	template <typename Type> inline Vec3<Type>::Vec3(void) {
		x = 0;
		y = 0;
		z = 0;
	}

	template <typename Type> inline Vec3<Type>::Vec3(Type X) {
		x = X;
		y = X;
		z = X;
	}

	template <typename Type> inline Vec3<Type>::Vec3(Type X, Type Y) {
		x = X;
		y = Y;
		z = 0;
	}

	template <typename Type> inline Vec3<Type>::Vec3(Type X, Type Y, Type Z) {
		x = X;
		y = Y;
		z = Z;
	}

	template <typename Type> inline Vec3<Type>::Vec3(const Vec2<Type>& v) {
		x = v.x;
		y = v.y;
		z = 0;
	}

	template <typename Type> inline Vec3<Type>::Vec3(const Vec3<Type>& v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

	template <typename Type> inline Vec3<Type>::Vec3(const Vec3<Type>&& v) {
		x = std::move(v.x);
		y = std::move(v.y);
		z = std::move(v.z);
	}

	template <typename Type> inline Vec3<Type>::Vec3(const Vec4<Type>& v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

	template <typename Type> inline Vec3<Type>::Vec3(const Color<Type>& c) {
		x = c.r;
		y = c.g;
		z = c.b;
	}

	template <typename Type> inline Vec3<Type>::~Vec3(void) {}

	template <typename Type> inline Vec3<Type>& Vec3<Type>::Set(Type X, Type Y) {
		x = X;
		y = Y;

		return *this;
	}

	template <typename Type> inline Vec3<Type>& Vec3<Type>::Set(Type X, Type Y, Type Z) {
		x = X;
		y = Y;
		z = Z;

		return *this;
	}

	template <typename Type> inline Vec3<Type>& Vec3<Type>::Zero(void) {
		x = 0;
		y = 0;
		z = 0;

		return *this;
	}

	template <typename Type> inline Type Vec3<Type>::Dot(const Vec3<Type> v) {

		return x * v.x + y * v.y + z * v.z;
	}

	template <typename Type> inline Vec3<Type> Vec3<Type>::Cross(const Vec3<Type> v) {

		return Vec3(
		           y * v.z - z * v.y,
		           z * v.x - x * v.z,
		           x * v.y - y * v.x
		       );
	}

	template <typename Type> inline Type Vec3<Type>::LengthSq(void) {

		return x * x + y * y + z * z;
	}

	template <typename Type> inline Type Vec3<Type>::Length(void) {
		Type lenSq = x * x + y * y + z * z;

		return lenSq == 0 ? 0 : sqrtf(lenSq);
	}

	template <typename Type> inline Type Vec3<Type>::Normalize(void) {
		Type lenSq = x * x + y * y + z * z;

		if (lenSq == 0) {
			return 0;
		}

		Type len = sqrtf(lenSq), invLen = 1 / len;

		x *= invLen;
		y *= invLen;
		z *= invLen;

		return len;
	}

	template <typename Type> inline Vec3<Type>& Vec3<Type>::Lerp(const Vec3<Type>& v, Type t) {
		x = Mathf.Lerp(x, v.x, t);
		y = Mathf.Lerp(y, v.y, t);
		z = Mathf.Lerp(z, v.z, t);

		return *this;
	}

	template <typename Type> inline Vec3<Type>& Vec3<Type>::Min(const Vec3<Type>& v) {
		Type vx = v.x,
		     vy = v.y,
		     vz = v.z;

		x = vx < x ? vx : x;
		y = vy < y ? vy : y;
		z = vz < z ? vz : z;

		return *this;
	}

	template <typename Type> inline Vec3<Type>& Vec3<Type>::Max(const Vec3<Type>& v) {
		Type vx = v.x,
		     vy = v.y,
		     vz = v.z;

		x = vx > x ? vx : x;
		y = vy > y ? vy : y;
		z = vz > z ? vz : z;

		return *this;
	}

	template <typename Type> inline Vec3<Type>& Vec3<Type>::operator -() {
		x = -x;
		y = -y;
		z = -z;

		return *this;
	}

	template <typename Type> inline Type Vec3<Type>::operator [] (int32 i) const {
		return (&x)[i];
	}

	template <typename Type> inline Type& Vec3<Type>::operator [] (int32 i) {
		return (&x)[i];
	}

	template <typename Type> inline Vec3<Type> Vec3<Type>::operator *(const Mat2<Type>& m) {

		return Vec3(
		           x * m[0] + y * m[2],
		           x * m[1] + y * m[3],
		           0
		       );
	}

	template <typename Type> inline Vec3<Type>& Vec3<Type>::operator *=(const Mat2<Type>& m) {
		Type tx = x, ty = y;

		x = tx * m[0] + ty * m[2];
		y = tx * m[1] + ty * m[3];

		return *this;
	}

	template <typename Type> inline Vec3<Type> Vec3<Type>::operator *(const Mat32<Type>& m) {

		return Vec3(
		           x * m[0] + y * m[2] + m[4],
		           x * m[1] + y * m[3] + m[5],
		           0
		       );
	}

	template <typename Type> inline Vec3<Type>& Vec3<Type>::operator *=(const Mat32<Type>& m) {
		Type tx = x, ty = y;

		x = tx * m[0] + ty * m[2] + m[4];
		y = tx * m[1] + ty * m[3] + m[5];

		return *this;
	}

	template <typename Type> inline Vec3<Type> Vec3<Type>::operator *(const Mat4<Type>& m) {

		return Vec3(
		           x * m[0] + y * m[4] + z * m[8] + m[12],
		           x * m[1] + y * m[5] + z * m[9] + m[13],
		           x * m[2] + y * m[6] + z * m[10] + m[14]
		       );
	}

	template <typename Type> inline Vec3<Type>& Vec3<Type>::operator *=(const Mat4<Type>& m) {
		Type tx = x, ty = y, tz = z;

		x = tx * m[0] + ty * m[4] + tz * m[8] + m[12];
		y = tx * m[1] + ty * m[5] + tz * m[9] + m[13];
		z = tx * m[2] + ty * m[6] + tz * m[10] + m[14];

		return *this;
	}

	template <typename Type> inline Vec3<Type> Vec3<Type>::operator +(const Vec3<Type>& v) {

		return Vec3(x + v.x, y + v.y, z + v.z);
	}

	template <typename Type> inline Vec3<Type> Vec3<Type>::operator -(const Vec3<Type>& v) {

		return Vec3(x - v.x, y - v.y, z - v.z);
	}

	template <typename Type> inline Vec3<Type> Vec3<Type>::operator *(const Vec3<Type>& v) {

		return Vec3(x * v.x, y * v.y, z * v.z);
	}

	template <typename Type> inline Vec3<Type> Vec3<Type>::operator /(const Vec3<Type>& v) {
		Type vx = v.x, vy = v.y, vz = v.y;

		vx = vx != 0 ? 1 / vx : 0;
		vy = vy != 0 ? 1 / vy : 0;
		vz = vz != 0 ? 1 / vz : 0;

		return Vec3(x * vx, y * vy, z * vz);
	}

	template <typename Type> inline void Vec3<Type>::operator +=(const Vec3<Type>& v) {
		x += v.x;
		y += v.y;
		z += v.z;
	}

	template <typename Type> inline void Vec3<Type>::operator -=(const Vec3<Type>& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	template <typename Type> inline void Vec3<Type>::operator *=(const Vec3<Type>& v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
	}

	template <typename Type> inline void Vec3<Type>::operator /=(const Vec3<Type>& v) {
		Type vx = v.x, vy = v.y, vz = v.z;

		x *= vx != 0 ? 1 / vx : 0;
		y *= vy != 0 ? 1 / vy : 0;
		z *= vz != 0 ? 1 / vz : 0;
	}


	template <typename Type> inline Vec3<Type> Vec3<Type>::operator +(Type s) {

		return Vec3(x + s, y + s, z + s);
	}

	template <typename Type> inline Vec3<Type> Vec3<Type>::operator -(Type s) {

		return Vec3(x - s, y - s, z - s);
	}

	template <typename Type> inline Vec3<Type> Vec3<Type>::operator *(Type s) {

		return Vec3(x * s, y * s, z * s);
	}

	template <typename Type> inline Vec3<Type> Vec3<Type>::operator /(Type s) {
		Type d = s != 0 ? 1 / s : 0;

		return Vec3(x * d, y * d, z * d);
	}

	template <typename Type> inline void Vec3<Type>::operator +=(Type s) {
		x += s;
		y += s;
		z += s;
	}

	template <typename Type> inline void Vec3<Type>::operator -=(Type s) {
		x -= s;
		y -= s;
		z -= s;
	}

	template <typename Type> inline void Vec3<Type>::operator *=(Type s) {
		x *= s;
		y *= s;
		z *= s;
	}

	template <typename Type> inline void Vec3<Type>::operator /=(Type s) {
		Type d = s != 0 ? 1 / s : 0;

		x *= d;
		y *= d;
		z *= d;
	}

	template <typename Type> inline Vec3<Type>& Vec3<Type>::operator =(const Vec3<Type>& v) {
		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}

	template <typename Type> inline Vec3<Type>& Vec3<Type>::operator =(const Vec3<Type> && v) {
		x = std::move(v.x);
		y = std::move(v.y);
		z = std::move(v.z);

		return *this;
	}

	template <typename Type> inline bool Vec3<Type>::operator ==(const Vec3<Type>& v) {

		return !(x != v.x || y != v.y || z != v.z);
	}

	template <typename Type> inline bool Vec3<Type>::operator !=(const Vec3<Type>& v) {

		return x != v.x || y != v.y || z != v.z;
	}

	template <typename Type> inline std::string Vec3<Type>::ToString(int32 p) {

		return "Vec3(" + Util.ToString(x, p) + ", " + Util.ToString(y, p) + ", " + Util.ToString(z, p) + ")";
	}
}

#endif