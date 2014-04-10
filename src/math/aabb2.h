#ifndef ODIN_AABB2_H
#define ODIN_AABB2_H


namespace Odin {

	template <typename Type> class AABB2 {

		public:
			Vec2<Type> min;
			Vec2<Type> max;

			inline explicit AABB2(void);
			inline AABB2(const Vec2<Type>& MIN, const Vec2<Type>& MAX);
			inline AABB2(const AABB2<Type>& other);
			inline AABB2(const AABB2<Type>&& other);

			inline ~AABB2(void);

			inline AABB2<Type>& Set(const Vec2<Type>& MIN, const Vec2<Type>& MAX);
			inline AABB2<Type>& Zero(void);
			inline AABB2<Type>& Clear(void);
			inline AABB2<Type>& FromPoints(Vec2<Type>* points[], uint32 length);
			inline AABB2<Type>& FromPoints(Array<Vec2<Type>*> points);
			inline AABB2<Type>& FromCenterSize(const Vec2<Type>& center, const Vec2<Type>& size);

			inline bool Contains(const Vec2<Type>& point);
			inline bool Intersects(const AABB2<Type>& other);

			inline static bool Contains(const AABB2<Type>& aabb, const Vec2<Type>& point) {
				Type px = point.x,
				     py = point.y;

				return !(
				           px < aabb.min.x || px > aabb.max.x ||
				           py < aabb.min.y || py > aabb.max.y
				       );
			}

			inline static bool Intersects(const AABB2<Type>& a, const AABB2<Type>& b) {

				return !(
				           b.max.x < a.min.x || b.min.x > a.max.x ||
				           b.max.y < a.min.y || b.min.y > a.max.y
				       );
			}

			inline void operator -();

			inline AABB2<Type> operator +(const AABB2<Type>& other);

			inline AABB2<Type> operator +(const Vec2<Type>& v);
			inline AABB2<Type> operator -(const Vec2<Type>& v);

			inline AABB2<Type> operator +(Type s);
			inline AABB2<Type> operator -(Type s);
			inline AABB2<Type> operator *(Type s);
			inline AABB2<Type> operator /(Type s);

			inline void operator +=(const AABB2<Type>& other);

			inline void operator +=(const Vec2<Type>& v);
			inline void operator -=(const Vec2<Type>& v);

			inline void operator +=(Type s);
			inline void operator -=(Type s);
			inline void operator *=(Type s);
			inline void operator /=(Type s);

			inline AABB2<Type>& operator =(const AABB2<Type>& other);
			inline AABB2<Type>& operator =(const AABB2<Type> && other);

			inline bool operator ==(const AABB2<Type>& other);
			inline bool operator !=(const AABB2<Type>& other);

			inline std::string ToString(int32 p = 5);
	};
}

#endif