#ifndef ODIN_VEC2_H
#define ODIN_VEC2_H

namespace Odin{
	
	struct Mat2;
	struct Mat32;
	struct Mat3;
	struct Mat4;
	
	struct Vec2{
		
		float x;
        float y;
		
		inline Vec2(void) {
            x = 0;
            y = 0;
        }
		
		inline Vec2(const float X) {
            x = X;
            y = X;
        }
		
		inline Vec2(const float X, const float Y) {
            x = X;
            y = Y;
        }
		
		inline Vec2(const Vec2& v) {
            x = v.x;
            y = v.y;
        }
		
		inline ~Vec2(void) {}
		
		inline Vec2& Set(const float X, const float Y) {
            x = X;
            y = Y;
			
			return *this;
        }
        
        inline Vec2& Zero() {
            x = 0;
            y = 0;
			
			return *this;
        }
        
        inline float Dot(const Vec2& v) {
			
            return x * v.x + y * v.y;
        }
        
        inline float Cross(const Vec2& v) {
			
            return x * v.y - y * v.x;
        }
        
        inline float LengthSq() {
			
            return x * x + y * y;
        }
        
        inline float Length() {
            float lenSq = x * x + y * y;
            
            return lenSq == 0 ? 0 : std::sqrt(lenSq);
        }
        
        inline float Normalize() {
            float lenSq = x * x + y * y;
            
            if(lenSq == 0) return 0;
            
            float len = std::sqrt(lenSq), invLen = 1 / len;
            
            x *= invLen;
            y *= invLen;
            
            return len;
        }
        
        inline Vec2& Lerp(const Vec2& v, const float t) {
            x = Mathf.Lerp(x, v.x, t);
            y = Mathf.Lerp(y, v.y, t);
			
			return *this;
        }
        
        inline static Vec2 Lerp(const Vec2& a, const Vec2& b, const float t) {
            
			return Vec2(
				Mathf.Lerp(a.x, b.x, t),
				Mathf.Lerp(a.y, b.y, t)
			);
        }
        
        inline static float Dot(const Vec2& a, const Vec2& b) {
			
            return a.x * b.x + a.y * b.y;
        }
        
        inline static float Cross(const Vec2& a, const Vec2& b) {
			
            return a.x * b.y - a.y * b.x;
        }
        
        inline Vec2& operator -() {
            x = -x;
            y = -y;
			
			return *this;
        }
        
        inline float operator [] (int i) const {
            return (&x)[i];
        }
        
        inline float& operator [] (int i) {
            return (&x)[i];
        }
        
        inline Vec2 operator *(const Mat2& m);
		inline Vec2& operator *=(const Mat2& m);
        
        inline Vec2 operator *(const Mat32& m);
		inline Vec2& operator *=(const Mat32& m);
        
        inline Vec2 operator *(const Mat4& m);
		inline Vec2& operator *=(const Mat4& m);
        
        inline Vec2 operator +(const Vec2& v) {
			
            return Vec2(x + v.x, y + v.y);
        }
        
        inline Vec2 operator -(const Vec2& v) {
			
            return Vec2(x - v.x, y - v.y);
        }
        
        inline Vec2 operator *(const Vec2& v) {
			
            return Vec2(x * v.x, y * v.y);
        }
        
        inline Vec2 operator /(const Vec2& v) {
            float vx = v.x, vy = v.y;
            
            vx = vx != 0 ? 1 / vx : 0;
            vy = vy != 0 ? 1 / vy : 0;
            
            return Vec2(x * vx, y * vy);
        }
        
        inline void operator +=(const Vec2& v) {
            x += v.x;
            y += v.y;
        }
        
        inline void operator -=(const Vec2& v) {
            x -= v.x;
            y -= v.y;
        }
        
        inline void operator *=(const Vec2& v) {
            x *= v.x;
            y *= v.y;
        }
        
        inline void operator /=(const Vec2& v) {
            float vx = v.x, vy = v.y;
            
            x *= vx != 0 ? 1 / vx : 0;
            y *= vy != 0 ? 1 / vy : 0;
        }
        
        
        inline Vec2 operator +(const float s) {
			
            return Vec2(x + s, y + s);
        }
        
        inline Vec2 operator -(const float s) {
			
            return Vec2(x - s, y - s);
        }
        
        inline Vec2 operator *(const float s) {
			
            return Vec2(x * s, y * s);
        }
        
        inline Vec2 operator /(const float s) {
            float d = s != 0 ? 1 / s : 0;
            
            return Vec2(x * d, y * d);
        }
        
        inline void operator +=(const float s) {
            x += s;
            y += s;
        }
        
        inline void operator -=(const float s) {
            x -= s;
            y -= s;
        }
        
        inline void operator *=(const float s) {
            x *= s;
            y *= s;
        }
        
        inline void operator /=(const float s) {
            float d = s != 0 ? 1 / s : 0;
            
            x *= d;
            y *= d;
        }
        
        inline Vec2 operator =(const Vec2& v) {
            x = v.x;
            y = v.y;
        }
        
        inline bool operator ==(const Vec2& v) {
			
            return !(x != v.x || y != v.y);
        }
        
        inline bool operator !=(const Vec2& v) {
			
            return x != v.x || y != v.y;
        }
        
        inline std::string ToString(int p = 5) {
			
			return "Vec2("+ util.ToString(x, p) +", "+ util.ToString(y, p) +")";
        }
	};
}

#endif