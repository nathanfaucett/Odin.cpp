#ifndef ODIN_AABB2_CPP
#define ODIN_AABB2_CPP


namespace Odin {

	template <typename Type> inline AABB2<Type>::AABB2(void) {
		min.Set(MAX_NUMBER<Type>(), MAX_NUMBER<Type>());
		max.Set(-MAX_NUMBER<Type>(), -MAX_NUMBER<Type>());
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

	template <typename Type> inline AABB2<Type>::~AABB2<Type>(void) {}

	template <typename Type> inline AABB2<Type>& AABB2<Type>::Set(const Vec2<Type>& MIN, const Vec2<Type>& MAX) {
		min = MIN;
		max = MAX;

		return *this;
	}

	template <typename Type> inline AABB2<Type>& AABB2<Type>::Zero(void) {
		min.Set(static_cast<Type>(0), static_cast<Type>(0));
		max.Set(static_cast<Type>(0), static_cast<Type>(0));

		return *this;
	}

	template <typename Type> inline AABB2<Type>& AABB2<Type>::Clear(void) {
		min.Set(MAX_NUMBER<Type>(), MAX_NUMBER<Type>());
		max.Set(-MAX_NUMBER<Type>(), -MAX_NUMBER<Type>());

		return *this;
	}

	template <typename Type> inline AABB2<Type>& AABB2<Type>::FromPoints(Vec2<Type>* points[], uint32 length) {
		Type minx = MAX_NUMBER<Type>(),
		     miny = MAX_NUMBER<Type>(),
		     maxx = -MAX_NUMBER<Type>(),
		     maxy = -MAX_NUMBER<Type>(),
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
		Type minx = MAX_NUMBER<Type>(),
		     miny = MAX_NUMBER<Type>(),
		     maxx = -MAX_NUMBER<Type>(),
		     maxy = -MAX_NUMBER<Type>(),
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
		     hx = size.x * static_cast<Type>(0.5),
		     hy = size.y * static_cast<Type>(0.5);

		min.x = x - hx;
		min.y = y - hy;

		max.x = x + hx;
		max.y = y + hy;

		return *this;
	}

	template <typename Type> inline AABB2<Type>& AABB2<Type>::FromCenterSize(const Vec2<Type>& center, Type size) {
		Type x = center.x,
		     y = center.y;

		min.x = x - size;
		min.y = y - size;

		max.x = x + size;
		max.y = y + size;

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

	template <typename Type> inline AABB2<Type>& AABB2<Type>::operator -(void) {
		-min;
		-max;
		
		return *this;
	}

	template <typename Type> inline AABB2<Type> AABB2<Type>::operator +(const AABB2<Type>& other) {

		return AABB2<Type>(
		           Vec2<Type>::Min(min, other.min),
		           Vec2<Type>::Max(max, other.max)
		       );
	}

	template <typename Type> inline AABB2<Type> AABB2<Type>::operator +(const Vec2<Type>& v) {

		return AABB2<Type>(
		           min + v,
		           max + v
		       );
	}

	template <typename Type> inline AABB2<Type> AABB2<Type>::operator -(const Vec2<Type>& v) {

		return AABB2<Type>(
		           min - v,
		           max - v
		       );
	}

	template <typename Type> inline AABB2<Type> AABB2<Type>::operator +(Type s) {

		return AABB2<Type>(
		           min + s,
		           max + s
		       );
	}

	template <typename Type> inline AABB2<Type> AABB2<Type>::operator -(Type s) {

		return AABB2<Type>(
		           min - s,
		           max - s
		       );
	}

	template <typename Type> inline AABB2<Type> AABB2<Type>::operator *(Type s) {

		return AABB2<Type>(
		           min * s,
		           max * s
		       );
	}

	template <typename Type> inline AABB2<Type> AABB2<Type>::operator /(Type s) {
		Type d = s == static_cast<Type>(0) ? static_cast<Type>(0) : static_cast<Type>(1) / s;

		return AABB2<Type>(
		           min * d,
		           max * d
		       );
	}

	template <typename Type> inline AABB2<Type>& AABB2<Type>::operator +=(const AABB2<Type>& other) {
		min.Min(other.min);
		max.Max(other.max);

		return *this;
	}

	template <typename Type> inline AABB2<Type>& AABB2<Type>::operator +=(const Vec2<Type>& v) {
		min += v;
		max += v;

		return *this;
	}

	template <typename Type> inline AABB2<Type>& AABB2<Type>::operator -=(const Vec2<Type>& v) {
		min -= v;
		max -= v;

		return *this;
	}

	template <typename Type> inline AABB2<Type>& AABB2<Type>::operator +=(Type s) {
		min += s;
		max += s;

		return *this;
	}

	template <typename Type> inline AABB2<Type>& AABB2<Type>::operator -=(Type s) {
		min -= s;
		max -= s;

		return *this;
	}

	template <typename Type> inline AABB2<Type>& AABB2<Type>::operator *=(Type s) {
		min *= s;
		max *= s;

		return *this;
	}

	template <typename Type> inline AABB2<Type>& AABB2<Type>::operator /=(Type s) {
		Type d = s == static_cast<Type>(0) ? static_cast<Type>(0) : static_cast<Type>(1) / s;

		min *= d;
		max *= d;

		return *this;
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