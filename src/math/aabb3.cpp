#ifndef ODIN_AABB3_CPP
#define ODIN_AABB3_CPP


namespace Odin {

	template <typename Type> inline AABB3<Type>::AABB3(void) {
		min.Set(Infinity, Infinity, Infinity);
		max.Set(-Infinity, -Infinity, -Infinity);
	}

	template <typename Type> inline AABB3<Type>::AABB3(const Vec3<Type>& MIN, const Vec3<Type>& MAX) {
		min = MIN;
		max = MAX;
	}

	template <typename Type> inline AABB3<Type>::AABB3(const AABB3<Type>& other) {
		min = other.min;
		max = other.max;
	}

	template <typename Type> inline AABB3<Type>::AABB3(const AABB3<Type>&& other) {
		min = std::move(other.min);
		max = std::move(other.max);
	}

	template <typename Type> inline AABB3<Type>::~AABB3(void) {}

	template <typename Type> inline AABB3<Type>& AABB3<Type>::Set(const Vec3<Type>& MIN, const Vec3<Type>& MAX) {
		min = MIN;
		max = MAX;

		return *this;
	}

	template <typename Type> inline AABB3<Type>& AABB3<Type>::Zero(void) {
		min.Set(0, 0, 0);
		max.Set(0, 0, 0);

		return *this;
	}

	template <typename Type> inline AABB3<Type>& AABB3<Type>::Clear(void) {
		min.Set(Infinity, Infinity, Infinity);
		max.Set(-Infinity, -Infinity, -Infinity);

		return *this;
	}

	template <typename Type> inline AABB3<Type>& AABB3<Type>::FromPoints(Vec3<Type>* points[], uint32 length) {
		Type minx = Infinity,
		     miny = Infinity,
		     minz = Infinity,
		     maxx = -Infinity,
		     maxy = -Infinity,
		     maxz = -Infinity,
		     x, y, z;

		Vec3<Type>* v;
		uint32 i = length;

		while (i--) {
			v = points[i];
			assert(v != NULL);
			x = v->x;
			y = v->y;
			z = v->z;

			minx = minx > x ? x : minx;
			miny = miny > y ? y : miny;
			minz = minz > z ? z : minz;

			maxx = maxx < x ? x : maxx;
			maxy = maxy < y ? y : maxy;
			maxz = maxz < z ? z : maxz;
		}

		min.x = minx;
		min.y = miny;
		min.z = minz;
		max.x = maxx;
		max.y = maxy;
		max.z = maxz;

		return *this;
	}

	template <typename Type> inline AABB3<Type>& AABB3<Type>::FromPoints(Array<Vec3<Type>*> points) {
		Type minx = Infinity,
		     miny = Infinity,
		     minz = Infinity,
		     maxx = -Infinity,
		     maxy = -Infinity,
		     maxz = -Infinity,
		     x, y, z;

		Vec3<Type>* v;
		uint32 i = points.Length();

		while (i--) {
			v = points[i];
			assert(v != NULL);
			x = v->x;
			y = v->y;
			z = v->z;

			minx = minx > x ? x : minx;
			miny = miny > y ? y : miny;
			minz = minz > z ? z : minz;

			maxx = maxx < x ? x : maxx;
			maxy = maxy < y ? y : maxy;
			maxz = maxz < z ? z : maxz;
		}

		min.x = minx;
		min.y = miny;
		min.z = minz;
		max.x = maxx;
		max.y = maxy;
		max.z = maxz;

		return *this;
	}

	template <typename Type> inline AABB3<Type>& AABB3<Type>::FromCenterSize(const Vec3<Type>& center, const Vec3<Type>& size) {
		Type x = center.x,
		     y = center.y,
		     z = center.z,
		     hx = size.x * 0.5,
		     hy = size.y * 0.5,
		     hz = size.z * 0.5;

		min.x = x - hx;
		min.y = y - hy;
		min.z = z - hz;

		max.x = x + hx;
		max.y = y + hy;
		max.z = z + hz;

		return *this;
	}

