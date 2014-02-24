#ifndef ODIN_AABB3_CPP
#define ODIN_AABB3_CPP


namespace Odin {

	inline AABB3::AABB3(void) {
		min.Set(Infinity, Infinity, Infinity);
		max.Set(-Infinity, -Infinity, -Infinity);
	}

	inline AABB3::AABB3(const Vec3& MIN, const Vec3& MAX) {
		min = MIN;
		max = MAX;
	}

	inline AABB3::AABB3(const AABB3& other) {
		min = other.min;
		max = other.max;
	}

	inline AABB3::AABB3(const AABB3&& other) {
		min = std::move(other.min);
		max = std::move(other.max);
	}

	inline AABB3::~AABB3(void) {}

	inline AABB3& AABB3::Set(const Vec3& MIN, const Vec3& MAX) {
		min = MIN;
		max = MAX;

		return *this;
	}

	inline AABB3& AABB3::Zero(void) {
		min.Set(0.0f, 0.0f, 0.0f);
		max.Set(0.0f, 0.0f, 0.0f);

		return *this;
	}

	inline AABB3& AABB3::Clear(void) {
		min.Set(Infinity, Infinity, Infinity);
		max.Set(-Infinity, -Infinity, -Infinity);

		return *this;
	}

	inline AABB3& AABB3::FromPoints(Vec3* points[], const unsigned int length) {
		float minx = Infinity,
		      miny = Infinity,
		      minz = Infinity,
		      maxx = -Infinity,
		      maxy = -Infinity,
		      maxz = -Infinity,
		      x, y, z;

		Vec3* v;
		unsigned int i = length;

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

	inline AABB3& AABB3::FromPoints(Array<Vec3*> points) {
		float minx = Infinity,
		      miny = Infinity,
		      minz = Infinity,
		      maxx = -Infinity,
		      maxy = -Infinity,
		      maxz = -Infinity,
		      x, y, z;

		Vec3* v;
		unsigned int i = points.Length();

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

	inline AABB3& AABB3::FromCenterSize(const Vec3& center, const Vec3& size) {
		float x = center.x,
		      y = center.y,
		      z = center.z,
		      hx = size.x * 0.5f,
		      hy = size.y * 0.5f,
		      hz = size.z * 0.5f;

		min.x = x - hx;
		min.y = y - hy;
		min.z = z - hz;

		max.x = x + hx;
		max.y = y + hy;
		max.z = z + hz;

		return *this;
	}

	inline bool AABB3::Contains(const Vec3& point) {
		float px = point.x,
		      py = point.y,
		      pz = point.z;

		return !(
		           px < min.x || px > max.x ||
		           py < min.y || py > max.y ||
		           pz < min.z || pz > max.z
		       );
	}

	inline bool AABB3::Intersects(const AABB3& other) {

		return !(
		           other.max.x < min.x || other.min.x > max.x ||
		           other.max.y < min.y || other.min.y > max.y ||
		           other.max.z < min.z || other.min.z > max.z
		       );
	}

	inline AABB3 AABB3::operator -() {
		-min;
		-max;
	}

	inline AABB3 AABB3::operator +(const AABB3& other) {

		return AABB3(
		           Vec3::Min(min, other.min),
		           Vec3::Max(max, other.max)
		       );
	}

	inline AABB3 AABB3::operator +(const Vec3& v) {

		return AABB3(
		           min + v,
		           max + v
		       );
	}

	inline AABB3 AABB3::operator -(const Vec3& v) {

		return AABB3(
		           min - v,
		           max - v
		       );
	}

	inline AABB3 AABB3::operator +(const float s) {

		return AABB3(
		           min + s,
		           max + s
		       );
	}

	inline AABB3 AABB3::operator -(const float s) {

		return AABB3(
		           min - s,
		           max - s
		       );
	}

	inline AABB3 AABB3::operator *(const float s) {

		return AABB3(
		           min * s,
		           max * s
		       );
	}

	inline AABB3 AABB3::operator /(const float s) {
		float d = s == 0.0f ? 0.0f : 1.0f / s;

		return AABB3(
		           min * d,
		           max * d
		       );
	}

	inline void AABB3::operator +=(const AABB3& other) {
		min.Min(other.min);
		max.Max(other.max);
	}

	inline void AABB3::operator +=(const Vec3& v) {
		min += v;
		max += v;
	}

	inline void AABB3::operator -=(const Vec3& v) {
		min -= v;
		max -= v;
	}

	inline void AABB3::operator +=(const float s) {
		min += s;
		max += s;
	}

	inline void AABB3::operator -=(const float s) {
		min -= s;
		max -= s;
	}

	inline void AABB3::operator *=(const float s) {
		min *= s;
		max *= s;
	}

	inline void AABB3::operator /=(const float s) {
		float d = s == 0.0f ? 0.0f : 1.0f / s;

		min *= d;
		max *= d;
	}

	inline AABB3& AABB3::operator =(const AABB3& other) {
		min = other.min;
		max = other.max;

		return *this;
	}

	inline AABB3& AABB3::operator =(const AABB3 && other) {
		min = std::move(other.min);
		max = std::move(other.max);

		return *this;
	}

	inline bool AABB3::operator ==(const AABB3& other) {

		return !(min != other.min || max != other.max);
	}

	inline bool AABB3::operator !=(const AABB3& other) {

		return min != other.min || max != other.max;
	}

	inline std::string AABB3::ToString(int p) {

		return "AABB3( min: " + min.ToString(p) + ", max: " + max.ToString(p) + ")";
	}
}

#endif