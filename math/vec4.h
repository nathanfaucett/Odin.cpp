#ifndef ODIN_VEC4_H
#define ODIN_VEC4_H


namespace Odin{
	
	struct Vec4{
		
		float x;
        float y;
        float z;
        float w;
		
		inline Vec4(void) {
            x = 0;
            y = 0;
            z = 0;
            w = 1;
        }
		
		inline Vec4(const float X) {
            x = X;
            y = X;
            z = X;
            w = X;
        }
		
		inline Vec4(const float X, const float Y, const float Z) {
            x = X;
            y = Y;
            z = Z;
            w = 1;
        }
		
		inline Vec4(const float X, const float Y, const float Z, const float W) {
            x = X;
            y = Y;
            z = Z;
            w = W;
        }
		
		inline Vec4(const Vec2& v) {
            x = v.x;
            y = v.y;
            z = 0;
			w = 1;
        }
		
		inline Vec4(const Vec3& v) {
            x = v.x;
            y = v.y;
            z = v.z;
			w = 1;
        }
		
		inline Vec4(const Vec4& v) {
            x = v.x;
            y = v.y;
            z = v.z;
            w = v.w;
        }
		
		inline ~Vec4(void) {}
		
		inline Vec4& Set(const float X, const float Y, const float Z) {
            x = X;
            y = Y;
            z = Z;
			
			return *this;
        }
		
		inline Vec4& Set(const float X, const float Y, const float Z, const float W) {
            x = X;
            y = Y;
            z = Z;
			w = W;
			
			return *this;
        }
        
        inline Vec4& Zero() {
            x = 0;
            y = 0;
            z = 0;
			w = 0;
			
			return *this;
        }
        
        inline float Dot(const Vec4 v) {
			
            return x * v.x + y * v.y + z * v.z + w * v.w;
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
        
        inline Vec4& Lerp(const Vec4& v, const float t) {
            x = Mathf.Lerp(x, v.x, t);
            y = Mathf.Lerp(y, v.y, t);
            z = Mathf.Lerp(z, v.z, t);
            w = Mathf.Lerp(w, v.w, t);
			
			return *this;
        }
        
        inline static Vec4 Lerp(const Vec4& a, const Vec4& b, const float t) {
            
			return Vec4(
				Mathf.Lerp(a.x, b.x, t),
				Mathf.Lerp(a.y, b.y, t),
				Mathf.Lerp(a.z, b.z, t),
				Mathf.Lerp(a.w, b.w, t)
			);
        }
        
        inline static float Dot(const Vec4& a, const Vec4& b) {
			
            return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
        }
        
        inline Vec4 operator -() {
            x = -x;
            y = -y;
            z = -z;
			w = -w;
        }
        
        inline float operator [] (int i) const {
            return (&x)[i];
        }
        
        inline float& operator [] (int i) {
            return (&x)[i];
        }
        
        inline Vec4 operator +(const Vec4& v) {
			
            return Vec4(x + v.x, y + v.y, z + v.z, w + v.w);
        }
        
        inline Vec4 operator -(const Vec4& v) {
			
            return Vec4(x - v.x, y - v.y, z - v.z, w - v.w);
        }
        
        inline Vec4 operator *(const Vec4& v) {
			
            return Vec4(x * v.x, y * v.y, z * v.z, w * v.w);
        }
        
        inline Vec4 operator /(const Vec4& v) {
            float vx = v.x, vy = v.y, vz = v.y, vw = v.w;
            
            vx = vx != 0 ? 1 / vx : 0;
            vy = vy != 0 ? 1 / vy : 0;
            vz = vz != 0 ? 1 / vz : 0;
            vw = vw != 0 ? 1 / vw : 0;
            
            return Vec4(x * vx, y * vy, z * vz, w * vw);
        }
        
        inline void operator +=(const Vec4& v) {
            x += v.x;
            y += v.y;
            z += v.z;
            w += v.w;
        }
        
        inline void operator -=(const Vec4& v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            w -= v.w;
        }
        
        inline void operator *=(const Vec4& v) {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            w *= v.w;
        }
        
        inline void operator /=(const Vec4& v) {
            float vx = v.x, vy = v.y, vz = v.z, vw = v.w;
            
            x *= vx != 0 ? 1 / vx : 0;
            y *= vy != 0 ? 1 / vy : 0;
            z *= vz != 0 ? 1 / vz : 0;
            w *= vw != 0 ? 1 / vw : 0;
        }
        
        
        inline Vec4 operator +(const float s) {
			
            return Vec4(x + s, y + s, z + s, w + s);
        }
        
        inline Vec4 operator -(const float s) {
			
            return Vec4(x - s, y - s, z - s, w - s);
        }
        
        inline Vec4 operator *(const float s) {
			
            return Vec4(x * s, y * s, z * s, w * s);
        }
        
        inline Vec4 operator /(const float s) {
            float d = s != 0 ? 1 / s : 0;
            
            return Vec4(x * d, y * d, z * d, w * d);
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
        
        inline Vec4 operator =(const Vec4& v) {
            x = v.x;
            y = v.y;
            z = v.z;
            w = v.w;
        }
        
        inline bool operator ==(const Vec4& v) {
			
            return !(x != v.x || y != v.y || z != v.z || w != v.w);
        }
        
        inline bool operator !=(const Vec4& v) {
			
            return x != v.x || y != v.y || z != v.z || w != v.w;
        }
        
        inline std::string ToString(int p = 5) {
			
			return "Vec4("+ util.ToString(x, p) +", "+ util.ToString(y, p) +", "+ util.ToString(z, p) +", "+ util.ToString(w, p) +")";
        }
	};
};

#endif