#ifndef ODIN_VEC4_CPP
#define ODIN_VEC4_CPP

namespace Odin {

	inline Vec4::Vec4(void) {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 1.0f;
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
		w = 1.0f;
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

	inline Vec4& Vec4::Zero(void) {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;

		return *this;
	}

	inline float Vec4::Dot(const Vec4 v) {

		return x * v.x + y * v.y + z * v.z + w * v.w;
	}

	inline float Vec4::LengthSq(void) {

		return x * x + y * y + z * z + w * w;
	}

	inline float Vec4::Length(void) {
		float lenSq = x * x + y * y + z * z + w * w;

		return lenSq == 0.0f ? 0.0f : sqrtf(lenSq);
	}

	inline float Vec4::Normalize(void) {
		float lenSq = x * x + y * y + z * z + w * w;

		if (lenSq == 0.0f) {
			return 0.0f;
		}

		float len = sqrtf(lenSq),
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
		float vx = v.x, vy = v.y, vz = v.z, vw = v.w;

		x *= vx != 0.0f ? 1.0f / vx : 0.0f;
		y *= vy != 0.0f ? 1.0f / vy : 0.0f;
		z *= vz != 0.0f ? 1.0f / vz : 0.0f;
		w *= vw != 0.0f ? 1.0f / vw : 0.0f;
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
		float d = s != 0.0f ? 1.0f / s : 0.0f;

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
		float d = s != 0.0f ? 1.0f / s : 0.0f;

		x *= d;
		y *= d;
		z *= d;
		w *= d;
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