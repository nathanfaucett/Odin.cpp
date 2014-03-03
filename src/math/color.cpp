#ifndef _ODIN_COLOR_CPP
#define _ODIN_COLOR_CPP


namespace Odin {

	inline Color::Color(void) {
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
	}

	inline Color::Color(float32 X) {
		r = X;
		g = X;
		b = X;
	}

	inline Color::Color(float32 R, float32 G, float32 B) {
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

	inline Color::Color(const Color&& c) {
		r = std::move(c.r);
		g = std::move(c.g);
		b = std::move(c.b);
	}

	inline Color::~Color(void) {}

	inline Color& Color::Set(float32 R, float32 G, float32 B) {
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

	inline float32 Color::Dot(const Color c) {

		return r * c.r + g * c.g + b * c.b;
	}

	inline float32 Color::LengthSq(void) {

		return r * r + g * g + b * b;
	}

	inline float32 Color::Length(void) {
		float32 lenSq = r * r + g * g + b * b;

		return lenSq == 0.0f ? 0.0f : sqrtf(lenSq);
	}

	inline float32 Color::Normalize(void) {
		float32 lenSq = r * r + g * g + b * b;

		if (lenSq == 0.0f) {
			return 0.0f;
		}

		float32 len = sqrtf(lenSq), invLen = 1.0f / len;

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

	inline Color& Color::Lerp(const Color& c, float32 t) {
		r = Mathf.Lerp(r, c.r, t);
		g = Mathf.Lerp(g, c.g, t);
		b = Mathf.Lerp(b, c.b, t);

		return *this;
	}

	inline Color& Color::operator -() {
		r = 1.0f - r;
		g = 1.0f - g;
		b = 1.0f - b;

		return *this;
	}

	inline float32 Color::operator [] (int32 i) const {
		return (&r)[i];
	}

	inline float32& Color::operator [] (int32 i) {
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
		float32 cx = c.r, cy = c.g, cz = c.g;

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
		float32 cx = c.r, cy = c.g, cz = c.b;

		r *= cx != 0.0f ? 1.0f / cx : 0.0f;
		g *= cy != 0.0f ? 1.0f / cy : 0.0f;
		b *= cz != 0.0f ? 1.0f / cz : 0.0f;
	}


	inline Color Color::operator +(float32 s) {

		return Color(r + s, g + s, b + s);
	}

	inline Color Color::operator -(float32 s) {

		return Color(r - s, g - s, b - s);
	}

	inline Color Color::operator *(float32 s) {

		return Color(r * s, g * s, b * s);
	}

	inline Color Color::operator /(float32 s) {
		float32 d = s != 0.0f ? 1.0f / s : 0.0f;

		return Color(r * d, g * d, b * d);
	}

	inline void Color::operator +=(float32 s) {
		r += s;
		g += s;
		b += s;
	}

	inline void Color::operator -=(float32 s) {
		r -= s;
		g -= s;
		b -= s;
	}

	inline void Color::operator *=(float32 s) {
		r *= s;
		g *= s;
		b *= s;
	}

	inline void Color::operator /=(float32 s) {
		float32 d = s != 0.0f ? 1.0f / s : 0.0f;

		r *= d;
		g *= d;
		b *= d;
	}

	inline Color& Color::operator =(const Color& c) {

		r = c.r;
		g = c.g;
		b = c.b;

		return *this;
	}

	inline Color& Color::operator =(const Color && c) {

		r = std::move(c.r);
		g = std::move(c.g);
		b = std::move(c.b);

		return *this;
	}

	inline bool Color::operator ==(const Color& c) {

		return !(r != c.r || g != c.g || b != c.b);
	}

	inline bool Color::operator !=(const Color& c) {

		return r != c.r || g != c.g || b != c.b;
	}

	inline std::string Color::ToString(int32 p) {

		return "Color(" + util.ToString(r, p) + ", " + util.ToString(g, p) + ", " + util.ToString(b, p) + ")";
	}
}

#endif