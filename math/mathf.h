#ifndef ODIN_MATHF_H
#define ODIN_MATHF_H

namespace Odin{
	
	struct Mathf{
		static constexpr double PI = M_PI;
        static constexpr double FOURTH_PI = M_PI * 0.25;
        static constexpr double HALF_PI = M_PI * 0.5;
        static constexpr double TWO_PI = M_PI * 2;
        
        static constexpr double Epsilon = FLT_EPSILON;
        static constexpr double Infinity = FLT_MAX;
        static constexpr double POS_Infinity = FLT_MAX;
        static constexpr double NEG_Infinity = -FLT_MAX;
        
        static constexpr double MAX_NUMBER = FLT_MAX;
        static constexpr double MIN_NUMBER = FLT_MIN;
        
        static constexpr double TO_DEGS = 180 / M_PI;
        static constexpr double TO_RADS = M_PI / 180;
        
        inline double Abs(const double x) {
			
			return x < 0 ? -x : x;
		}
		
        inline double Pow(const double x, const float e) {
			
			return std::pow(x, e);
		}
        
		inline double Sqrt(const double x) {
			
			return std::sqrt(x);
		}
        
		inline double Log(const double x) {
			
			return std::log(x);
		}
        inline double Log10(const double x) {
			
			return std::log10(x);
		}
        
        inline double Cos(const double x) {
			
			return std::cos(x);
		}
        inline double Sin(const double x) {
			
			return std::sin(x);
		}
        inline double Tan(const double x) {
			
			return std::tan(x);
		}
        
        inline double Acos(const double x) {
			
			return std::acos(x);
		}
        inline double Asin(const double x) {
			
			return std::asin(x);
		}
        inline double Atan(const double x) {
			
			return std::atan(x);
		}
        
        inline double Atan2(const double y, const double x) {
			
			return std::atan2(y, x);
		}
        
        inline double Cosh(const double x) {
			
			return std::cosh(x);
		}
        inline double Sinh(const double x) {
			
			return std::sinh(x);
		}
        inline double Tanh(const double x) {
			
			return std::tanh(x);
		}
        
        inline double Floor(const double x) {
			
			return std::floor(x);
		}
        inline double Ceil(const double x) {
			
			return std::ceil(x);
		}
        inline double Round(const double x) {
			
			return std::floor(x + 0.5);
		}
        
        inline bool Equals(const float a, const float b) {
			
            return Abs(a - b) <= FLT_EPSILON;
		}
        
        inline float Modulo(const float a, const float b) {
            float r = fmod(a, b);
            
            return (r * b < FLT_EPSILON) ? r + b : r;
		}
        
        inline float Clamp(const float x, const float min, const float max) {
			
            return x < min ? min : x > max ? max : x;
		}
        
        inline float ClampBottom(const float x, const float min) {
			
            return x < min ? min : x;
		}
        
        inline float ClampTop(const float x, const float max) {
			
            return x > max ? max : x;
		}
        
        inline float Clamp01(const float x) {
			
            return x < 0 ? 0 : x > 1 ? 1 : x;
       
		}
        
        inline float Radian(const float x) {
			
            return Modulo(x, TWO_PI);
		}
        
        inline float Angle(const float x) {
			
            return Modulo(x, 360);
		}
        
        inline float Sign(const float x) {
			
            return x ? x < 0 ? -1 : 1 : 0;
		}
        
        inline int Sign(const int x) {
			
            return x ? x < 0 ? -1 : 1 : 0;
		}
        
        inline float Lerp(const float a, const float b, const float t) {
			
            return a + (b - a) * t;
		}
		
        inline float lerpCos(const float a, const float b, const float t) {
			float ft = t * PI,
                f = (1 - cos(ft)) * 0.5;

            return a * (1 - f) + b * f;
		}
        
        inline float LerpCubic(const float v0, const float v1, const float v2, const float v3, const float t) {
            float P = (v3 - v2) - (v0 - v1),
                Q = (v0 - v1) - P,
                R = v2 - v0,
                S = v1,

                Pt = P * t,
                Qt = Q * t,
                Rt = R * t;

            return (Pt * Pt * Pt) + (Qt * Qt) + Rt + S;
		}
        
        inline float LerpRadian(const float a, const float b, const float t) {
			
            return Radian(a + (b - a) * t);
		}
        
        inline float LerpAngle(const float a, const float b, const float t) {
			
            return Angle(a + (b - a) * t);
       
		}
        
        inline float SmoothStep(const float x, const float min, const float max) {
			float t = x;
			
            if (t <= min) return 0;
            if (t >= max) return 1;

            t = (t - min) / (max - min);

            return t * t * (3 - 2 * t);
		}
        
        inline float SmootherStep(const float x, const float min, const float max) {
			float t = x;
			
			if (t <= min) return 0;
            if (t >= max) return 1;

            t = (t - min) / (max - min);

            return t * t * t * (t * (t * 6 - 15) + 10);
		}
        
        inline float PingPong(const float x, const float length) {
			
            return length - Abs(Modulo(x, 2 * length) - length);
		}
        
        inline float ToRads(const float x) {
			
            return Radian(x * TO_RADS);
		}
        
        inline float ToDegs(const float x) {
			
            return Angle(x * TO_DEGS);
       
		}
        
        inline bool IsPowerOfTwo(const float n) {
            int x = n;
            
            return (x & -x) == x;
		}
        
        inline float ToPowerOfTwo(const float n) {
            int x = Abs(n);
            
            --x;
            x |= x >> 1;
            x |= x >> 2;
            x |= x >> 4;
            x |= x >> 8;
            x |= x >> 16;
            
            return x + 1;
		}
        
        inline float Random() {
			
            return (double) std::rand() / RAND_MAX;
		}
		
        inline int RandInt(int const min, const int max) {
			
            return Round(min + (Random() * (max - min)));
		}
        
        inline float RandFloat(const float min, const float max) {
			
            return min + (Random() * (max - min));
		}
        
        inline float V2LengthSq(const float x, const float y) {
			
            return x * x + y * y;
		}
        
        inline float V3LengthSq(const float x, const float y, const float z) {
			
            return x * x + y * y + z * z;
		}
        
        inline float V2Length(const float x, const float y) {
			float length = x * x + y * y;
			
            return length == 0 ? 0 : std::sqrt(length);
		}
        
        inline float V3Length(const float x, const float y, const float z) {
			float length = x * x + y * y + z * z;
			
            return length == 0 ? 0 : std::sqrt(length);
		}
	};
	
	Mathf Mathf;
}

#endif