#ifndef ODIN_VEC3_H
#define ODIN_VEC3_H


namespace Odin{
	
	struct Vec3{
		
		float x;
        float y;
        float z;
		
		inline Vec3(void) {
            x = 0;
            y = 0;
            z = 0;
        }
		
		inline Vec3(const float X) {
            x = X;
            y = X;
            z = X;
        }
		
		inline Vec3(const float X, const float Y) {
            x = X;
            y = Y;
            z = 0;
        }
		
		inline Vec3(const float X, const float Y, const float Z) {
            x = X;
            y = Y;
            z = Z;
        }
		
		inline Vec3(const Vec2& v) {
            x = v.x;
            y = v.y;
            z = 0;
        }
		
		inline Vec3(const Vec3& v) {
            x = v.x;
            y = v.y;
            z = v.z;
        }
		
		inline ~Vec3(void) {}
		
		inline Vec3& Set(const float X, const float Y, const float Z) {
            x = X;
            y = Y;
            z = Z;
			
			return *this;
        }
        
        inline Vec3& Zero() {
            x = 0;
            y = 0;
            z = 0;
			
			return *this;
        }
        
        inline float Dot(const Vec3 v) {
			
            return x * v.x + y * v.y + z * v.z;
        }
        
        inline Vec3 Cross(const Vec3 v) {
			
            return Vec3(
				y * v.z - z * v.y,
				z * v.x - x * v.z,
				x * v.y - y * v.x
			);
        }
        
        inline float LengthSq() {
			
            return x * x + y * y + z * z;
        }
        
        inline float Length() {
            float lenSq = x * x + y * y + z * z;
            
            return lenSq == 0 ? 0 : std::sqrt(lenSq);
        }
        
        inline float Normalize() {
            float lenSq = x * x + y * y + z * z;
            
            if(lenSq == 0) return 0;
            
            float len = std::sqrt(lenSq), invLen = 1 / len;
            
            x *= invLen;
            y *= invLen;
            z *= invLen;
            
            return len;
        }
        
        inline Vec3& Lerp(const Vec3& v, const float t) {
            x = Mathf.Lerp(x, v.x, t);
            y = Mathf.Lerp(y, v.y, t);
            z = Mathf.Lerp(z, v.z, t);
			
			return *this;
        }
        
        inline static Vec3 Lerp(const Vec3& a, const Vec3& b, const float t) {
            
			return Vec3(
				Mathf.Lerp(a.x, b.x, t),
				Mathf.Lerp(a.y, b.y, t),
				Mathf.Lerp(a.z, b.z, t)
			);
        }
        
        inline static float Dot(const Vec3& a, const Vec3& b) {
			
            return a.x * b.x + a.y * b.y + a.z * b.z;
        }
        
        inline static Vec3 Cross(const Vec3& a, const Vec3& b) {
			
            return Vec3(
				a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x
			);
        }
        
        inline Vec3 operator -() {
            x = -x;
            y = -y;
            z = -z;
        }
        
        inline float operator [] (int i) const {
            return (&x)[i];
        }
        
        inline float& operator [] (int i) {
            return (&x)[i];
        }
        
        inline Vec3 operator *(const Mat2& m);
		inline Vec3& operator *=(const Mat2& m);
        
        inline Vec3 operator *(const Mat32& m);
		inline Vec3& operator *=(const Mat32& m);
        
        inline Vec3 operator *(const Mat4& m);
		inline Vec3& operator *=(const Mat4& m);
        
        inline Vec3 operator +(const Vec3& v) {
			
            return Vec3(x + v.x, y + v.y, z + v.z);
        }
        
        inline Vec3 operator -(const Vec3& v) {
			
            return Vec3(x - v.x, y - v.y, z - v.z);
        }
        
        inline Vec3 operator *(const Vec3& v) {
			
            return Vec3(x * v.x, y * v.y, z * v.z);
        }
        
        inline Vec3 operator /(const Vec3& v) {
            float vx = v.x, vy = v.y, vz = v.y;
            
            vx = vx != 0 ? 1 / vx : 0;
            vy = vy != 0 ? 1 / vy : 0;
            vz = vz != 0 ? 1 / vz : 0;
            
            return Vec3(x * vx, y * vy, z * vz);
        }
        
        inline void operator +=(const Vec3& v) {
            x += v.x;
            y += v.y;
            z += v.z;
        }
        
        inline void operator -=(const Vec3& v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
        }
        
        inline void operator *=(const Vec3& v) {
            x *= v.x;
            y *= v.y;
            z *= v.z;
        }
        
        inline void operator /=(const Vec3& v) {
            float vx = v.x, vy = v.y, vz = v.z;
            
            x *= vx != 0 ? 1 / vx : 0;
            y *= vy != 0 ? 1 / vy : 0;
            z *= vz != 0 ? 1 / vz : 0;
        }
        
        
        inline Vec3 operator +(const float s) {
			
            return Vec3(x + s, y + s, z + s);
        }
        
        inline Vec3 operator -(const float s) {
			
            return Vec3(x - s, y - s, z - s);
        }
        
        inline Vec3 operator *(const float s) {
			
            return Vec3(x * s, y * s, z * s);
        }
        
        inline Vec3 operator /(const float s) {
            float d = s != 0 ? 1 / s : 0;
            
            return Vec3(x * d, y * d, z * d);
        }
        
        inline void operator +=(const float s) {
            x += s;
            y += s;
            z += s;
        }
        
        inline void operator -=(const float s) {
            x -= s;
            y -= s;
            z -= s;
        }
        
        inline void operator *=(const float s) {
            x *= s;
            y *= s;
            z *= s;
        }
        
        inline void operator /=(const float s) {
            float d = s != 0 ? 1 / s : 0;
            
            x *= d;
            y *= d;
            z *= d;
        }
        
        inline Vec3 operator =(const Vec3& v) {
            x = v.x;
            y = v.y;
            z = v.z;
        }
        
        inline bool operator ==(const Vec3& v) {
			
            return !(x != v.x || y != v.y || z != v.z);
        }
        
        inline bool operator !=(const Vec3& v) {
			
            return x != v.x || y != v.y || z != v.z;
        }
        
        inline std::string ToString(int p = 5) {
			
			return "Vec3("+ util.ToString(x, p) +", "+ util.ToString(y, p) +", "+ util.ToString(z, p) +")";
        }
	};
}

#endif