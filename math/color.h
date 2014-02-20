#ifndef ODIN_COLOR_H
#define ODIN_COLOR_H


namespace Odin{
	
	struct Color{
		
		float r;
        float g;
        float b;
		
		inline Color(void) {
            r = 0;
            g = 0;
            b = 0;
        }
		
		inline Color(const float X) {
            r = X;
            g = X;
            b = X;
        }
		
		inline Color(const float R, const float G, const float B) {
            r = R;
            g = G;
            b = B;
        }
		
		inline Color(const Vec2& v) {
            r = v.x;
            g = v.y;
            b = 0;
        }
		
		inline Color(const Vec3& v) {
            r = v.x;
            g = v.y;
            b = v.z;
        }
		
		inline Color(const Vec4& v) {
            r = v.x;
            g = v.y;
            b = v.z;
        }
		
		inline Color(const Color& c) {
            r = c.r;
            g = c.g;
            b = c.b;
        }
		
		inline ~Color(void) {}
		
		inline Color& Set(const float R, const float G, const float B) {
            r = R;
            g = G;
            b = B;
			
			return *this;
        }
        
        inline Color& Zero() {
            r = 0;
            g = 0;
            b = 0;
			
			return *this;
        }
        
        inline float Dot(const Color c) {
			
            return r * c.r + g * c.g + b * c.b;
        }
        
        inline float LengthSq() {
			
            return r * r + g * g + b * b;
        }
        
        inline float Length() {
            float lenSq = r * r + g * g + b * b;
            
            return lenSq == 0 ? 0 : std::sqrt(lenSq);
        }
        
        inline float Normalize() {
            float lenSq = r * r + g * g + b * b;
            
            if(lenSq == 0) return 0;
            
            float len = std::sqrt(lenSq), invLen = 1 / len;
            
            r *= invLen;
            g *= invLen;
            b *= invLen;
            
            return len;
        }
        
        inline void CNormalize() {
            
            r = r > 1 ? 1 : r < 0 ? 0 : r;
            g = g > 1 ? 1 : g < 0 ? 0 : g;
            b = b > 1 ? 1 : b < 0 ? 0 : b;
        }
        
        inline Color& Lerp(const Color& c, const float t) {
            r = Mathf.Lerp(r, c.r, t);
            g = Mathf.Lerp(g, c.g, t);
            b = Mathf.Lerp(b, c.b, t);
			
			return *this;
        }
        
        inline static Color Lerp(const Color& a, const Color& b, const float t) {
            
			return Color(
				Mathf.Lerp(a.r, b.r, t),
				Mathf.Lerp(a.g, b.g, t),
				Mathf.Lerp(a.b, b.b, t)
			);
        }
        
        inline static float Dot(const Color& a, const Color& b) {
			
            return a.r * b.r + a.g * b.g + a.b * b.b;
        }
        
        inline Color operator -() {
            r = 1 - r;
            g = 1 - g;
            b = 1 - b;
        }
        
        inline float operator [] (int i) const {
            return (&r)[i];
        }
        
        inline float& operator [] (int i) {
            return (&r)[i];
        }
        
        inline Color operator +(const Color& c) {
			
            return Color(r + c.r, g + c.g, b + c.b);
        }
        
        inline Color operator -(const Color& c) {
			
            return Color(r - c.r, g - c.g, b - c.b);
        }
        
        inline Color operator *(const Color& c) {
			
            return Color(r * c.r, g * c.g, b * c.b);
        }
        
        inline Color operator /(const Color& c) {
            float cx = c.r, cy = c.g, cz = c.g;
            
            cx = cx != 0 ? 1 / cx : 0;
            cy = cy != 0 ? 1 / cy : 0;
            cz = cz != 0 ? 1 / cz : 0;
            
            return Color(r * cx, g * cy, b * cz);
        }
        
        inline void operator +=(const Color& c) {
            r += c.r;
            g += c.g;
            b += c.b;
        }
        
        inline void operator -=(const Color& c) {
            r -= c.r;
            g -= c.g;
            b -= c.b;
        }
        
        inline void operator *=(const Color& c) {
            r *= c.r;
            g *= c.g;
            b *= c.b;
        }
        
        inline void operator /=(const Color& c) {
            float cx = c.r, cy = c.g, cz = c.b;
            
            r *= cx != 0 ? 1 / cx : 0;
            g *= cy != 0 ? 1 / cy : 0;
            b *= cz != 0 ? 1 / cz : 0;
        }
        
        
        inline Color operator +(const float s) {
			
            return Color(r + s, g + s, b + s);
        }
        
        inline Color operator -(const float s) {
			
            return Color(r - s, g - s, b - s);
        }
        
        inline Color operator *(const float s) {
			
            return Color(r * s, g * s, b * s);
        }
        
        inline Color operator /(const float s) {
            float d = s != 0 ? 1 / s : 0;
            
            return Color(r * d, g * d, b * d);
        }
        
        inline void operator +=(const float s) {
            r += s;
            g += s;
            b += s;
        }
        
        inline void operator -=(const float s) {
            r -= s;
            g -= s;
            b -= s;
        }
        
        inline void operator *=(const float s) {
            r *= s;
            g *= s;
            b *= s;
        }
        
        inline void operator /=(const float s) {
            float d = s != 0 ? 1 / s : 0;
            
            r *= d;
            g *= d;
            b *= d;
        }
        
        inline Color operator =(const Color& c) {
            r = c.r;
            g = c.g;
            b = c.b;
        }
        
        inline bool operator ==(const Color& c) {
			
            return !(r != c.r || g != c.g || b != c.b);
        }
        
        inline bool operator !=(const Color& c) {
			
            return r != c.r || g != c.g || b != c.b;
        }
        
        inline std::string ToString(int p = 5) {
			
			return "Color("+ util.ToString(r, p) +", "+ util.ToString(g, p) +", "+ util.ToString(b, p) +")";
        }
	};
}

#endif