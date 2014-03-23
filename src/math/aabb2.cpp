#ifndef _ODIN_AABB2_CPP_
#define _ODIN_AABB2_CPP_


namespace Odin {

	template <typename Type> inline AABB2<Type>::AABB2(void) {
		min.Set(Infinity, Infinity);
		max.Set(-Infinity, -Infinity);
	}

	template <typename Type> inline AABB2<Type>::AABB2(const Vec2<Type>& MIN, const Vec2<Type>& MAX) {
		min = MIN;
		max = MAX;
	}

	template <typename Type> inline AABB2<Type>::AABB2(const AABB2<Type>& other) {
		min = other.min;
		max = other.max;
	}

	template <typename Type> inline AABB2<Type>::AABB2(const AABB2<Type>&& other) {
		min = std::move(other.min);
		max = std::move(other.max);
	}

	template <typename Type> inline AABB2<Type>::~AABB2(void) {}

	template <typename Type> inline AABB2<Type>& AABB2<Type>::Set(const Vec2<Type>& MIN, const Vec2<Type>& MAX) {
		min = MIN;
		max = MAX;

		return *this;
	}

	template <typename Type> inline AABB2<Type>& AABB2<Type>::Zero(void) {
		min.Set(0, 0);
		max.Set(0, 0);

		return *this;
	}

	template <typename Type> inline AABB2<Type>& AABB2<Type>::Clear(void) {
		min.Set(Infinity, Infinity);
		max.Set(-Infinity, -Infinity);

		return *this;
	}

	template <typename Type> inline AABB2<Type>& AABB2<Type>::FromPoints(Vec2<Type>* points[], uint32 length) {
		Type minx = Infinity,
		     miny = Infinity,
		     maxx = -Infinity,
		     maxy = -Infinity,
		     x, y;

		Vec2<Type>* v;
		uint32 i = length;

		while (i--) {
			v = points[i];
			assert(v != NULL);
			x = v->x;
			y = v->y;

			minx = minx > x ? x : minx;
			miny = miny > y ? y : miny;

			maxx = maxx < x ? x : maxx;
			maxy = maxy < y ? y : maxy;
		}

		min.x = minx;
		min.y = miny;
		max.x = maxx;
		max.y = maxy;

		return *this;
	}

	template <typename Type> inline AABB2<Type>& AABB2<Type>::FromPoints(Array<Vec2<Type>*> points) {
		Type minx = Infinity,
		     miny = Infinity,
		     maxx = -Infinity,
		     maxy = -Infinity,
		     x, y;

		Vec2<Type>* v;
		uint32 i = points.Length();

		while (i--) {
			v = points[i];
			assert(v != NULL);
			x = v->x;
			y = v->y;

			minx = minx > x ? x : minx;
			miny = miny > y ? y : miny;

			maxx = maxx < x ? x : maxx;
			maxy = maxy < y ? y : maxy;
		}

		min.x = minx;
		min.y = miny;
		max.x = maxx;
		max.y = maxy;

		return *this;
	}

	template <typename Type> inline AABB2<Type>& AABB2<Type>::FromCenterSize(const Vec2<Type>& center, const Vec2<Type>& size) {
		Type x = center.x,
		     y = center.y,
		     hx = size.x * 0.5,
		     hy = size.y * 0.5;

		min.x = x - hx;
		min.y = y - hy;

		max.x = x + hx;
		max.y = y + hy;

		return *this;
	}

	template <typename Type> inline bool AABB2<Type>::Contains(const Vec2<Type>& point) {
		Type px = point.x,
		     py = point.y;

		return !(
		           px < min.x || px > max.x ||
		           py < min.y || py > max.y
		       );
	}

	template <typename Type> inline bool AABB2<Type>::Intersects(const AABB2<Type>& other) {

		return !(
		           other.max.x < min.x || other.min.x > max.x ||
		           other.max.y < min.y || other.min.y > max.y
		       );
	}

	template <typename Type> inline void AABB2<Type>::operator -() {
		-min;
		-max;
	}

	template <typename Type> inline AABB2<Type> AABB2<Type>::operator +(const AABB2<Type>& other) {

		return AABB2(
		           Vec2<Type>::Min(min, other.min),
		           Vec2<Type>::Max(max, other.max)
		       );
	}

	template <typename Type> inline AABB2<Type> AABB2<Type>::operator +(const Vec2<Type>& v) {

		return AABB2(
		           min + v,
		           max + v
		       );
	}

	template <typename Type> inline AABB2<Type> AABB2<Type>::operator -(const Vec2<Type>& v) {

		return AABB2(
		           min - v,
		           max - v
		       );
	}

	template <typename Type> inline AABB2<Type> AABB2<Type>::operator +(Type s) {

		return AABB2(
		           min + s,
		           max + s
		       );
	}

	template <typename Type> inline AABB2<Type> AABB2<Type>::operator -(Type s) {

		return AABB2(
		           min - s,
		           max - s
		       );
	}

	template <typename Type> inline AABB2<Type> AABB2<Type>::operator *(Type s) {

		return AABB2(
		           min * s,
		           max * s
		       );
	}

	template <typename Type> inline AABB2<Type> AABB2<Type>::operator /(Type s) {
		Type d = s == 0 ? 0 : 1 / s;

		return AABB2(
		           min * d,
		           max * d
		       );
	}

	template <typename Type> inline void AABB2<Type>::operator +=(const AABB2<Type>& other) {
		min.Min(other.min);
		max.Max(other.max);
	}

	template <typename Type> inline void AABB2<Type>::operator +=(const Vec2<Type>& v) {
		min += v;
		max += v;
	}

	template <typename Type> inline void AABB2<Type>::operator -=(const Vec2<Type>& v) {
		min -= v;
		max -= v;
	}

	template <typename Type> inline void AABB2<Type>::operator +=(Type s) {
		min += s;
		max += s;
	}

	template <typename Type> inline void AABB2<Type>::operator -=(Type s) {
		min -= s;
		max -= s;
	}

	template <typename Type> inline void AABB2<Type>::operator *=(Type s) {
		min *= s;
		max *= s;
	}

	template <typename Type> inline void AABB2<Type>::operator /=(Type s) {
		Type d = s == 0 ? 0 : 1 / s;

		min *= d;
		max *= d;
	}

	template <typename Type> inline AABB2<Type>& AABB2<Type>::operator =(const AABB2<Type>& other) {
		min = other.min;
		max = other.max;

		return *this;
	}

	template <typename Type> inline AABB2<Type>& AABB2<Type>::operator =(const AABB2<Type> && other) {
		min = std::move(other.min);
		max = std::move(other.max);

		return *this;
	}

	template <typename Type> inline bool AABB2<Type>::operator ==(const AABB2<Type>& other) {

		return !(min != other.min || max != other.max);
	}

	template <typename Type> inline bool AABB2<Type>::operator !=(const AABB2<Type>& other) {

		return min != other.min || max != other.max;
	}

	template <typename Type> inline std::string AABB2<Type>::ToString(int32 p) {

		return "AABB2( min: " + min.ToString(p) + ", max: " + max.ToString(p) + ")";
	}
}

#endif