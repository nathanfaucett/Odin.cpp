#ifndef ODIN_VEC4_CPP
#define ODIN_VEC4_CPP

namespace Odin {

	inline Vec4::Vec4(void) {
		x = 0;
		y = 0;
		z = 0;
		w = 1;
	}

	inline Vec4::Vec4(const float X) {
		x = X;
		y = X;
		z = X;
		w = X;
	}

	inline Vec4::Vec4(const float X, const float Y, const float Z) {
		x = X;
		y = Y;
		z = Z;
		w = 1;
	}

	inline Vec4::Vec4(const float X, const float Y, const float Z, const float W) {
		x = X;
		y = Y;
		z = Z;
		w = W;
	}

	inline Vec4::Vec4(const Vec2& v) {
		x = v.x;
		y = v.y;
		z = 0;
		w = 1;
	}

	inline Vec4::Vec4(const Vec3& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = 1;
	}

	inline Vec4::Vec4(const Vec4& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}

	inline Vec4::~Vec4(void) {}

	inline Vec4& Vec4::Set(const float X, const float Y, const float Z) {
		x = X;
		y = Y;
		z = Z;

		return *this;
	}

	inline Vec4& Vec4::Set(const float X, const float Y, const float Z, const float W) {
		x = X;
		y = Y;
		z = Z;
		w = W;

		return *this;
	}

	inline Vec4& Vec4::Zero() {
		x = 0;
		y = 0;
		z = 0;
		w = 0;

		return *this;
	}

	inline float Vec4::Dot(const Vec4 v) {

		return x * v.x + y * v.y + z * v.z + w * v.w;
	}

	inline float Vec4::LengthSq() {

		return x * x + y * y + z * z + w * w;
	}

	inline float Vec4::Length() {
		float lenSq = x * x + y * y + z * z + w * w;

		return lenSq == 0 ? 0 : std::sqrt(lenSq);
	}

	inline float Vec4::Normalize() {
		float lenSq = x * x + y * y + z * z + w * w;

		if (lenSq == 0) {
			return 0;
		}

		float len = std::sqrt(lenSq),
		      invLen = 1 / len;

		x *= invLen;
		y *= invLen;
		z *= invLen;
		w *= invLen;

		return len;
	}

	inline Vec4& Vec4::Lerp(const Vec4& v, const float t) {
		x = Mathf.Lerp(x, v.x, t);
		y = Mathf.Lerp(y, v.y, t);
		z = Mathf.Lerp(z, v.z, t);
		w = Mathf.Lerp(w, v.w, t);

		return *this;
	}

	inline Vec4 Vec4::operator -() {
		x = -x;
		y = -y;
		z = -z;
		w = -w;
	}

	inline float Vec4::operator [] (int i) const {
		return (&x)[i];
	}

	inline float& Vec4::operator [] (int i) {
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
		float vx = v.x, vy = v.y, vz = v.y, vw = v.w;

		vx = vx != 0 ? 1 / vx : 0;
		vy = vy != 0 ? 1 / vy : 0;
		vz = vz != 0 ? 1 / vz : 0;
		vw = vw != 0 ? 1 / vw : 0;

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
		float vx = v.x, vy = v.y, vz = v.z, vw = v.w;

		x *= vx != 0 ? 1 / vx : 0;
		y *= vy != 0 ? 1 / vy : 0;
		z *= vz != 0 ? 1 / vz : 0;
		w *= vw != 0 ? 1 / vw : 0;
	}


	inline Vec4 Vec4::operator +(const float s) {

		return Vec4(x + s, y + s, z + s, w + s);
	}

	inline Vec4 Vec4::operator -(const float s) {

		return Vec4(x - s, y - s, z - s, w - s);
	}

	inline Vec4 Vec4::operator *(const float s) {

		return Vec4(x * s, y * s, z * s, w * s);
	}

	inline Vec4 Vec4::operator /(const float s) {
		float d = s != 0 ? 1 / s : 0;

		return Vec4(x * d, y * d, z * d, w * d);
	}

	inline void Vec4::operator +=(const float s) {
		x += s;
		y += s;
		z += s;
		w += s;
	}

	inline void Vec4::operator -=(const float s) {
		x -= s;
		y -= s;
		z -= s;
		w -= s;
	}

	inline void Vec4::operator *=(const float s) {
		x *= s;
		y *= s;
		z *= s;
		w *= s;
	}

	inline void Vec4::operator /=(const float s) {
		float d = s != 0 ? 1 / s : 0;

		x *= d;
		y *= d;
		z *= d;
		w *= d;
	}

	inline Vec4 Vec4::operator =(const Vec4& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}

	inline bool Vec4::operator ==(const Vec4& v) {

		return !(x != v.x || y != v.y || z != v.z || w != v.w);
	}

	inline bool Vec4::operator !=(const Vec4& v) {

		return x != v.x || y != v.y || z != v.z || w != v.w;
	}

	inline std::string Vec4::ToString(int p) {

		return "Vec4(" + util.ToString(x, p) + ", " + util.ToString(y, p) + ", " + util.ToString(z, p) + ", " + util.ToString(w, p) + ")";
	}
};

#endif