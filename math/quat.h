#ifndef ODIN_QUAT_H
#define ODIN_QUAT_H

namespace Odin{
	
	struct Quat{
		
		float x;
        float y;
        float z;
        float w;
		
		inline Quat(void) {
            x = 0;
            y = 0;
            z = 0;
            w = 1;
        }
		
		inline Quat(const float X, const float Y, const float Z) {
            x = X;
            y = Y;
            z = Z;
            w = 1;
        }
		
		inline Quat(const float X, const float Y, const float Z, const float W) {
            x = X;
            y = Y;
            z = Z;
            w = W;
        }
		
		inline Quat(const Vec3& v) {
            x = v.x;
            y = v.y;
            z = v.z;
			w = 1;
        }
		
		inline Quat(const Vec4& v) {
            x = v.x;
            y = v.y;
            z = v.z;
			w = v.w;
        }
		
		inline Quat(const Quat& q) {
            x = q.x;
            y = q.y;
            z = q.z;
            w = q.w;
        }
		
		inline ~Quat(void) {}
		
		inline Quat& Set(const float X, const float Y, const float Z) {
            x = X;
            y = Y;
            z = Z;
			
			return *this;
        }
		
		inline Quat& Set(const float X, const float Y, const float Z, const float W) {
            x = X;
            y = Y;
            z = Z;
			w = W;
			
			return *this;
        }
        
        inline Quat& Zero() {
            x = 0;
            y = 0;
            z = 0;
			w = 0;
			
			return *this;
        }
        
        inline float Dot(const Quat q) {
			
            return x * q.x + y * q.y + z * q.z + w * q.w;
        }
        
        inline float LengthSq() {
			
            return x * x + y * y + z * z + w * w;
        }
        
        inline float Length() {
            float lenSq = x * x + y * y + z * z + w * w;
            
            return lenSq == 0 ? 0 : std::sqrt(lenSq);
        }
        
        inline float Normalize() {
            float lenSq = x * x + y * y + z * z + w * w;
            
            if(lenSq == 0) return 0;
            
            float len = std::sqrt(lenSq),
				invLen = 1 / len;
            
            x *= invLen;
            y *= invLen;
            z *= invLen;
            w *= invLen;
            
            return len;
        }
        
        inline Quat Lerp(const Quat& q, const float t) {
            x = Mathf.Lerp(x, q.x, t);
            y = Mathf.Lerp(y, q.y, t);
            z = Mathf.Lerp(z, q.z, t);
            w = Mathf.Lerp(w, q.w, t);
			
			return *this;
        }
        
        inline Quat& Slerp(const Quat& q, const float t) {
            float ax = x,
                ay = y,
                az = z,
                aw = w,
                bx = q.x,
                by = q.y,
                bz = q.z,
                bw = q.w,

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
                sinom = 1 / std::sin(omega);
                scale0 = std::sin((1 - t) * omega) * sinom;
                scale1 = std::sin(t * omega) * sinom;
            } else {
                scale0 = 1 - t;
                scale1 = t;
            }

            x = scale0 * ax + scale1 * bx;
            y = scale0 * ay + scale1 * by;
            z = scale0 * az + scale1 * bz;
            w = scale0 * aw + scale1 * bw;
			
			return *this;
        }
        
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
        
        inline Quat& FromMatrix(const Mat3& m);
		
        inline Quat& FromMatrix(const Mat4& m);
        
        inline static float Dot(const Quat& a, const Quat& b) {
			
            return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
        }
        
        inline Quat& operator -() {
			float lenSq = x * x + y * y + z * z + w * w;
            
			if (lenSq == 0 || lenSq == 1) {
				x = -x;
				y = -y;
				z = -z;
				return *this;
			}
            
            float len = std::sqrt(lenSq),
				invLen = 1 / len;
			
            x *= -invLen;
            y *= -invLen;
            z *= -invLen;
			w *= invLen;
			
			return *this;
        }
        
