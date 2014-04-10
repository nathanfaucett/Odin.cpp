#ifndef ODIN_VEC2_CPP
#define ODIN_VEC2_CPP

namespace Odin {

	template <typename Type> const Vec2<Type> Vec2<Type>::ZERO(0, 0);
	template <typename Type> const Vec2<Type> Vec2<Type>::UNIT_X(1, 0);
	template <typename Type> const Vec2<Type> Vec2<Type>::UNIT_Y(0, 1);
	template <typename Type> const Vec2<Type> Vec2<Type>::NEGATIVE_UNIT_X(-1, 0);
	template <typename Type> const Vec2<Type> Vec2<Type>::NEGATIVE_UNIT_Y(0, -1);
	template <typename Type> const Vec2<Type> Vec2<Type>::UNIT_SCALE(1, 1);

	template <typename Type> inline Vec2<Type>::Vec2(void) {
		x = 0;
		y = 0;
	}

	template <typename Type> inline Vec2<Type>::Vec2(Type X) {
		x = X;
		y = X;
	}

	template <typename Type> inline Vec2<Type>::Vec2(Type X, Type Y) {
		x = X;
		y = Y;
	}

	template <typename Type> inline Vec2<Type>::Vec2(const Vec2<Type>& v) {
		x = v.x;
		y = v.y;
	}

	template <typename Type> inline Vec2<Type>::Vec2(const Vec2<Type>&& v) {
		x = std::move(v.x);
		y = std::move(v.y);
	}

	template <typename Type> inline Vec2<Type>::Vec2(const Vec3<Type>& v) {
		x = v.x;
		y = v.y;
	}

	template <typename Type> inline Vec2<Type>::Vec2(const Vec4<Type>& v) {
		x = v.x;
		y = v.y;
	}

	template <typename Type> inline Vec2<Type>::Vec2(const Color<Type>& c) {
		x = c.r;
		y = c.g;
	}

