#ifndef _ODIN_VEC4_CPP
#define _ODIN_VEC4_CPP

namespace Odin {

	const Vec4 Vec4::ZERO(0.0f, 0.0f, 0.0f, 0.0f);
	const Vec4 Vec4::UNIT_X(1.0f, 0.0f, 0.0f, 0.0f);
	const Vec4 Vec4::UNIT_Y(0.0f, 1.0f, 0.0f, 0.0f);
	const Vec4 Vec4::UNIT_Z(0.0f, 0.0f, 1.0f, 0.0f);
	const Vec4 Vec4::UNIT_W(0.0f, 0.0f, 0.0f, 1.0f);
	const Vec4 Vec4::NEGATIVE_UNIT_X(-1.0f, 0.0f, 0.0f, 0.0f);
	const Vec4 Vec4::NEGATIVE_UNIT_Y(0.0f, -1.0f, 0.0f, 0.0f);
	const Vec4 Vec4::NEGATIVE_UNIT_Z(0.0f, 0.0f, -1.0f, 0.0f);
	const Vec4 Vec4::NEGATIVE_UNIT_W(0.0f, 0.0f, 0.0f, -1.0f);
	const Vec4 Vec4::UNIT_SCALE(1.0f, 1.0f, 1.0f, 1.0f);

	inline Vec4::Vec4(void) {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 1.0f;
	}

	inline Vec4::Vec4(float32 X) {
		x = X;
		y = X;
		z = X;
		w = X;
	}

	inline Vec4::Vec4(float32 X, float32 Y, float32 Z) {
		x = X;
		y = Y;
		z = Z;
		w = 1.0f;
	}

	inline Vec4::Vec4(float32 X, float32 Y, float32 Z, float32 W) {
		x = X;
		y = Y;
		z = Z;
		w = W;
	}

	inline Vec4::Vec4(const Vec2& v) {
		x = v.x;
		y = v.y;
		z = 0.0f;
		w = 1.0f;
	}

	inline Vec4::Vec4(const Vec3& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = 1.0f;
	}

	inline Vec4::Vec4(const Vec4& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}

	inline Vec4::Vec4(const Vec4&& v) {
		x = std::move(v.x);
		y = std::move(v.y);
		z = std::move(v.z);
		w = std::move(v.w);
	}

	inline Vec4::Vec4(const Color& c) {
		x = c.r;
		y = c.g;
		z = c.b;
		w = 1.0f;
	}

	inline Vec4::~Vec4(void) {}

	inline Vec4& Vec4::Set(float32 X, float32 Y) {
		x = X;
		y = Y;

		return *this;
	}

	inline Vec4& Vec4::Set(float32 X, float32 Y, float32 Z) {
		x = X;
		y = Y;
		z = Z;

		return *this;
	}

	inline Vec4& Vec4::Set(float32 X, float32 Y, float32 Z, float32 W) {
		x = X;
		y = Y;
		z = Z;
		w = W;

		return *this;
	}

	inline Vec4& Vec4::Zero(void) {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;

		return *this;
	}

	inline float32 Vec4::Dot(const Vec4 v) {

		return x * v.x + y * v.y + z * v.z + w * v.w;
	}

	inline float32 Vec4::LengthSq(void) {

		return x * x + y * y + z * z + w * w;
	}

	inline float32 Vec4::Length(void) {
		float32 lenSq = x * x + y * y + z * z + w * w;

		return lenSq == 0.0f ? 0.0f : sqrtf(lenSq);
	}

	inline float32 Vec4::Normalize(void) {
		float32 lenSq = x * x + y * y + z * z + w * w;

		if (lenSq == 0.0f) {
			return 0.0f;
		}

		float32 len = sqrtf(lenSq),
		        invLen = 1.0f / len;

		x *= invLen;
		y *= invLen;
		z *= invLen;
		w *= invLen;

		return len;
	}

	inline Vec4& Vec4::Lerp(const Vec4& v, float32 t) {
		x = Mathf.Lerp(x, v.x, t);
		y = Mathf.Lerp(y, v.y, t);
		z = Mathf.Lerp(z, v.z, t);
		w = Mathf.Lerp(w, v.w, t);

		return *this;
	}

	inline Vec4& Vec4::Min(const Vec4& v) {
		float32 vx = v.x,
		        vy = v.y,
		        vz = v.z,
		        vw = v.w;

		x = vx < x ? vx : x;
		y = vy < y ? vy : y;
		z = vz < z ? vz : z;
		w = vw > w ? vw : w;

		return *this;
	}

