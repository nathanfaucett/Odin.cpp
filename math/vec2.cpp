#ifndef ODIN_VEC2_CPP
#define ODIN_VEC2_CPP

namespace Odin {

	inline Vec2::Vec2(void) {
		x = 0;
		y = 0;
	}

	inline Vec2::Vec2(const float X) {
		x = X;
		y = X;
	}

	inline Vec2::Vec2(const float X, const float Y) {
		x = X;
		y = Y;
	}

	inline Vec2::Vec2(const Vec2& v) {
		x = v.x;
		y = v.y;
	}

	inline Vec2::~Vec2(void) {}

	inline Vec2& Vec2::Set(const float X, const float Y) {
		x = X;
		y = Y;

		return *this;
	}

	inline Vec2& Vec2::Zero() {
		x = 0;
		y = 0;

		return *this;
	}

	inline float Vec2::Dot(const Vec2& v) {

		return x * v.x + y * v.y;
	}

	inline float Vec2::Cross(const Vec2& v) {

		return x * v.y - y * v.x;
	}

	inline float Vec2::LengthSq() {

		return x * x + y * y;
	}

	inline float Vec2::Length() {
		float lenSq = x * x + y * y;

		return lenSq == 0 ? 0 : std::sqrt(lenSq);
	}

	inline float Vec2::Normalize() {
		float lenSq = x * x + y * y;

		if (lenSq == 0) {
			return 0;
		}

		float len = std::sqrt(lenSq), invLen = 1 / len;

		x *= invLen;
		y *= invLen;

		return len;
	}

	inline Vec2& Vec2::Lerp(const Vec2& v, const float t) {
		x = Mathf.Lerp(x, v.x, t);
		y = Mathf.Lerp(y, v.y, t);

		return *this;
	}

	inline Vec2& Vec2::operator -() {
		x = -x;
		y = -y;

		return *this;
	}

	inline float Vec2::operator [] (int i) const {
		return (&x)[i];
	}

	inline float& Vec2::operator [] (int i) {
		return (&x)[i];
	}

	inline Vec2 Vec2::operator *(const Mat2& m) {

		return Vec2(
		           x * m[0] + y * m[2],
		           x * m[1] + y * m[3]
		       );
	}

	inline Vec2& Vec2::operator *=(const Mat2& m) {
		float tx = x, ty = y;

		x = tx * m[0] + ty * m[2];
		y = tx * m[1] + ty * m[3];

		return *this;
	}

	inline Vec2 Vec2::operator *(const Mat32& m) {

		return Vec2(
		           x * m[0] + y * m[2] + m[4],
		           x * m[1] + y * m[3] + m[5]
		       );
	}

	inline Vec2& Vec2::operator *=(const Mat32& m) {
		float tx = x, ty = y;

		x = tx * m[0] + ty * m[2] + m[4];
		y = tx * m[1] + ty * m[3] + m[5];

		return *this;
	}

	inline Vec2 Vec2::operator *(const Mat4& m) {

		return Vec2(
		           x * m[0] + y * m[4] + m[12],
		           x * m[1] + y * m[5] + m[13]
		       );
	}

	inline Vec2& Vec2::operator *=(const Mat4& m) {
		float tx = x, ty = y;

		x = tx * m[0] + ty * m[4] + m[12];
		y = tx * m[1] + ty * m[5] + m[13];

		return *this;
	}

	inline Vec2 Vec2::operator +(const Vec2& v) {

		return Vec2(x + v.x, y + v.y);
	}

	inline Vec2 Vec2::operator -(const Vec2& v) {

		return Vec2(x - v.x, y - v.y);
	}

	inline Vec2 Vec2::operator *(const Vec2& v) {

		return Vec2(x * v.x, y * v.y);
	}

	inline Vec2 Vec2::operator /(const Vec2& v) {
		float vx = v.x, vy = v.y;

		vx = vx != 0 ? 1 / vx : 0;
		vy = vy != 0 ? 1 / vy : 0;

		return Vec2(x * vx, y * vy);
	}

	inline void Vec2::operator +=(const Vec2& v) {
		x += v.x;
		y += v.y;
	}

	inline void Vec2::operator -=(const Vec2& v) {
		x -= v.x;
		y -= v.y;
	}

	inline void Vec2::operator *=(const Vec2& v) {
		x *= v.x;
		y *= v.y;
	}

	inline void Vec2::operator /=(const Vec2& v) {
		float vx = v.x, vy = v.y;

		x *= vx != 0 ? 1 / vx : 0;
		y *= vy != 0 ? 1 / vy : 0;
	}


	inline Vec2 Vec2::operator +(const float s) {

		return Vec2(x + s, y + s);
	}

	inline Vec2 Vec2::operator -(const float s) {

		return Vec2(x - s, y - s);
	}

	inline Vec2 Vec2::operator *(const float s) {

		return Vec2(x * s, y * s);
	}

	inline Vec2 Vec2::operator /(const float s) {
		float d = s != 0 ? 1 / s : 0;

		return Vec2(x * d, y * d);
	}

	inline void Vec2::operator +=(const float s) {
		x += s;
		y += s;
	}

	inline void Vec2::operator -=(const float s) {
		x -= s;
		y -= s;
	}

	inline void Vec2::operator *=(const float s) {
		x *= s;
		y *= s;
	}

	inline void Vec2::operator /=(const float s) {
		float d = s != 0 ? 1 / s : 0;

		x *= d;
		y *= d;
	}

	inline Vec2 Vec2::operator =(const Vec2& v) {
		x = v.x;
		y = v.y;
	}

	inline bool Vec2::operator ==(const Vec2& v) {

		return !(x != v.x || y != v.y);
	}

	inline bool Vec2::operator !=(const Vec2& v) {

		return x != v.x || y != v.y;
	}

	inline std::string Vec2::ToString(int p) {

		return "Vec2(" + util.ToString(x, p) + ", " + util.ToString(y, p) + ")";
	}
}

#endif