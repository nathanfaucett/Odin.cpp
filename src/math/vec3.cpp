#ifndef _ODIN_VEC3_CPP
#define _ODIN_VEC3_CPP

namespace Odin {

	const Vec3 Vec3::ZERO(0.0f, 0.0f, 0.0f);
	const Vec3 Vec3::UNIT_X(1.0f, 0.0f, 0.0f);
	const Vec3 Vec3::UNIT_Y(0.0f, 1.0f, 0.0f);
	const Vec3 Vec3::UNIT_Z(0.0f, 0.0f, 1.0f);
	const Vec3 Vec3::NEGATIVE_UNIT_X(-1.0f, 0.0f, 0.0f);
	const Vec3 Vec3::NEGATIVE_UNIT_Y(0.0f, -1.0f, 0.0f);
	const Vec3 Vec3::NEGATIVE_UNIT_Z(0.0f, 0.0f, -1.0f);
	const Vec3 Vec3::UNIT_SCALE(1.0f, 1.0f, 1.0f);

	inline Vec3::Vec3(void) {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	inline Vec3::Vec3(float32 X) {
		x = X;
		y = X;
		z = X;
	}

	inline Vec3::Vec3(float32 X, float32 Y) {
		x = X;
		y = Y;
		z = 0.0f;
	}

	inline Vec3::Vec3(float32 X, float32 Y, float32 Z) {
		x = X;
		y = Y;
		z = Z;
	}

	inline Vec3::Vec3(const Vec2& v) {
		x = v.x;
		y = v.y;
		z = 0.0f;
	}

	inline Vec3::Vec3(const Vec3& v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

	inline Vec3::Vec3(const Vec3&& v) {
		x = std::move(v.x);
		y = std::move(v.y);
		z = std::move(v.z);
	}

	inline Vec3::Vec3(const Vec4& v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

	inline Vec3::Vec3(const Color& c) {
		x = c.r;
		y = c.g;
		z = c.b;
	}

	inline Vec3::~Vec3(void) {}

	inline Vec3& Vec3::Set(float32 X, float32 Y) {
		x = X;
		y = Y;

		return *this;
	}

	inline Vec3& Vec3::Set(float32 X, float32 Y, float32 Z) {
		x = X;
		y = Y;
		z = Z;

		return *this;
	}

	inline Vec3& Vec3::Zero(void) {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;

		return *this;
	}

	inline float32 Vec3::Dot(const Vec3 v) {

		return x * v.x + y * v.y + z * v.z;
	}

	inline Vec3 Vec3::Cross(const Vec3 v) {

		return Vec3(
		           y * v.z - z * v.y,
		           z * v.x - x * v.z,
		           x * v.y - y * v.x
		       );
	}

	inline float32 Vec3::LengthSq(void) {

		return x * x + y * y + z * z;
	}

	inline float32 Vec3::Length(void) {
		float32 lenSq = x * x + y * y + z * z;

		return lenSq == 0.0f ? 0.0f : sqrtf(lenSq);
	}

	inline float32 Vec3::Normalize(void) {
		float32 lenSq = x * x + y * y + z * z;

		if (lenSq == 0.0f) {
			return 0.0f;
		}

		float32 len = sqrtf(lenSq), invLen = 1.0f / len;

		x *= invLen;
		y *= invLen;
		z *= invLen;

		return len;
	}

	inline Vec3& Vec3::Lerp(const Vec3& v, float32 t) {
		x = Mathf.Lerp(x, v.x, t);
		y = Mathf.Lerp(y, v.y, t);
		z = Mathf.Lerp(z, v.z, t);

		return *this;
	}

	inline Vec3& Vec3::Min(const Vec3& v) {
		float32 vx = v.x,
		        vy = v.y,
		        vz = v.z;

		x = vx < x ? vx : x;
		y = vy < y ? vy : y;
		z = vz < z ? vz : z;

		return *this;
	}

	inline Vec3& Vec3::Max(const Vec3& v) {
		float32 vx = v.x,
		        vy = v.y,
		        vz = v.z;

		x = vx > x ? vx : x;
		y = vy > y ? vy : y;
		z = vz > z ? vz : z;

		return *this;
	}

	inline Vec3& Vec3::operator -() {
		x = -x;
		y = -y;
		z = -z;

		return *this;
	}

	inline float32 Vec3::operator [] (int32 i) const {
		return (&x)[i];
	}

	inline float32& Vec3::operator [] (int32 i) {
		return (&x)[i];
	}

	inline Vec3 Vec3::operator *(const Mat2& m) {

		return Vec3(
		           x * m[0] + y * m[2],
		           x * m[1] + y * m[3],
		           0.0f
		       );
	}

	inline Vec3& Vec3::operator *=(const Mat2& m) {
		float32 tx = x, ty = y;

		x = tx * m[0] + ty * m[2];
		y = tx * m[1] + ty * m[3];

		return *this;
	}

	inline Vec3 Vec3::operator *(const Mat32& m) {

		return Vec3(
		           x * m[0] + y * m[2] + m[4],
		           x * m[1] + y * m[3] + m[5],
		           0.0f
		       );
	}

	inline Vec3& Vec3::operator *=(const Mat32& m) {
		float32 tx = x, ty = y;

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
		float32 tx = x, ty = y, tz = z;

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
		float32 vx = v.x, vy = v.y, vz = v.y;

		vx = vx != 0.0f ? 1.0f / vx : 0.0f;
		vy = vy != 0.0f ? 1.0f / vy : 0.0f;
		vz = vz != 0.0f ? 1.0f / vz : 0.0f;

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
		float32 vx = v.x, vy = v.y, vz = v.z;

		x *= vx != 0.0f ? 1.0f / vx : 0.0f;
		y *= vy != 0.0f ? 1.0f / vy : 0.0f;
		z *= vz != 0.0f ? 1.0f / vz : 0.0f;
	}


	inline Vec3 Vec3::operator +(float32 s) {

		return Vec3(x + s, y + s, z + s);
	}

	inline Vec3 Vec3::operator -(float32 s) {

		return Vec3(x - s, y - s, z - s);
	}

	inline Vec3 Vec3::operator *(float32 s) {

		return Vec3(x * s, y * s, z * s);
	}

	inline Vec3 Vec3::operator /(float32 s) {
		float32 d = s != 0.0f ? 1.0f / s : 0.0f;

		return Vec3(x * d, y * d, z * d);
	}

	inline void Vec3::operator +=(float32 s) {
		x += s;
		y += s;
		z += s;
	}

	inline void Vec3::operator -=(float32 s) {
		x -= s;
		y -= s;
		z -= s;
	}

	inline void Vec3::operator *=(float32 s) {
		x *= s;
		y *= s;
		z *= s;
	}

	inline void Vec3::operator /=(float32 s) {
		float32 d = s != 0.0f ? 1.0f / s : 0.0f;

		x *= d;
		y *= d;
		z *= d;
	}

	inline Vec3& Vec3::operator =(const Vec3& v) {
		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}

	inline Vec3& Vec3::operator =(const Vec3 && v) {
		x = std::move(v.x);
		y = std::move(v.y);
		z = std::move(v.z);

		return *this;
	}

	inline bool Vec3::operator ==(const Vec3& v) {

		return !(x != v.x || y != v.y || z != v.z);
	}

	inline bool Vec3::operator !=(const Vec3& v) {

		return x != v.x || y != v.y || z != v.z;
	}

	inline std::string Vec3::ToString(int32 p) {

		return "Vec3(" + util.ToString(x, p) + ", " + util.ToString(y, p) + ", " + util.ToString(z, p) + ")";
	}
}

#endif