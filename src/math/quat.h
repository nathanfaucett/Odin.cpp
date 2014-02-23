#ifndef ODIN_QUAT_H
#define ODIN_QUAT_H

namespace Odin {

	struct Quat {

		float x;
		float y;
		float z;
		float w;

		inline explicit Quat(void);
		inline explicit Quat(const float X, const float Y, const float Z);
		inline explicit Quat(const float X, const float Y, const float Z, const float W);
		inline Quat(const Vec3& v);
		inline Quat(const Vec3& v, const float angle);
		inline Quat(const Vec4& v);
		inline Quat(const Quat& q);
		inline Quat(const Quat&& q);
		inline ~Quat(void);

		inline Quat& Set(const float X, const float Y, const float Z);
		inline Quat& Set(const float X, const float Y, const float Z, const float W);
		inline Quat& Zero(void);

		inline float Dot(const Quat q);
		inline float LengthSq(void);
		inline float Length(void);
		inline float Normalize(void);

		inline Quat Lerp(const Quat& q, const float t);
		inline Quat& Slerp(const Quat& q, const float t);

		inline static Quat Lerp(const Quat& a, const Quat& b, const float t) {

			return Quat(
			           Mathf.Lerp(a.x, b.x, t),
			           Mathf.Lerp(a.y, b.y, t),
			           Mathf.Lerp(a.z, b.z, t),
			           Mathf.Lerp(a.w, b.w, t)
			       );
		}

		inline static Quat Slerp(const Quat& a, const Quat& b, const float t) {
			float ax = a.x,
			      ay = a.y,
			      az = a.z,
			      aw = a.w,
			      bx = b.x,
			      by = b.y,
			      bz = b.z,
			      bw = b.w,

			      omega, sinom, scale0, scale1,
			      cosom = ax * bx + ay * by + az * bz + aw * bw;

			if (cosom < 0.0f) {
				cosom *= -1.0f;
				bx *= -1.0f;
				by *= -1.0f;
				bz *= -1.0f;
				bw *= -1.0f;
			}

			if (1.0f - cosom > Mathf.Epsilon) {
				omega = acosf(cosom);
				sinom = 1.0f / sinf(omega);
				scale0 = sinf((1.0f - t) * omega) * sinom;
				scale1 = sinf(t * omega) * sinom;

			} else {
				scale0 = 1.0f - t;
				scale1 = t;
			}

			return Quat(
			           scale0 * ax + scale1 * bx,
			           scale0 * ay + scale1 * by,
			           scale0 * az + scale1 * bz,
			           scale0 * aw + scale1 * bw
			       );
		}

		inline static float Dot(const Quat& a, const Quat& b) {

			return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
		}

		inline Quat& FromMatrix(const Mat3& m);
		inline Quat& FromMatrix(const Mat4& m);

		inline Quat& operator -();
		inline Quat Inverse(void);

		inline Quat& calculateW(void);

		inline Quat& RotateX(const float angle);
		inline Quat& RotateY(const float angle);
		inline Quat& RotateZ(const float angle);
		inline Quat& Rotate(const float x, const float y, const float z);
		inline Quat& LookRotation(const Vec3& forward, const Vec3& up);
		inline Quat& FromAxisAngle(const Vec3& axis, const float angle);
		inline Quat& FromVec3s(const Vec3& u, const Vec3& v);

		inline float operator [] (int i) const;
		inline float& operator [] (int i);

		inline Quat operator +(const Quat& q);
		inline Quat operator -(const Quat& q);
		inline Quat operator *(const Quat& q);
		inline Quat operator /(const Quat& q);

		inline void operator +=(const Quat& q);
		inline void operator -=(const Quat& q);
		inline void operator *=(const Quat& q);
		inline void operator /=(const Quat& q);


		inline Quat operator +(const float s);
		inline Quat operator -(const float s);
		inline Quat operator *(const float s);
		inline Quat operator /(const float s);

		inline void operator +=(const float s);
		inline void operator -=(const float s);
		inline void operator *=(const float s);
		inline void operator /=(const float s);

		inline Quat& operator =(const Quat& q);
		inline Quat& operator =(const Quat && q);

		inline bool operator ==(const Quat& q);
		inline bool operator !=(const Quat& q);

		inline std::string ToString(int p = 5);
	};
};

#endif