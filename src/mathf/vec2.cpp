#ifndef ODIN_VEC2_CPP
#define ODIN_VEC2_CPP

namespace Odin {

	template <typename Type> Vec2<Type> Vec2<Type>::Right(static_cast<Type>(1), static_cast<Type>(0));
	template <typename Type> Vec2<Type> Vec2<Type>::Up(static_cast<Type>(0), static_cast<Type>(1));
	template <typename Type> Vec2<Type> Vec2<Type>::Left(-static_cast<Type>(1), static_cast<Type>(0));
	template <typename Type> Vec2<Type> Vec2<Type>::Down(static_cast<Type>(0), -static_cast<Type>(1));

	template <typename Type> inline Vec2<Type>::Vec2(void) {
		x = static_cast<Type>(0);
		y = static_cast<Type>(0);
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
		x = static_cast<Type>(0);
		y = static_cast<Type>(0);

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

		return lenSq == static_cast<Type>(0) ? static_cast<Type>(0) : Mathf.Sqrt(lenSq);
	}

	template <typename Type> inline Type Vec2<Type>::Normalize(void) {
		Type lenSq = x * x + y * y;

		if (lenSq == static_cast<Type>(0)) {
			return static_cast<Type>(0);
		}

		Type len = Mathf.Sqrt(lenSq), invLen = static_cast<Type>(1) / len;

		x *= invLen;
		y *= invLen;

		return len;
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::Lerp(const Vec2<Type>& v, float32 t) {
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

	template <typename Type> inline Vec2<Type>& Vec2<Type>::TransformProjection(const Mat4<Type>& m) {
		Type d = m[3] * x + m[7] * y + m[15];
		d = d != static_cast<Type>(0) ? static_cast<Type>(1) / d : static_cast<Type>(0);

		x = (m[0] * x + m[4] * y + m[12]) * d;
		y = (m[1] * x + m[5] * y + m[13]) * d;
		
		return *this;
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator -(void) {
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

	template <typename Type> inline Vec2<Type> Vec2<Type>::operator *(const Quat<Type>& q) {
		Type qx = q.x,
			 qy = q.y,
			 qz = q.z,
			 qw = q.w,

			 ix = qw * x + qy - qz * y,
			 iy = qw * y + qz * x - qx,
			 iz = qw + qx * y - qy * x,
			 iw = -qx * x - qy * y - qz;

		return Vec2<Type>(
		           ix * qw + iw * -qx + iy * -qz - iz * -qy,
		           iy * qw + iw * -qy + iz * -qx - ix * -qz
		       );
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator *=(const Quat<Type>& q) {
		Type qx = q.x,
			 qy = q.y,
			 qz = q.z,
			 qw = q.w,

			 ix = qw * x + qy - qz * y,
			 iy = qw * y + qz * x - qx,
			 iz = qw + qx * y - qy * x,
			 iw = -qx * x - qy * y - qz;
		
		x = ix * qw + iw * -qx + iy * -qz - iz * -qy;
		y = iy * qw + iw * -qy + iz * -qx - ix * -qz;

		return *this;
	}

	template <typename Type> inline Vec2<Type> Vec2<Type>::operator *(const Mat2<Type>& m) {

		return Vec2<Type>(
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

		return Vec2<Type>(
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

		return Vec2<Type>(
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

	template <typename Type> inline Vec2<Type> Vec2<Type>::operator *(const Mat43<Type>& m) {

		return Vec2<Type>(
		           x * m[0] + y * m[3] + m[9],
		           x * m[1] + y * m[4] + m[10]
		       );
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator *=(const Mat43<Type>& m) {
		Type tx = x, ty = y;

		x = tx * m[0] + ty * m[3] + m[9];
		y = tx * m[1] + ty * m[4] + m[10];

		return *this;
	}

	template <typename Type> inline Vec2<Type> Vec2<Type>::operator +(const Vec2<Type>& v) {

		return Vec2<Type>(x + v.x, y + v.y);
	}

	template <typename Type> inline Vec2<Type> Vec2<Type>::operator -(const Vec2<Type>& v) {

		return Vec2<Type>(x - v.x, y - v.y);
	}

	template <typename Type> inline Vec2<Type> Vec2<Type>::operator *(const Vec2<Type>& v) {

		return Vec2<Type>(x * v.x, y * v.y);
	}

	template <typename Type> inline Vec2<Type> Vec2<Type>::operator /(const Vec2<Type>& v) {
		Type vx = v.x, vy = v.y;

		vx = vx != static_cast<Type>(0) ? static_cast<Type>(1) / vx : static_cast<Type>(0);
		vy = vy != static_cast<Type>(0) ? static_cast<Type>(1) / vy : static_cast<Type>(0);

		return Vec2<Type>(x * vx, y * vy);
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator +=(const Vec2<Type>& v) {
		x += v.x;
		y += v.y;

		return *this;
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator -=(const Vec2<Type>& v) {
		x -= v.x;
		y -= v.y;

		return *this;
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator *=(const Vec2<Type>& v) {
		x *= v.x;
		y *= v.y;

		return *this;
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator /=(const Vec2<Type>& v) {
		Type vx = v.x, vy = v.y;

		x *= vx != static_cast<Type>(0) ? static_cast<Type>(1) / vx : static_cast<Type>(0);
		y *= vy != static_cast<Type>(0) ? static_cast<Type>(1) / vy : static_cast<Type>(0);

		return *this;
	}

	template <typename Type> inline Vec2<Type> Vec2<Type>::operator +(const Vec3<Type>& v) {

		return Vec2<Type>(x + v.x, y + v.y);
	}

	template <typename Type> inline Vec2<Type> Vec2<Type>::operator -(const Vec3<Type>& v) {

		return Vec2<Type>(x - v.x, y - v.y);
	}

	template <typename Type> inline Vec2<Type> Vec2<Type>::operator *(const Vec3<Type>& v) {

		return Vec2<Type>(x * v.x, y * v.y);
	}

	template <typename Type> inline Vec2<Type> Vec2<Type>::operator /(const Vec3<Type>& v) {
		Type vx = v.x, vy = v.y;

		vx = vx != static_cast<Type>(0) ? static_cast<Type>(1) / vx : static_cast<Type>(0);
		vy = vy != static_cast<Type>(0) ? static_cast<Type>(1) / vy : static_cast<Type>(0);

		return Vec2<Type>(x * vx, y * vy);
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator +=(const Vec3<Type>& v) {
		x += v.x;
		y += v.y;

		return *this;
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator -=(const Vec3<Type>& v) {
		x -= v.x;
		y -= v.y;

		return *this;
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator *=(const Vec3<Type>& v) {
		x *= v.x;
		y *= v.y;

		return *this;
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator /=(const Vec3<Type>& v) {
		Type vx = v.x, vy = v.y;

		x *= vx != static_cast<Type>(0) ? static_cast<Type>(1) / vx : static_cast<Type>(0);
		y *= vy != static_cast<Type>(0) ? static_cast<Type>(1) / vy : static_cast<Type>(0);

		return *this;
	}


	template <typename Type> inline Vec2<Type> Vec2<Type>::operator +(Type s) {

		return Vec2<Type>(x + s, y + s);
	}

	template <typename Type> inline Vec2<Type> Vec2<Type>::operator -(Type s) {

		return Vec2<Type>(x - s, y - s);
	}

	template <typename Type> inline Vec2<Type> Vec2<Type>::operator *(Type s) {

		return Vec2<Type>(x * s, y * s);
	}

	template <typename Type> inline Vec2<Type> Vec2<Type>::operator /(Type s) {
		Type d = s != static_cast<Type>(0) ? static_cast<Type>(1) / s : static_cast<Type>(0);

		return Vec2<Type>(x * d, y * d);
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator +=(Type s) {
		x += s;
		y += s;
		
		return *this;
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator -=(Type s) {
		x -= s;
		y -= s;
		
		return *this;
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator *=(Type s) {
		x *= s;
		y *= s;
		
		return *this;
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator /=(Type s) {
		Type d = s != static_cast<Type>(0) ? static_cast<Type>(1) / s : static_cast<Type>(0);

		x *= d;
		y *= d;
		
		return *this;
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

	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator =(const Vec3<Type>& v) {
		x = v.x;
		y = v.y;

		return *this;
	}
	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator =(const Vec3<Type> && v) {
		x = std::move(v.x);
		y = std::move(v.y);

		return *this;
	}

	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator =(const Vec4<Type>& v) {
		x = v.x;
		y = v.y;

		return *this;
	}
	template <typename Type> inline Vec2<Type>& Vec2<Type>::operator =(const Vec4<Type> && v) {
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

		return "Vec2(" + Odin::ToString(x, p) + ", " + Odin::ToString(y, p) + ")";
	}
}

#endif