	template <typename Type> inline bool AABB3<Type>::Contains(const Vec3<Type>& point) {
		Type px = point.x,
		     py = point.y,
		     pz = point.z;

		return !(
		           px < min.x || px > max.x ||
		           py < min.y || py > max.y ||
		           pz < min.z || pz > max.z
		       );
	}

	template <typename Type> inline bool AABB3<Type>::Intersects(const AABB3<Type>& other) {

		return !(
		           other.max.x < min.x || other.min.x > max.x ||
		           other.max.y < min.y || other.min.y > max.y ||
		           other.max.z < min.z || other.min.z > max.z
		       );
	}

	template <typename Type> inline void AABB3<Type>::operator -() {
		-min;
		-max;
	}

	template <typename Type> inline AABB3<Type> AABB3<Type>::operator +(const AABB3<Type>& other) {

		return AABB3(
		           Vec3<Type>::Min(min, other.min),
		           Vec3<Type>::Max(max, other.max)
		       );
	}

	template <typename Type> inline AABB3<Type> AABB3<Type>::operator +(const Vec3<Type>& v) {

		return AABB3(
		           min + v,
		           max + v
		       );
	}

	template <typename Type> inline AABB3<Type> AABB3<Type>::operator -(const Vec3<Type>& v) {

		return AABB3(
		           min - v,
		           max - v
		       );
	}

	template <typename Type> inline AABB3<Type> AABB3<Type>::operator +(Type s) {

		return AABB3(
		           min + s,
		           max + s
		       );
	}

	template <typename Type> inline AABB3<Type> AABB3<Type>::operator -(Type s) {

		return AABB3(
		           min - s,
		           max - s
		       );
	}

	template <typename Type> inline AABB3<Type> AABB3<Type>::operator *(Type s) {

		return AABB3(
		           min * s,
		           max * s
		       );
	}

	template <typename Type> inline AABB3<Type> AABB3<Type>::operator /(Type s) {
		Type d = s == 0 ? 0 : 1 / s;

		return AABB3(
		           min * d,
		           max * d
		       );
	}

	template <typename Type> inline void AABB3<Type>::operator +=(const AABB3<Type>& other) {
		min.Min(other.min);
		max.Max(other.max);
	}

	template <typename Type> inline void AABB3<Type>::operator +=(const Vec3<Type>& v) {
		min += v;
		max += v;
	}

	template <typename Type> inline void AABB3<Type>::operator -=(const Vec3<Type>& v) {
		min -= v;
		max -= v;
	}

	template <typename Type> inline void AABB3<Type>::operator +=(Type s) {
		min += s;
		max += s;
	}

	template <typename Type> inline void AABB3<Type>::operator -=(Type s) {
		min -= s;
		max -= s;
	}

	template <typename Type> inline void AABB3<Type>::operator *=(Type s) {
		min *= s;
		max *= s;
	}

	template <typename Type> inline void AABB3<Type>::operator /=(Type s) {
		Type d = s == 0 ? 0 : 1 / s;

		min *= d;
		max *= d;
	}

	template <typename Type> inline AABB3<Type>& AABB3<Type>::operator =(const AABB3<Type>& other) {
		min = other.min;
		max = other.max;

		return *this;
	}

	template <typename Type> inline AABB3<Type>& AABB3<Type>::operator =(const AABB3<Type> && other) {
		min = std::move(other.min);
		max = std::move(other.max);

		return *this;
	}

	template <typename Type> inline bool AABB3<Type>::operator ==(const AABB3<Type>& other) {

		return !(min != other.min || max != other.max);
	}

	template <typename Type> inline bool AABB3<Type>::operator !=(const AABB3<Type>& other) {

		return min != other.min || max != other.max;
	}

	template <typename Type> inline std::string AABB3<Type>::ToString(int32 p) {

		return "AABB3( min: " + min.ToString(p) + ", max: " + max.ToString(p) + ")";
	}
}

#endif