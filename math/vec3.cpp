#ifndef ODIN_VEC3_CPP
#define ODIN_VEC3_CPP

namespace Odin {

	inline Vec3::Vec3(void) {
		x = 0;
		y = 0;
		z = 0;
	}

	inline Vec3::Vec3(const float X) {
		x = X;
		y = X;
		z = X;
	}

	inline Vec3::Vec3(const float X, const float Y) {
		x = X;
		y = Y;
		z = 0;
	}

	inline Vec3::Vec3(const float X, const float Y, const float Z) {
		x = X;
		y = Y;
		z = Z;
	}

	inline Vec3::Vec3(const Vec2& v) {
		x = v.x;
		y = v.y;
		z = 0;
	}

	inline Vec3::Vec3(const Vec3& v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

	inline Vec3::~Vec3(void) {}

	inline Vec3& Vec3::Set(const float X, const float Y, const float Z) {
		x = X;
		y = Y;
		z = Z;

		return *this;
	}

	inline Vec3& Vec3::Zero() {
		x = 0;
		y = 0;
		z = 0;

		return *this;
	}

	inline float Vec3::Dot(const Vec3 v) {

		return x * v.x + y * v.y + z * v.z;
	}

	inline Vec3 Vec3::Cross(const Vec3 v) {

		return Vec3(
		           y * v.z - z * v.y,
		           z * v.x - x * v.z,
		           x * v.y - y * v.x
		       );
	}

	inline float Vec3::LengthSq() {

		return x * x + y * y + z * z;
	}

	inline float Vec3::Length() {
		float lenSq = x * x + y * y + z * z;

		return lenSq == 0 ? 0 : std::sqrt(lenSq);
	}

	inline float Vec3::Normalize() {
		float lenSq = x * x + y * y + z * z;

		if (lenSq == 0) {
			return 0;
		}

		float len = std::sqrt(lenSq), invLen = 1 / len;

		x *= invLen;
		y *= invLen;
		z *= invLen;

		return len;
	}

	inline Vec3& Vec3::Lerp(const Vec3& v, const float t) {
		x = Mathf.Lerp(x, v.x, t);
		y = Mathf.Lerp(y, v.y, t);
		z = Mathf.Lerp(z, v.z, t);

		return *this;
	}

	inline Vec3 Vec3::operator -() {
		x = -x;
		y = -y;
		z = -z;
	}

	inline float Vec3::operator [] (int i) const {
		return (&x)[i];
	}

	inline float& Vec3::operator [] (int i) {
		return (&x)[i];
	}

	inline Vec3 Vec3::operator *(const Mat2& m) {

		return Vec3(
		           x * m[0] + y * m[2],
		           x * m[1] + y * m[3],
		           0
		       );
	}

	inline Vec3& Vec3::operator *=(const Mat2& m) {
		float tx = x, ty = y;

		x = tx * m[0] + ty * m[2];
		y = tx * m[1] + ty * m[3];

		return *this;
	}

	inline Vec3 Vec3::operator *(const Mat32& m) {

		return Vec3(
		           x * m[0] + y * m[2] + m[4],
		           x * m[1] + y * m[3] + m[5],
		           0
		       );
	}

	inline Vec3& Vec3::operator *=(const Mat32& m) {
		float tx = x, ty = y;

		x = tx * m[0] + ty * m[2] + m[4];
		y = tx * m[1] + ty * m[3] + m[5];

		return *this;
	}

	inline Vec3 Vec3::operator *(const Mat4& m) {

		return Vec3(
		           x * m[0] + y * m[4] + z * m[8] + m[12],
		           x * m[1] + y * m[5] + z * m[9] + m[13],
		           x * m[2] + y * m[6] + z * m[10] + m[14]
		       );
	}

	inline Vec3& Vec3::operator *=(const Mat4& m) {
		float tx = x, ty = y, tz = z;

		x = tx * m[0] + ty * m[4] + tz * m[8] + m[12];
		y = tx * m[1] + ty * m[5] + tz * m[9] + m[13];
		z = tx * m[2] + ty * m[6] + tz * m[10] + m[14];

		return *this;
	}

	inline Vec3 Vec3::operator +(const Vec3& v) {

		return Vec3(x + v.x, y + v.y, z + v.z);
	}

	inline Vec3 Vec3::operator -(const Vec3& v) {

		return Vec3(x - v.x, y - v.y, z - v.z);
	}

	inline Vec3 Vec3::operator *(const Vec3& v) {

		return Vec3(x * v.x, y * v.y, z * v.z);
	}

	inline Vec3 Vec3::operator /(const Vec3& v) {
		float vx = v.x, vy = v.y, vz = v.y;

		vx = vx != 0 ? 1 / vx : 0;
		vy = vy != 0 ? 1 / vy : 0;
		vz = vz != 0 ? 1 / vz : 0;

		return Vec3(x * vx, y * vy, z * vz);
	}

	inline void Vec3::operator +=(const Vec3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
	}

	inline void Vec3::operator -=(const Vec3& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	inline void Vec3::operator *=(const Vec3& v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
	}

	inline void Vec3::operator /=(const Vec3& v) {
		float vx = v.x, vy = v.y, vz = v.z;

		x *= vx != 0 ? 1 / vx : 0;
		y *= vy != 0 ? 1 / vy : 0;
		z *= vz != 0 ? 1 / vz : 0;
	}


	inline Vec3 Vec3::operator +(const float s) {

		return Vec3(x + s, y + s, z + s);
	}

	inline Vec3 Vec3::operator -(const float s) {

		return Vec3(x - s, y - s, z - s);
	}

	inline Vec3 Vec3::operator *(const float s) {

		return Vec3(x * s, y * s, z * s);
	}

	inline Vec3 Vec3::operator /(const float s) {
		float d = s != 0 ? 1 / s : 0;

		return Vec3(x * d, y * d, z * d);
	}

	inline void Vec3::operator +=(const float s) {
		x += s;
		y += s;
		z += s;
	}

	inline void Vec3::operator -=(const float s) {
		x -= s;
		y -= s;
		z -= s;
	}

	inline void Vec3::operator *=(const float s) {
		x *= s;
		y *= s;
		z *= s;
	}

	inline void Vec3::operator /=(const float s) {
		float d = s != 0 ? 1 / s : 0;

		x *= d;
		y *= d;
		z *= d;
	}

	inline Vec3 Vec3::operator =(const Vec3& v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

	inline bool Vec3::operator ==(const Vec3& v) {

		return !(x != v.x || y != v.y || z != v.z);
	}

	inline bool Vec3::operator !=(const Vec3& v) {

		return x != v.x || y != v.y || z != v.z;
	}

	inline std::string Vec3::ToString(int p) {

		return "Vec3(" + util.ToString(x, p) + ", " + util.ToString(y, p) + ", " + util.ToString(z, p) + ")";
	}
}

#endif