	inline Vec4& Vec4::Max(const Vec4& v) {
		float32 vx = v.x,
		        vy = v.y,
		        vz = v.z,
		        vw = v.w;

		x = vx > x ? vx : x;
		y = vy > y ? vy : y;
		z = vz > z ? vz : z;
		w = vw > w ? vw : w;

		return *this;
	}

	inline Vec4& Vec4::operator -() {
		x = -x;
		y = -y;
		z = -z;
		w = -w;

		return *this;
	}

	inline float32 Vec4::operator [] (int32 i) const {
		return (&x)[i];
	}

	inline float32& Vec4::operator [] (int32 i) {
		return (&x)[i];
	}

	inline Vec4 Vec4::operator +(const Vec4& v) {

		return Vec4(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	inline Vec4 Vec4::operator -(const Vec4& v) {

		return Vec4(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	inline Vec4 Vec4::operator *(const Vec4& v) {

		return Vec4(x * v.x, y * v.y, z * v.z, w * v.w);
	}

	inline Vec4 Vec4::operator /(const Vec4& v) {
		float32 vx = v.x, vy = v.y, vz = v.y, vw = v.w;

		vx = vx != 0.0f ? 1.0f / vx : 0.0f;
		vy = vy != 0.0f ? 1.0f / vy : 0.0f;
		vz = vz != 0.0f ? 1.0f / vz : 0.0f;
		vw = vw != 0.0f ? 1.0f / vw : 0.0f;

		return Vec4(x * vx, y * vy, z * vz, w * vw);
	}

	inline void Vec4::operator +=(const Vec4& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
	}

	inline void Vec4::operator -=(const Vec4& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
	}

	inline void Vec4::operator *=(const Vec4& v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		w *= v.w;
	}

	inline void Vec4::operator /=(const Vec4& v) {
		float32 vx = v.x, vy = v.y, vz = v.z, vw = v.w;

		x *= vx != 0.0f ? 1.0f / vx : 0.0f;
		y *= vy != 0.0f ? 1.0f / vy : 0.0f;
		z *= vz != 0.0f ? 1.0f / vz : 0.0f;
		w *= vw != 0.0f ? 1.0f / vw : 0.0f;
	}


	inline Vec4 Vec4::operator +(float32 s) {

		return Vec4(x + s, y + s, z + s, w + s);
	}

	inline Vec4 Vec4::operator -(float32 s) {

		return Vec4(x - s, y - s, z - s, w - s);
	}

	inline Vec4 Vec4::operator *(float32 s) {

		return Vec4(x * s, y * s, z * s, w * s);
	}

	inline Vec4 Vec4::operator /(float32 s) {
		float32 d = s != 0.0f ? 1.0f / s : 0.0f;

		return Vec4(x * d, y * d, z * d, w * d);
	}

	inline void Vec4::operator +=(float32 s) {
		x += s;
		y += s;
		z += s;
		w += s;
	}

	inline void Vec4::operator -=(float32 s) {
		x -= s;
		y -= s;
		z -= s;
		w -= s;
	}

	inline void Vec4::operator *=(float32 s) {
		x *= s;
		y *= s;
		z *= s;
		w *= s;
	}

	inline void Vec4::operator /=(float32 s) {
		float32 d = s != 0.0f ? 1.0f / s : 0.0f;

		x *= d;
		y *= d;
		z *= d;
		w *= d;
	}

	inline Vec4& Vec4::operator =(const Vec4& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;

		return *this;
	}

	inline Vec4& Vec4::operator =(const Vec4 && v) {
		x = std::move(v.x);
		y = std::move(v.y);
		z = std::move(v.z);
		w = std::move(v.w);

		return *this;
	}

	inline bool Vec4::operator ==(const Vec4& v) {

		return !(x != v.x || y != v.y || z != v.z || w != v.w);
	}

	inline bool Vec4::operator !=(const Vec4& v) {

		return x != v.x || y != v.y || z != v.z || w != v.w;
	}

	inline std::string Vec4::ToString(int32 p) {

		return "Vec4(" + util.ToString(x, p) + ", " + util.ToString(y, p) + ", " + util.ToString(z, p) + ", " + util.ToString(w, p) + ")";
	}
};

#endif