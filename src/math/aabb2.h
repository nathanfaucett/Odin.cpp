#ifndef ODIN_AABB2_H
#define ODIN_AABB2_H


namespace Odin {

	struct AABB2 {

		Vec2 min;
		Vec2 max;

		inline explicit AABB2(void);
		inline AABB2(const Vec2& MIN, const Vec2& MAX);
		inline AABB2(const AABB2& other);
		inline AABB2(const AABB2&& other);

		inline ~AABB2(void);

		inline AABB2& Set(const Vec2& MIN, const Vec2& MAX);
		inline AABB2& Zero(void);
		inline AABB2& Clear(void);
		inline AABB2& FromPoints(Vec2* points[], const unsigned int length);
		inline AABB2& FromPoints(Array<Vec2*> points);
		inline AABB2& FromCenterSize(const Vec2& center, const Vec2& size);

		inline bool Contains(const Vec2& point);
		inline bool Intersects(const AABB2& other);

		inline static bool Contains(const AABB2& aabb, const Vec2& point) {
			float px = point.x,
			      py = point.y;

			return !(
			           px < aabb.min.x || px > aabb.max.x ||
			           py < aabb.min.y || py > aabb.max.y
			       );
		}

		inline static bool Intersects(const AABB2& a, const AABB2& b) {

			return !(
			           b.max.x < a.min.x || b.min.x > a.max.x ||
			           b.max.y < a.min.y || b.min.y > a.max.y
			       );
		}

		inline AABB2 operator -();

		inline AABB2 operator +(const AABB2& other);

		inline AABB2 operator +(const Vec2& v);
		inline AABB2 operator -(const Vec2& v);

		inline AABB2 operator +(const float s);
		inline AABB2 operator -(const float s);
		inline AABB2 operator *(const float s);
		inline AABB2 operator /(const float s);

		inline void operator +=(const AABB2& other);

		inline void operator +=(const Vec2& v);
		inline void operator -=(const Vec2& v);

		inline void operator +=(const float s);
		inline void operator -=(const float s);
		inline void operator *=(const float s);
		inline void operator /=(const float s);

		inline AABB2& operator =(const AABB2& other);
		inline AABB2& operator =(const AABB2 && other);

		inline bool operator ==(const AABB2& other);
		inline bool operator !=(const AABB2& other);

		inline std::string ToString(int p = 5);
	};
}

#endif