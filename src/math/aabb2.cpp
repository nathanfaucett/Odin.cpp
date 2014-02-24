#ifndef ODIN_AABB2_CPP
#define ODIN_AABB2_CPP


namespace Odin {

	inline AABB2::AABB2(void) {
		min.Set(Infinity, Infinity);
		max.Set(-Infinity, -Infinity);
	}

	inline AABB2::AABB2(const Vec2& MIN, const Vec2& MAX) {
		min = MIN;
		max = MAX;
	}

	inline AABB2::AABB2(const AABB2& other) {
		min = other.min;
		max = other.max;
	}

	inline AABB2::AABB2(const AABB2&& other) {
		min = std::move(other.min);
		max = std::move(other.max);
	}

	inline AABB2::~AABB2(void) {}

	inline AABB2& AABB2::Set(const Vec2& MIN, const Vec2& MAX) {
		min = MIN;
		max = MAX;

		return *this;
	}

	inline AABB2& AABB2::Zero(void) {
		min.Set(0.0f, 0.0f);
		max.Set(0.0f, 0.0f);

		return *this;
	}

	inline AABB2& AABB2::Clear(void) {
		min.Set(Infinity, Infinity);
		max.Set(-Infinity, -Infinity);

		return *this;
	}

	inline AABB2& AABB2::FromPoints(Vec2* points[], const unsigned int length) {
		float minx = Infinity,
		      miny = Infinity,
		      maxx = -Infinity,
		      maxy = -Infinity,
		      x, y;

		Vec2* v;
		unsigned int i = length;

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

	inline AABB2& AABB2::FromPoints(Array<Vec2*> points) {
		float minx = Infinity,
		      miny = Infinity,
		      maxx = -Infinity,
		      maxy = -Infinity,
		      x, y;

		Vec2* v;
		unsigned int i = points.Length();

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

	inline AABB2& AABB2::FromCenterSize(const Vec2& center, const Vec2& size) {
		float x = center.x,
		      y = center.y,
		      hx = size.x * 0.5f,
		      hy = size.y * 0.5f;

		min.x = x - hx;
		min.y = y - hy;

		max.x = x + hx;
		max.y = y + hy;

		return *this;
	}

	inline bool AABB2::Contains(const Vec2& point) {
		float px = point.x,
		      py = point.y;

		return !(
		           px < min.x || px > max.x ||
		           py < min.y || py > max.y
		       );
	}

	inline bool AABB2::Intersects(const AABB2& other) {

		return !(
		           other.max.x < min.x || other.min.x > max.x ||
		           other.max.y < min.y || other.min.y > max.y
		       );
	}

	inline AABB2 AABB2::operator -() {
		-min;
		-max;
	}

	inline AABB2 AABB2::operator +(const AABB2& other) {

		return AABB2(
		           Vec2::Min(min, other.min),
		           Vec2::Max(max, other.max)
		       );
	}

	inline AABB2 AABB2::operator +(const Vec2& v) {

		return AABB2(
		           min + v,
		           max + v
		       );
	}

	inline AABB2 AABB2::operator -(const Vec2& v) {

		return AABB2(
		           min - v,
		           max - v
		       );
	}

	inline AABB2 AABB2::operator +(const float s) {

		return AABB2(
		           min + s,
		           max + s
		       );
	}

	inline AABB2 AABB2::operator -(const float s) {

		return AABB2(
		           min - s,
		           max - s
		       );
	}

	inline AABB2 AABB2::operator *(const float s) {

		return AABB2(
		           min * s,
		           max * s
		       );
	}

	inline AABB2 AABB2::operator /(const float s) {
		float d = s == 0.0f ? 0.0f : 1.0f / s;

		return AABB2(
		           min * d,
		           max * d
		       );
	}

	inline void AABB2::operator +=(const AABB2& other) {
		min.Min(other.min);
		max.Max(other.max);
	}

	inline void AABB2::operator +=(const Vec2& v) {
		min += v;
		max += v;
	}

	inline void AABB2::operator -=(const Vec2& v) {
		min -= v;
		max -= v;
	}

	inline void AABB2::operator +=(const float s) {
		min += s;
		max += s;
	}

	inline void AABB2::operator -=(const float s) {
		min -= s;
		max -= s;
	}

	inline void AABB2::operator *=(const float s) {
		min *= s;
		max *= s;
	}

	inline void AABB2::operator /=(const float s) {
		float d = s == 0.0f ? 0.0f : 1.0f / s;

		min *= d;
		max *= d;
	}

	inline AABB2& AABB2::operator =(const AABB2& other) {
		min = other.min;
		max = other.max;

		return *this;
	}

	inline AABB2& AABB2::operator =(const AABB2 && other) {
		min = std::move(other.min);
		max = std::move(other.max);

		return *this;
	}

	inline bool AABB2::operator ==(const AABB2& other) {

		return !(min != other.min || max != other.max);
	}

	inline bool AABB2::operator !=(const AABB2& other) {

		return min != other.min || max != other.max;
	}

	inline std::string AABB2::ToString(int p) {

		return "AABB2( min: " + min.ToString(p) + ", max: " + max.ToString(p) + ")";
	}
}

#endif