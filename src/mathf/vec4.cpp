#ifndef ODIN_VEC4_CPP
#define ODIN_VEC4_CPP

namespace Odin {

	template <typename Type> Vec4<Type> Vec4<Type>::Right(static_cast<Type>(1), static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1));
	template <typename Type> Vec4<Type> Vec4<Type>::Forward(static_cast<Type>(0), static_cast<Type>(1), static_cast<Type>(0), static_cast<Type>(1));
	template <typename Type> Vec4<Type> Vec4<Type>::Up(static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1), static_cast<Type>(1));
	template <typename Type> Vec4<Type> Vec4<Type>::Left(-static_cast<Type>(1), static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1));
	template <typename Type> Vec4<Type> Vec4<Type>::Backward(static_cast<Type>(0), -static_cast<Type>(1), static_cast<Type>(0), static_cast<Type>(1));
	template <typename Type> Vec4<Type> Vec4<Type>::Down(static_cast<Type>(0), static_cast<Type>(0), -static_cast<Type>(1), static_cast<Type>(1));
	
	template <typename Type> inline Vec4<Type>::Vec4(void) {
		x = static_cast<Type>(0);
		y = static_cast<Type>(0);
		z = static_cast<Type>(0);
		w = static_cast<Type>(1);
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
		w = static_cast<Type>(1);
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
		z = static_cast<Type>(0);
		w = static_cast<Type>(1);
	}

	template <typename Type> inline Vec4<Type>::Vec4(const Vec3<Type>& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = static_cast<Type>(1);
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
		w = static_cast<Type>(1);
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
		x = static_cast<Type>(0);
		y = static_cast<Type>(0);
		z = static_cast<Type>(0);
		w = static_cast<Type>(0);

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

		return lenSq == static_cast<Type>(0) ? static_cast<Type>(0) : Mathf.Sqrt(lenSq);
	}

	template <typename Type> inline Type Vec4<Type>::Normalize(void) {
		Type lenSq = x * x + y * y + z * z + w * w;

		if (lenSq == static_cast<Type>(0)) {
			return static_cast<Type>(0);
		}

		Type len = Mathf.Sqrt(lenSq),
		     invLen = static_cast<Type>(1) / len;

		x *= invLen;
		y *= invLen;
		z *= invLen;
		w *= invLen;

		return len;
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::Lerp(const Vec4<Type>& v, float32 t) {
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

	template <typename Type> inline Vec4<Type>& Vec4<Type>::TransformProjection(const Mat4<Type>& m) {
		Type d = m[3] * x + m[7] * y + m[11] * z + m[15] * w;
		d = d != static_cast<Type>(0) ? static_cast<Type>(1) / d : static_cast<Type>(0);

		x = (m[0] * x + m[4] * y + m[8] * z + m[12] * w) * d;
		y = (m[1] * x + m[5] * y + m[9] * z + m[13] * w) * d;
		z = (m[2] * x + m[6] * y + m[10] * z + m[14] * w) * d;
		w = (m[3] * x + m[7] * y + m[11] * z + m[15] * w) * d;
		
		return *this;
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::operator -(void) {
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

	template <typename Type> inline Vec4<Type> Vec4<Type>::operator *(const Quat<Type>& q) {
		Type qx = q.x,
			 qy = q.y,
			 qz = q.z,
			 qw = q.w,

			 ix = qw * x + qy * z - qz * y,
			 iy = qw * y + qz * x - qx * z,
			 iz = qw * z + qx * y - qy * x,
			 iw = -qx * x - qy * y - qz * z;

		return Vec4<Type>(
		           ix * qw + iw * -qx + iy * -qz - iz * -qy,
		           iy * qw + iw * -qy + iz * -qx - ix * -qz,
		           iz * qw + iw * -qz + ix * -qy - iy * -qx,
				   static_cast<Type>(1)
		       );
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::operator *=(const Quat<Type>& q) {
		Type qx = q.x,
			 qy = q.y,
			 qz = q.z,
			 qw = q.w,

			 ix = qw * x + qy * z - qz * y,
			 iy = qw * y + qz * x - qx * z,
			 iz = qw * z + qx * y - qy * x,
			 iw = -qx * x - qy * y - qz * z;

		x = ix * qw + iw * -qx + iy * -qz - iz * -qy;
		y = iy * qw + iw * -qy + iz * -qx - ix * -qz;
		z = iz * qw + iw * -qz + ix * -qy - iy * -qx;

		return *this;
	}

	template <typename Type> inline Vec4<Type> Vec4<Type>::operator *(const Mat2<Type>& m) {

		return Vec4<Type>(
		           x * m[0] + y * m[2],
		           x * m[1] + y * m[3],
		           static_cast<Type>(0)
		       );
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::operator *=(const Mat2<Type>& m) {
		Type tx = x, ty = y;

		x = tx * m[0] + ty * m[2];
		y = tx * m[1] + ty * m[3];

		return *this;
	}

	template <typename Type> inline Vec4<Type> Vec4<Type>::operator *(const Mat32<Type>& m) {

		return Vec4<Type>(
		           x * m[0] + y * m[2] + m[4],
		           x * m[1] + y * m[3] + m[5],
		           static_cast<Type>(0)
		       );
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::operator *=(const Mat32<Type>& m) {
		Type tx = x, ty = y;

		x = tx * m[0] + ty * m[2] + m[4];
		y = tx * m[1] + ty * m[3] + m[5];

		return *this;
	}

	template <typename Type> inline Vec4<Type> Vec4<Type>::operator *(const Mat3<Type>& m) {

		return Vec4<Type>(
		           x * m[0] + y * m[3] + z * m[6],
		           x * m[1] + y * m[4] + z * m[7],
		           x * m[2] + y * m[5] + z * m[8],
		           static_cast<Type>(1)
		       );
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::operator *=(const Mat3<Type>& m) {
		Type tx = x, ty = y, tz = z;

		x = tx * m[0] + ty * m[3] + tz * m[6];
		y = tx * m[1] + ty * m[4] + tz * m[7];
		z = tx * m[2] + ty * m[5] + tz * m[8];

		return *this;
	}

	template <typename Type> inline Vec4<Type> Vec4<Type>::operator *(const Mat4<Type>& m) {

		return Vec4<Type>(
		           x * m[0] + y * m[4] + z * m[8] + m[12],
		           x * m[1] + y * m[5] + z * m[9] + m[13],
		           x * m[2] + y * m[6] + z * m[10] + m[14],
		           static_cast<Type>(1)
		       );
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::operator *=(const Mat4<Type>& m) {
		Type tx = x, ty = y, tz = z;

		x = tx * m[0] + ty * m[4] + tz * m[8] + m[12];
		y = tx * m[1] + ty * m[5] + tz * m[9] + m[13];
		z = tx * m[2] + ty * m[6] + tz * m[10] + m[14];

		return *this;
	}

	template <typename Type> inline Vec4<Type> Vec4<Type>::operator *(const Mat43<Type>& m) {

		return Vec4<Type>(
		           x * m[0] + y * m[3] + z * m[6] + m[9],
		           x * m[1] + y * m[4] + z * m[7] + m[10],
		           x * m[2] + y * m[5] + z * m[8] + m[11],
		           static_cast<Type>(1)
		       );
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::operator *=(const Mat43<Type>& m) {
		Type tx = x, ty = y, tz = z;

		x = tx * m[0] + ty * m[3] + tz * m[6] + m[9];
		y = tx * m[1] + ty * m[4] + tz * m[7] + m[10];
		z = tx * m[2] + ty * m[5] + tz * m[8] + m[11];

		return *this;
	}

	template <typename Type> inline Vec4<Type> Vec4<Type>::operator +(const Vec4<Type>& v) {

		return Vec4<Type>(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	template <typename Type> inline Vec4<Type> Vec4<Type>::operator -(const Vec4<Type>& v) {

		return Vec4<Type>(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	template <typename Type> inline Vec4<Type> Vec4<Type>::operator *(const Vec4<Type>& v) {

		return Vec4<Type>(x * v.x, y * v.y, z * v.z, w * v.w);
	}

	template <typename Type> inline Vec4<Type> Vec4<Type>::operator /(const Vec4<Type>& v) {
		Type vx = v.x, vy = v.y, vz = v.y, vw = v.w;

		vx = vx != static_cast<Type>(0) ? static_cast<Type>(1) / vx : static_cast<Type>(0);
		vy = vy != static_cast<Type>(0) ? static_cast<Type>(1) / vy : static_cast<Type>(0);
		vz = vz != static_cast<Type>(0) ? static_cast<Type>(1) / vz : static_cast<Type>(0);
		vw = vw != static_cast<Type>(0) ? static_cast<Type>(1) / vw : static_cast<Type>(0);

		return Vec4<Type>(x * vx, y * vy, z * vz, w * vw);
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::operator +=(const Vec4<Type>& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;

		return *this;
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::operator -=(const Vec4<Type>& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;

		return *this;
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::operator *=(const Vec4<Type>& v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		w *= v.w;

		return *this;
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::operator /=(const Vec4<Type>& v) {
		Type vx = v.x, vy = v.y, vz = v.z, vw = v.w;

		x *= vx != static_cast<Type>(0) ? static_cast<Type>(1) / vx : static_cast<Type>(0);
		y *= vy != static_cast<Type>(0) ? static_cast<Type>(1) / vy : static_cast<Type>(0);
		z *= vz != static_cast<Type>(0) ? static_cast<Type>(1) / vz : static_cast<Type>(0);
		w *= vw != static_cast<Type>(0) ? static_cast<Type>(1) / vw : static_cast<Type>(0);

		return *this;
	}


	template <typename Type> inline Vec4<Type> Vec4<Type>::operator +(Type s) {

		return Vec4<Type>(x + s, y + s, z + s, w + s);
	}

	template <typename Type> inline Vec4<Type> Vec4<Type>::operator -(Type s) {

		return Vec4<Type>(x - s, y - s, z - s, w - s);
	}

	template <typename Type> inline Vec4<Type> Vec4<Type>::operator *(Type s) {

		return Vec4<Type>(x * s, y * s, z * s, w * s);
	}

	template <typename Type> inline Vec4<Type> Vec4<Type>::operator /(Type s) {
		Type d = s != static_cast<Type>(0) ? static_cast<Type>(1) / s : static_cast<Type>(0);

		return Vec4<Type>(x * d, y * d, z * d, w * d);
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::operator +=(Type s) {
		x += s;
		y += s;
		z += s;
		w += s;

		return *this;
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::operator -=(Type s) {
		x -= s;
		y -= s;
		z -= s;
		w -= s;

		return *this;
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::operator *=(Type s) {
		x *= s;
		y *= s;
		z *= s;
		w *= s;

		return *this;
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::operator /=(Type s) {
		Type d = s != static_cast<Type>(0) ? static_cast<Type>(1) / s : static_cast<Type>(0);

		x *= d;
		y *= d;
		z *= d;
		w *= d;

		return *this;
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::operator =(const Vec2<Type>& v) {
		x = v.x;
		y = v.y;

		return *this;
	}
	template <typename Type> inline Vec4<Type>& Vec4<Type>::operator =(const Vec2<Type> && v) {
		x = std::move(v.x);
		y = std::move(v.y);

		return *this;
	}

	template <typename Type> inline Vec4<Type>& Vec4<Type>::operator =(const Vec3<Type>& v) {
		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}
	template <typename Type> inline Vec4<Type>& Vec4<Type>::operator =(const Vec3<Type> && v) {
		x = std::move(v.x);
		y = std::move(v.y);
		z = std::move(v.z);

		return *this;
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

		return "Vec4(" + Odin::ToString(x, p) + ", " + Odin::ToString(y, p) + ", " + Odin::ToString(z, p) + ", " + Odin::ToString(w, p) + ")";
	}
};

#endif