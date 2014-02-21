#ifndef ODIN_QUAT_H
#define ODIN_QUAT_H

namespace Odin {

	struct Quat {

		float x;
		float y;
		float z;
		float w;

		inline Quat(void);
		inline Quat(const float X, const float Y, const float Z);
		inline Quat(const float X, const float Y, const float Z, const float W);
		inline Quat(const Vec3& v);
		inline Quat(const Vec4& v);
		inline Quat(const Quat& q);
		inline ~Quat(void);

		inline Quat& Set(const float X, const float Y, const float Z);
		inline Quat& Set(const float X, const float Y, const float Z, const float W);
		inline Quat& Zero();

		inline float Dot(const Quat q);
		inline float LengthSq();
		inline float Length();
		inline float Normalize();

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

			if (cosom < 0) {
				cosom *= -1;
				bx *= -1;
				by *= -1;
				bz *= -1;
				bw *= -1;
			}

			if (1 - cosom > Mathf.Epsilon) {
				omega = std::acos(cosom);
				sinom = 1 / sin(omega);
				scale0 = std::sin((1 - t) * omega) * sinom;
				scale1 = std::sin(t * omega) * sinom;

			} else {
				scale0 = 1 - t;
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
		inline Quat Inverse();

		inline Quat& calculateW();

		inline Quat& RotateX(const float angle);
		inline Quat& RotateY(const float angle);
		inline Quat& RotateZ(const float angle);
		inline Quat& Rotate(const float x, const float y, const float z);
		inline Quat& LookRotation(const Vec3& forward, const Vec3& up);
		inline Quat& fromAxisAngle(const Vec3& axis, const float angle);
		inline Quat& fromVec3s(const Vec3& u, const Vec3& v);

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

		inline void operator =(const Quat& q);
		inline bool operator ==(const Quat& q);
		inline bool operator !=(const Quat& q);

		inline std::string ToString(int p = 5);
	};
};

#endif