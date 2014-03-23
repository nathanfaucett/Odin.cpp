#ifndef _ODIN_AABB3_H_
#define _ODIN_AABB3_H_


namespace Odin {

	class AABB3 {

		public:

			Vec3 min;
			Vec3 max;

			inline explicit AABB3(void);
			inline AABB3(const Vec3& MIN, const Vec3& MAX);
			inline AABB3(const AABB3& other);
			inline AABB3(const AABB3&& other);

			inline ~AABB3(void);

			inline AABB3& Set(const Vec3& MIN, const Vec3& MAX);
			inline AABB3& Zero(void);
			inline AABB3& Clear(void);
			inline AABB3& FromPoints(Vec3* points[], uint32 length);
			inline AABB3& FromPoints(Array<Vec3*> points);
			inline AABB3& FromCenterSize(const Vec3& center, const Vec3& size);

			inline bool Contains(const Vec3& point);
			inline bool Intersects(const AABB3& other);

			inline static bool Contains(const AABB3& aabb, const Vec3& point) {
				float32 px = point.x,
				        py = point.y;

				return !(
				           px < aabb.min.x || px > aabb.max.x ||
				           py < aabb.min.y || py > aabb.max.y
				       );
			}

			inline static bool Intersects(const AABB3& a, const AABB3& b) {

				return !(
				           b.max.x < a.min.x || b.min.x > a.max.x ||
				           b.max.y < a.min.y || b.min.y > a.max.y
				       );
			}

			inline void operator -();

			inline AABB3 operator +(const AABB3& other);

			inline AABB3 operator +(const Vec3& v);
			inline AABB3 operator -(const Vec3& v);

			inline AABB3 operator +(float32 s);
			inline AABB3 operator -(float32 s);
			inline AABB3 operator *(float32 s);
			inline AABB3 operator /(float32 s);

			inline void operator +=(const AABB3& other);

			inline void operator +=(const Vec3& v);
			inline void operator -=(const Vec3& v);

			inline void operator +=(float32 s);
			inline void operator -=(float32 s);
			inline void operator *=(float32 s);
			inline void operator /=(float32 s);

			inline AABB3& operator =(const AABB3& other);
			inline AABB3& operator =(const AABB3 && other);

			inline bool operator ==(const AABB3& other);
			inline bool operator !=(const AABB3& other);

			inline std::string ToString(int32 p = 5);
	};
}

#endif