        inline Quat Inverse() {
			float lenSq = x * x + y * y + z * z + w * w;
            
			if (lenSq == 0 || lenSq == 1) {
				return Quat(-x, -y, -z, w);
			}
            
            float len = std::sqrt(lenSq),
				invLen = 1 / len;
			
			return Quat(
				-x * invLen,
				-y * invLen,
				-z * invLen,
				w * invLen
			);
        }
        
        inline Quat& calculateW() {

            w = -std::sqrt(abs(1 - x * x - y * y - z * z));
			
			return *this;
        }
        
        inline Quat& RotateX(const float angle) {
			float halfAngle = angle * 0.5,
                ax = x,
                ay = y,
                az = z,
                aw = w,
                s = std::sin(halfAngle),
                c = std::cos(halfAngle);

            x = ax * c + aw * s;
            y = ay * c + az * s;
            z = az * c - ay * s;
            w = aw * c - ax * s;
			
			return *this;
        }
        
        inline Quat& RotateY(const float angle) {
			float halfAngle = angle * 0.5,
                ax = x,
                ay = y,
                az = z,
                aw = w,
                s = std::sin(halfAngle),
                c = std::cos(halfAngle);

            x = ax * c - az * s;
            y = ay * c + aw * s;
            z = az * c + ax * s;
            w = aw * c - ay * s;
			
			return *this;
        }
        
        inline Quat& RotateZ(const float angle) {
			float halfAngle = angle * 0.5,
                ax = x,
                ay = y,
                az = z,
                aw = w,
                s = std::sin(halfAngle),
                c = std::cos(halfAngle);

            x = ax * c + ay * s;
            y = ay * c - ax * s;
            z = az * c + aw * s;
            w = aw * c - az * s;
			
			return *this;
        }
        
        inline Quat& Rotate(const float x, const float y, const float z) {
			
			RotateZ(z);
			RotateX(x);
			RotateY(y);
			
			return *this;
        }
        
        inline Quat& LookRotation(const Vec3& forward, const Vec3& up) {
			float fx = forward.x,
                fy = forward.y,
                fz = forward.z,
                ux = up.x,
                uy = up.y,
                uz = up.z,

                ax = uy * fz - uz * fy,
                ay = uz * fx - ux * fz,
                az = ux * fy - uy * fx,

                d = (1 + ux * fx + uy * fy + uz * fz) * 2,
                dsq = d * d,
                s = 1 / dsq;

            x = ax * s;
            y = ay * s;
            z = az * s;
            w = dsq * 0.5;
			
			return *this;
        }
        
        inline Quat& fromAxisAngle(const Vec3& axis, const float angle) {
			float halfAngle = angle * 0.5,
                s = std::sin(halfAngle);

            x = axis.x * s;
            y = axis.y * s;
            z = axis.z * s;
            w = cos(halfAngle);

            return *this;
        }
        
        inline Quat& fromVec3s(const Vec3& u, const Vec3& v) {
			Vec3 a = Vec3::Cross(u, v);
			float ux = u.x,
				uy = u.y,
				uz = u.z,
				
				vx = v.x,
				vy = v.y,
				vz = v.z,

			x = a.x;
			y = a.y;
			z = a.z;
			w = std::sqrt((ux * ux + uy * uy + uz * uz) * (vx * vx + vy * vy + vz * vz)) + (ux * vx + uy * vy + uz * vz);
			Normalize();
			
			return *this;
        }
        
        inline float operator [] (int i) const {
            return (&x)[i];
        }
        
        inline float& operator [] (int i) {
            return (&x)[i];
        }
        
        inline Quat operator +(const Quat& q) {
			
            return Quat(x + q.x, y + q.y, z + q.z, w + q.w);
        }
        
        inline Quat operator -(const Quat& q) {
			
            return Quat(x - q.x, y - q.y, z - q.z, w - q.w);
        }
        
