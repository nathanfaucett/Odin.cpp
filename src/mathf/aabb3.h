#ifndef ODIN_AABB3_H
#define ODIN_AABB3_H


namespace Odin {

	template <typename Type> class AABB3 {

		public:

			Vec3<Type> min;
			Vec3<Type> max;

			inline explicit AABB3(void);
			inline AABB3(const Vec3<Type>& MIN, const Vec3<Type>& MAX);
			inline AABB3(const AABB3<Type>& other);
			inline AABB3(const AABB3<Type>&& other);

			inline ~AABB3(void);

			inline AABB3<Type>& Set(const Vec3<Type>& MIN, const Vec3<Type>& MAX);
			inline AABB3<Type>& Zero(void);
			inline AABB3<Type>& Clear(void);
			inline AABB3<Type>& FromPoints(Vec3<Type>* points[], uint32 length);
			inline AABB3<Type>& FromPoints(Array<Vec3<Type>*> points);
			inline AABB3<Type>& FromCenterSize(const Vec3<Type>& center, const Vec3<Type>& size);
			inline AABB3<Type>& FromCenterSize(const Vec3<Type>& center, Type size);

			inline bool Contains(const Vec3<Type>& point);
			inline bool Intersects(const AABB3<Type>& other);

			inline static bool Contains(const AABB3<Type>& aabb, const Vec3<Type>& point) {
				Type px = point.x,
				     py = point.y;

				return !(
				           px < aabb.min.x || px > aabb.max.x ||
				           py < aabb.min.y || py > aabb.max.y
				       );
			}

			inline static bool Intersects(const AABB3<Type>& a, const AABB3<Type>& b) {

				return !(
				           b.max.x < a.min.x || b.min.x > a.max.x ||
				           b.max.y < a.min.y || b.min.y > a.max.y
				       );
			}

			inline void operator -();

			inline AABB3<Type> operator +(const AABB3<Type>& other);

			inline AABB3<Type> operator +(const Vec3<Type>& v);
			inline AABB3<Type> operator -(const Vec3<Type>& v);

			inline AABB3<Type> operator +(Type s);
			inline AABB3<Type> operator -(Type s);
			inline AABB3<Type> operator *(Type s);
			inline AABB3<Type> operator /(Type s);

			inline AABB3<Type>& operator +=(const AABB3<Type>& other);

			inline AABB3<Type>& operator +=(const Vec3<Type>& v);
			inline AABB3<Type>& operator -=(const Vec3<Type>& v);

			inline AABB3<Type>& operator +=(Type s);
			inline AABB3<Type>& operator -=(Type s);
			inline AABB3<Type>& operator *=(Type s);
			inline AABB3<Type>& operator /=(Type s);

			inline AABB3<Type>& operator =(const AABB3<Type>& other);
			inline AABB3<Type>& operator =(const AABB3<Type> && other);

			inline bool operator ==(const AABB3<Type>& other);
			inline bool operator !=(const AABB3<Type>& other);

			inline std::string ToString(int32 p = 6);
	};
}

#endif