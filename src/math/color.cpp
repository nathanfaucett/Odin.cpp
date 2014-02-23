#ifndef ODIN_COLOR_CPP
#define ODIN_COLOR_CPP


namespace Odin {

	inline Color::Color(void) {
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
	}

	inline Color::Color(const float X) {
		r = X;
		g = X;
		b = X;
	}

	inline Color::Color(const float R, const float G, const float B) {
		r = R;
		g = G;
		b = B;
	}

	inline Color::Color(const Vec2& v) {
		r = v.x;
		g = v.y;
		b = 0.0f;
	}

	inline Color::Color(const Vec3& v) {
		r = v.x;
		g = v.y;
		b = v.z;
	}

	inline Color::Color(const Vec4& v) {
		r = v.x;
		g = v.y;
		b = v.z;
	}

	inline Color::Color(const Color& c) {
		r = c.r;
		g = c.g;
		b = c.b;
	}

	inline Color::~Color(void) {}

	inline Color& Color::Set(const float R, const float G, const float B) {
		r = R;
		g = G;
		b = B;

		return *this;
	}

	inline Color& Color::Zero(void) {
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;

		return *this;
	}

	inline float Color::Dot(const Color c) {

		return r * c.r + g * c.g + b * c.b;
	}

	inline float Color::LengthSq(void) {

		return r * r + g * g + b * b;
	}

	inline float Color::Length(void) {
		float lenSq = r * r + g * g + b * b;

		return lenSq == 0.0f ? 0.0f : sqrtf(lenSq);
	}

	inline float Color::Normalize(void) {
		float lenSq = r * r + g * g + b * b;

		if (lenSq == 0.0f) {
			return 0.0f;
		}

		float len = sqrtf(lenSq), invLen = 1 / len;

		r *= invLen;
		g *= invLen;
		b *= invLen;

		return len;
	}

	inline void Color::CNormalize(void) {

		r = r > 1.0f ? 1.0f : r < 0.0f ? 0.0f : r;
		g = g > 1.0f ? 1.0f : g < 0.0f ? 0.0f : g;
		b = b > 1.0f ? 1.0f : b < 0.0f ? 0.0f : b;
	}

	inline Color& Color::Lerp(const Color& c, const float t) {
		r = Mathf.Lerp(r, c.r, t);
		g = Mathf.Lerp(g, c.g, t);
		b = Mathf.Lerp(b, c.b, t);

		return *this;
	}

	inline Color Color::operator -() {
		r = 1.0f - r;
		g = 1.0f - g;
		b = 1.0f - b;
	}

	inline float Color::operator [] (int i) const {
		return (&r)[i];
	}

	inline float& Color::operator [] (int i) {
		return (&r)[i];
	}

	inline Color Color::operator +(const Color& c) {

		return Color(r + c.r, g + c.g, b + c.b);
	}

	inline Color Color::operator -(const Color& c) {

		return Color(r - c.r, g - c.g, b - c.b);
	}

	inline Color Color::operator *(const Color& c) {

		return Color(r * c.r, g * c.g, b * c.b);
	}

	inline Color Color::operator /(const Color& c) {
		float cx = c.r, cy = c.g, cz = c.g;

		cx = cx != 0.0f ? 1.0f / cx : 0.0f;
		cy = cy != 0.0f ? 1.0f / cy : 0.0f;
		cz = cz != 0.0f ? 1.0f / cz : 0.0f;

		return Color(r * cx, g * cy, b * cz);
	}

	inline void Color::operator +=(const Color& c) {
		r += c.r;
		g += c.g;
		b += c.b;
	}

	inline void Color::operator -=(const Color& c) {
		r -= c.r;
		g -= c.g;
		b -= c.b;
	}

	inline void Color::operator *=(const Color& c) {
		r *= c.r;
		g *= c.g;
		b *= c.b;
	}

	inline void Color::operator /=(const Color& c) {
		float cx = c.r, cy = c.g, cz = c.b;

		r *= cx != 0.0f ? 1.0f / cx : 0.0f;
		g *= cy != 0.0f ? 1.0f / cy : 0.0f;
		b *= cz != 0.0f ? 1.0f / cz : 0.0f;
	}


	inline Color Color::operator +(const float s) {

		return Color(r + s, g + s, b + s);
	}

	inline Color Color::operator -(const float s) {

		return Color(r - s, g - s, b - s);
	}

	inline Color Color::operator *(const float s) {

		return Color(r * s, g * s, b * s);
	}

	inline Color Color::operator /(const float s) {
		float d = s != 0.0f ? 1.0f / s : 0.0f;

		return Color(r * d, g * d, b * d);
	}

	inline void Color::operator +=(const float s) {
		r += s;
		g += s;
		b += s;
	}

	inline void Color::operator -=(const float s) {
		r -= s;
		g -= s;
		b -= s;
	}

	inline void Color::operator *=(const float s) {
		r *= s;
		g *= s;
		b *= s;
	}

	inline void Color::operator /=(const float s) {
		float d = s != 0.0f ? 1.0f / s : 0.0f;

		r *= d;
		g *= d;
		b *= d;
	}

	inline bool Color::operator ==(const Color& c) {

		return !(r != c.r || g != c.g || b != c.b);
	}

	inline bool Color::operator !=(const Color& c) {

		return r != c.r || g != c.g || b != c.b;
	}

	inline std::string Color::ToString(int p) {

		return "Color(" + util.ToString(r, p) + ", " + util.ToString(g, p) + ", " + util.ToString(b, p) + ")";
	}
}

#endif