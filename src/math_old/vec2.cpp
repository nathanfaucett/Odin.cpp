#ifndef _ODIN_VEC2_CPP_
#define _ODIN_VEC2_CPP_

namespace Odin {

	const Vec2 Vec2::ZERO(0.0f, 0.0f);
	const Vec2 Vec2::UNIT_X(1.0f, 0.0f);
	const Vec2 Vec2::UNIT_Y(0.0f, 1.0f);
	const Vec2 Vec2::NEGATIVE_UNIT_X(-1.0f, 0.0f);
	const Vec2 Vec2::NEGATIVE_UNIT_Y(0.0f, -1.0f);
	const Vec2 Vec2::UNIT_SCALE(1.0f, 1.0f);

	inline Vec2::Vec2(void) {
		x = 0.0f;
		y = 0.0f;
	}

	inline Vec2::Vec2(float32 X) {
		x = X;
		y = X;
	}

	inline Vec2::Vec2(float32 X, float32 Y) {
		x = X;
		y = Y;
	}

	inline Vec2::Vec2(const Vec2& v) {
		x = v.x;
		y = v.y;
	}

	inline Vec2::Vec2(const Vec2&& v) {
		x = std::move(v.x);
		y = std::move(v.y);
	}

	inline Vec2::Vec2(const Vec3& v) {
		x = v.x;
		y = v.y;
	}

	inline Vec2::Vec2(const Vec4& v) {
		x = v.x;
		y = v.y;
	}

	inline Vec2::Vec2(const Color& c) {
		x = c.r;
		y = c.g;
	}

	inline Vec2::~Vec2(void) {}

	inline Vec2& Vec2::Set(float32 X, float32 Y) {
		x = X;
		y = Y;

		return *this;
	}

	inline Vec2& Vec2::Zero(void) {
		x = 0.0f;
		y = 0.0f;

		return *this;
	}

	inline float32 Vec2::Dot(const Vec2& v) {

		return x * v.x + y * v.y;
	}

	inline float32 Vec2::Cross(const Vec2& v) {

		return x * v.y - y * v.x;
	}

	inline float32 Vec2::LengthSq(void) {

		return x * x + y * y;
	}

	inline float32 Vec2::Length(void) {
		float32 lenSq = x * x + y * y;

		return lenSq == 0.0f ? 0.0f : sqrtf(lenSq);
	}

	inline float32 Vec2::Normalize(void) {
		float32 lenSq = x * x + y * y;

		if (lenSq == 0.0f) {
			return 0.0f;
		}

		float32 len = sqrtf(lenSq), invLen = 1.0f / len;

		x *= invLen;
		y *= invLen;

		return len;
	}

	inline Vec2& Vec2::Lerp(const Vec2& v, float32 t) {
		x = Mathf.Lerp(x, v.x, t);
		y = Mathf.Lerp(y, v.y, t);

		return *this;
	}

	inline Vec2& Vec2::Min(const Vec2& v) {
		float32 vx = v.x,
		        vy = v.y;

		x = vx < x ? vx : x;
		y = vy < y ? vy : y;

		return *this;
	}

	inline Vec2& Vec2::Max(const Vec2& v) {
		float32 vx = v.x,
		        vy = v.y;

		x = vx > x ? vx : x;
		y = vy > y ? vy : y;

		return *this;
	}

	inline Vec2& Vec2::operator -() {
		x = -x;
		y = -y;

		return *this;
	}

	inline float32 Vec2::operator [] (int32 i) const {
		return (&x)[i];
	}

	inline float32& Vec2::operator [] (int32 i) {
		return (&x)[i];
	}

	inline Vec2 Vec2::operator *(const Mat2& m) {

		return Vec2(
		           x * m[0] + y * m[2],
		           x * m[1] + y * m[3]
		       );
	}

	inline Vec2& Vec2::operator *=(const Mat2& m) {
		float32 tx = x, ty = y;

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
		float32 tx = x, ty = y;

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
		float32 tx = x, ty = y;

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
		float32 vx = v.x, vy = v.y;

		vx = vx != 0.0f ? 1.0f / vx : 0.0f;
		vy = vy != 0.0f ? 1.0f / vy : 0.0f;

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
		float32 vx = v.x, vy = v.y;

		x *= vx != 0.0f ? 1.0f / vx : 0.0f;
		y *= vy != 0.0f ? 1.0f / vy : 0.0f;
	}


	inline Vec2 Vec2::operator +(float32 s) {

		return Vec2(x + s, y + s);
	}

	inline Vec2 Vec2::operator -(float32 s) {

		return Vec2(x - s, y - s);
	}

	inline Vec2 Vec2::operator *(float32 s) {

		return Vec2(x * s, y * s);
	}

	inline Vec2 Vec2::operator /(float32 s) {
		float32 d = s != 0.0f ? 1.0f / s : 0.0f;

		return Vec2(x * d, y * d);
	}

	inline void Vec2::operator +=(float32 s) {
		x += s;
		y += s;
	}

	inline void Vec2::operator -=(float32 s) {
		x -= s;
		y -= s;
	}

	inline void Vec2::operator *=(float32 s) {
		x *= s;
		y *= s;
	}

	inline void Vec2::operator /=(float32 s) {
		float32 d = s != 0.0f ? 1.0f / s : 0.0f;

		x *= d;
		y *= d;
	}

	inline Vec2& Vec2::operator =(const Vec2& v) {
		x = v.x;
		y = v.y;

		return *this;
	}

	inline Vec2& Vec2::operator =(const Vec2 && v) {
		x = std::move(v.x);
		y = std::move(v.y);

		return *this;
	}

	inline bool Vec2::operator ==(const Vec2& v) {

		return !(x != v.x || y != v.y);
	}

	inline bool Vec2::operator !=(const Vec2& v) {

		return x != v.x || y != v.y;
	}

	inline std::string Vec2::ToString(int32 p) {

		return "Vec2(" + util.ToString(x, p) + ", " + util.ToString(y, p) + ")";
	}
}

#endif