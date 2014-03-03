#ifndef _ODIN_AABB2_H
#define _ODIN_AABB2_H


namespace Odin {

	class AABB2 {

		public:
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
			inline AABB2& FromPoints(Vec2* points[], uint32 length);
			inline AABB2& FromPoints(Array<Vec2*> points);
			inline AABB2& FromCenterSize(const Vec2& center, const Vec2& size);

			inline bool Contains(const Vec2& point);
			inline bool Intersects(const AABB2& other);

			inline static bool Contains(const AABB2& aabb, const Vec2& point) {
				float32 px = point.x,
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

			inline void operator -();

			inline AABB2 operator +(const AABB2& other);

			inline AABB2 operator +(const Vec2& v);
			inline AABB2 operator -(const Vec2& v);

			inline AABB2 operator +(float32 s);
			inline AABB2 operator -(float32 s);
			inline AABB2 operator *(float32 s);
			inline AABB2 operator /(float32 s);

			inline void operator +=(const AABB2& other);

			inline void operator +=(const Vec2& v);
			inline void operator -=(const Vec2& v);

			inline void operator +=(float32 s);
			inline void operator -=(float32 s);
			inline void operator *=(float32 s);
			inline void operator /=(float32 s);

			inline AABB2& operator =(const AABB2& other);
			inline AABB2& operator =(const AABB2 && other);

			inline bool operator ==(const AABB2& other);
			inline bool operator !=(const AABB2& other);

			inline std::string ToString(int32 p = 5);
	};
}

#endif