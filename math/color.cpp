#ifndef ODIN_COLOR_CPP
#define ODIN_COLOR_CPP


namespace Odin {

	inline Color::Color(void) {
		r = 0;
		g = 0;
		b = 0;
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
		b = 0;
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

	inline Color& Color::Zero() {
		r = 0;
		g = 0;
		b = 0;

		return *this;
	}

	inline float Color::Dot(const Color c) {

		return r * c.r + g * c.g + b * c.b;
	}

	inline float Color::LengthSq() {

		return r * r + g * g + b * b;
	}

	inline float Color::Length() {
		float lenSq = r * r + g * g + b * b;

		return lenSq == 0 ? 0 : std::sqrt(lenSq);
	}

	inline float Color::Normalize() {
		float lenSq = r * r + g * g + b * b;

		if (lenSq == 0) {
			return 0;
		}

		float len = std::sqrt(lenSq), invLen = 1 / len;

		r *= invLen;
		g *= invLen;
		b *= invLen;

		return len;
	}

	inline void Color::CNormalize() {

		r = r > 1 ? 1 : r < 0 ? 0 : r;
		g = g > 1 ? 1 : g < 0 ? 0 : g;
		b = b > 1 ? 1 : b < 0 ? 0 : b;
	}

	inline Color& Color::Lerp(const Color& c, const float t) {
		r = Mathf.Lerp(r, c.r, t);
		g = Mathf.Lerp(g, c.g, t);
		b = Mathf.Lerp(b, c.b, t);

		return *this;
	}

	inline Color Color::operator -() {
		r = 1 - r;
		g = 1 - g;
		b = 1 - b;
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

		cx = cx != 0 ? 1 / cx : 0;
		cy = cy != 0 ? 1 / cy : 0;
		cz = cz != 0 ? 1 / cz : 0;

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

		r *= cx != 0 ? 1 / cx : 0;
		g *= cy != 0 ? 1 / cy : 0;
		b *= cz != 0 ? 1 / cz : 0;
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
		float d = s != 0 ? 1 / s : 0;

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
		float d = s != 0 ? 1 / s : 0;

		r *= d;
		g *= d;
		b *= d;
	}

	inline Color Color::operator =(const Color& c) {
		r = c.r;
		g = c.g;
		b = c.b;
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