        inline Quat operator *(const Quat& q) {
			float ax = x,
                ay = y,
                az = z,
                aw = w,
                bx = q.x,
                by = q.y,
                bz = q.z,
                bw = q.w;
			
            return Quat(
				ax * bw + aw * bx + ay * bz - az * by,
				ay * bw + aw * by + az * bx - ax * bz,
				az * bw + aw * bz + ax * by - ay * bx,
				aw * bw - ax * bx - ay * by - az * bz
			);
        }
        
        inline Quat operator /(const Quat& q) {
            float ax = x,
                ay = y,
                az = z,
                aw = w,
                bx = -q.x,
                by = -q.y,
                bz = -q.z,
                bw = q.w;
			
            return Quat(
				ax * bw + aw * bx + ay * bz - az * by,
				ay * bw + aw * by + az * bx - ax * bz,
				az * bw + aw * bz + ax * by - ay * bx,
				-(aw * bw - ax * bx - ay * by - az * bz)
			);
        }
        
        inline void operator +=(const Quat& q) {
            x += q.x;
            y += q.y;
            z += q.z;
            w += q.w;
        }
        
        inline void operator -=(const Quat& q) {
            x -= q.x;
            y -= q.y;
            z -= q.z;
            w -= q.w;
        }
        
        inline void operator *=(const Quat& q) {
			float ax = x,
                ay = y,
                az = z,
                aw = w,
                bx = q.x,
                by = q.y,
                bz = q.z,
                bw = q.w;

            x = ax * bw + aw * bx + ay * bz - az * by;
            y = ay * bw + aw * by + az * bx - ax * bz;
            z = az * bw + aw * bz + ax * by - ay * bx;
            w = aw * bw - ax * bx - ay * by - az * bz;
        }
        
        inline void operator /=(const Quat& q) {
            float ax = x,
                ay = y,
                az = z,
                aw = w,
                bx = -q.x,
                by = -q.y,
                bz = -q.z,
                bw = q.w;

            x = ax * bw + aw * bx + ay * bz - az * by;
            y = ay * bw + aw * by + az * bx - ax * bz;
            z = az * bw + aw * bz + ax * by - ay * bx;
            w = -(aw * bw - ax * bx - ay * by - az * bz);
        }
        
        
        inline Quat operator +(const float s) {
			
            return Quat(x + s, y + s, z + s, w + s);
        }
        
        inline Quat operator -(const float s) {
			
            return Quat(x - s, y - s, z - s, w - s);
        }
        
        inline Quat operator *(const float s) {
			
            return Quat(x * s, y * s, z * s, w * s);
        }
        
        inline Quat operator /(const float s) {
            float d = s != 0 ? 1 / s : 0;
            
            return Quat(x * d, y * d, z * d, w * d);
        }
        
        inline void operator +=(const float s) {
            x += s;
            y += s;
            z += s;
			w += s;
        }
        
        inline void operator -=(const float s) {
            x -= s;
            y -= s;
            z -= s;
			w -= s;
        }
        
        inline void operator *=(const float s) {
            x *= s;
            y *= s;
            z *= s;
            w *= s;
        }
        
        inline void operator /=(const float s) {
            float d = s != 0 ? 1 / s : 0;
            
            x *= d;
            y *= d;
            z *= d;
            w *= d;
        }
        
        inline void operator =(const Quat& q) {
            x = q.x;
            y = q.y;
            z = q.z;
            w = q.w;
        }
        
        inline bool operator ==(const Quat& q) {
			
            return !(x != q.x || y != q.y || z != q.z || w != q.w);
        }
        
        inline bool operator !=(const Quat& q) {
			
            return x != q.x || y != q.y || z != q.z || w != q.w;
        }
        
        inline std::string ToString(int p = 5) {
			
			return "Quat("+ util.ToString(x, p) +", "+ util.ToString(y, p) +", "+ util.ToString(z, p) +", "+ util.ToString(w, p) +")";
        }
	};
};

#endif