	template <typename Type> inline Vec2<Type>::~Vec2(void) {}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::Set(Type X, Type Y) {
		x = X;
		y = Y;

		return *this;
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::Zero(void) {
		x = 0;
		y = 0;

		return *this;
	}

	template <typename Type> inline Type Vec2<Type>::Dot(const Vec2<Type>& v) {

		return x * v.x + y * v.y;
	}

	template <typename Type> inline Type Vec2<Type>::Cross(const Vec2<Type>& v) {

		return x * v.y - y * v.x;
	}

	template <typename Type> inline Type Vec2<Type>::LengthSq(void) {

		return x * x + y * y;
	}

	template <typename Type> inline Type Vec2<Type>::Length(void) {
		Type lenSq = x * x + y * y;

		return lenSq == 0 ? 0 : sqrtf(lenSq);
	}

	template <typename Type> inline Type Vec2<Type>::Normalize(void) {
		Type lenSq = x * x + y * y;

		if (lenSq == 0) {
			return 0;
		}

		Type len = sqrtf(lenSq), invLen = 1 / len;

		x *= invLen;
		y *= invLen;

		return len;
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::Lerp(const Vec2<Type>& v, Type t) {
		x = Mathf.Lerp(x, v.x, t);
		y = Mathf.Lerp(y, v.y, t);

		return *this;
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::Min(const Vec2<Type>& v) {
		Type vx = v.x,
		     vy = v.y;

		x = vx < x ? vx : x;
		y = vy < y ? vy : y;

		return *this;
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::Max(const Vec2<Type>& v) {
		Type vx = v.x,
		     vy = v.y;

		x = vx > x ? vx : x;
		y = vy > y ? vy : y;

		return *this;
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator -() {
		x = -x;
		y = -y;

		return *this;
	}

	template <typename Type> inline Type Vec2<Type>::operator [] (int32 i) const {
		return (&x)[i];
	}

	template <typename Type> inline Type& Vec2<Type>::operator [] (int32 i) {
		return (&x)[i];
	}

	template <typename Type> inline Vec2<Type> Vec2<Type>::operator *(const Mat2<Type>& m) {

		return Vec2(
		           x * m[0] + y * m[2],
		           x * m[1] + y * m[3]
		       );
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator *=(const Mat2<Type>& m) {
		Type tx = x, ty = y;

		x = tx * m[0] + ty * m[2];
		y = tx * m[1] + ty * m[3];

		return *this;
	}

	template <typename Type> inline Vec2<Type> Vec2<Type>::operator *(const Mat32<Type>& m) {

		return Vec2(
		           x * m[0] + y * m[2] + m[4],
		           x * m[1] + y * m[3] + m[5]
		       );
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator *=(const Mat32<Type>& m) {
		Type tx = x, ty = y;

		x = tx * m[0] + ty * m[2] + m[4];
		y = tx * m[1] + ty * m[3] + m[5];

		return *this;
	}

	template <typename Type> inline Vec2<Type> Vec2<Type>::operator *(const Mat4<Type>& m) {

		return Vec2(
		           x * m[0] + y * m[4] + m[12],
		           x * m[1] + y * m[5] + m[13]
		       );
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator *=(const Mat4<Type>& m) {
		Type tx = x, ty = y;

		x = tx * m[0] + ty * m[4] + m[12];
		y = tx * m[1] + ty * m[5] + m[13];

		return *this;
	}

	template <typename Type> inline Vec2<Type> Vec2<Type>::operator +(const Vec2<Type>& v) {

		return Vec2(x + v.x, y + v.y);
	}

	template <typename Type> inline Vec2<Type> Vec2<Type>::operator -(const Vec2<Type>& v) {

		return Vec2(x - v.x, y - v.y);
	}

	template <typename Type> inline Vec2<Type> Vec2<Type>::operator *(const Vec2<Type>& v) {

		return Vec2(x * v.x, y * v.y);
	}

	template <typename Type> inline Vec2<Type> Vec2<Type>::operator /(const Vec2<Type>& v) {
		Type vx = v.x, vy = v.y;

		vx = vx != 0 ? 1 / vx : 0;
		vy = vy != 0 ? 1 / vy : 0;

		return Vec2(x * vx, y * vy);
	}

	template <typename Type> inline void Vec2<Type>::operator +=(const Vec2<Type>& v) {
		x += v.x;
		y += v.y;
	}

	template <typename Type> inline void Vec2<Type>::operator -=(const Vec2<Type>& v) {
		x -= v.x;
		y -= v.y;
	}

	template <typename Type> inline void Vec2<Type>::operator *=(const Vec2<Type>& v) {
		x *= v.x;
		y *= v.y;
	}

	template <typename Type> inline void Vec2<Type>::operator /=(const Vec2<Type>& v) {
		Type vx = v.x, vy = v.y;

		x *= vx != 0 ? 1 / vx : 0;
		y *= vy != 0 ? 1 / vy : 0;
	}


	template <typename Type> inline Vec2<Type> Vec2<Type>::operator +(Type s) {

		return Vec2(x + s, y + s);
	}

	template <typename Type> inline Vec2<Type> Vec2<Type>::operator -(Type s) {

		return Vec2(x - s, y - s);
	}

	template <typename Type> inline Vec2<Type> Vec2<Type>::operator *(Type s) {

		return Vec2(x * s, y * s);
	}

	template <typename Type> inline Vec2<Type> Vec2<Type>::operator /(Type s) {
		Type d = s != 0 ? 1 / s : 0;

		return Vec2(x * d, y * d);
	}

	template <typename Type> inline void Vec2<Type>::operator +=(Type s) {
		x += s;
		y += s;
	}

	template <typename Type> inline void Vec2<Type>::operator -=(Type s) {
		x -= s;
		y -= s;
	}

	template <typename Type> inline void Vec2<Type>::operator *=(Type s) {
		x *= s;
		y *= s;
	}

	template <typename Type> inline void Vec2<Type>::operator /=(Type s) {
		Type d = s != 0 ? 1 / s : 0;

		x *= d;
		y *= d;
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator =(const Vec2<Type>& v) {
		x = v.x;
		y = v.y;

		return *this;
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator =(const Vec2<Type> && v) {
		x = std::move(v.x);
		y = std::move(v.y);

		return *this;
	}

	template <typename Type> inline bool Vec2<Type>::operator ==(const Vec2<Type>& v) {

		return !(x != v.x || y != v.y);
	}

	template <typename Type> inline bool Vec2<Type>::operator !=(const Vec2<Type>& v) {

		return x != v.x || y != v.y;
	}

	template <typename Type> inline std::string Vec2<Type>::ToString(int32 p) {

		return "Vec2(" + Util.ToString(x, p) + ", " + Util.ToString(y, p) + ")";
	}
}

#endif