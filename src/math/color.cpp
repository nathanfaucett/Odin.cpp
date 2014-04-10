#ifndef ODIN_COLOR_CPP
#define ODIN_COLOR_CPP


namespace Odin {

	template <typename Type> inline Color<Type>::Color(void) {
		r = 0;
		g = 0;
		b = 0;
	}

	template <typename Type> inline Color<Type>::Color(Type X) {
		r = X;
		g = X;
		b = X;
	}

	template <typename Type> inline Color<Type>::Color(Type R, Type G, Type B) {
		r = R;
		g = G;
		b = B;
	}

	template <typename Type> inline Color<Type>::Color(const Vec2<Type>& v) {
		r = v.x;
		g = v.y;
		b = 0;
	}

	template <typename Type> inline Color<Type>::Color(const Vec3<Type>& v) {
		r = v.x;
		g = v.y;
		b = v.z;
	}

	template <typename Type> inline Color<Type>::Color(const Vec4<Type>& v) {
		r = v.x;
		g = v.y;
		b = v.z;
	}

	template <typename Type> inline Color<Type>::Color(const Color<Type>& c) {
		r = c.r;
		g = c.g;
		b = c.b;
	}

	template <typename Type> inline Color<Type>::Color(const Color<Type>&& c) {
		r = std::move(c.r);
		g = std::move(c.g);
		b = std::move(c.b);
	}

	template <typename Type> inline Color<Type>::~Color(void) {}

	template <typename Type> inline Color<Type>& Color<Type>::Set(Type R, Type G, Type B) {
		r = R;
		g = G;
		b = B;

		return *this;
	}

	template <typename Type> inline Color<Type>& Color<Type>::Zero(void) {
		r = 0;
		g = 0;
		b = 0;

		return *this;
	}

	template <typename Type> inline Type Color<Type>::Dot(const Color<Type> c) {

		return r * c.r + g * c.g + b * c.b;
	}

	template <typename Type> inline Type Color<Type>::LengthSq(void) {

		return r * r + g * g + b * b;
	}

	template <typename Type> inline Type Color<Type>::Length(void) {
		Type lenSq = r * r + g * g + b * b;

		return lenSq == 0 ? 0 : sqrtf(lenSq);
	}

	template <typename Type> inline Type Color<Type>::Normalize(void) {
		Type lenSq = r * r + g * g + b * b;

		if (lenSq == 0) {
			return 0;
		}

		Type len = sqrtf(lenSq), invLen = 1 / len;

		r *= invLen;
		g *= invLen;
		b *= invLen;

		return len;
	}

	template <typename Type> inline void Color<Type>::CNormalize(void) {

		r = r > 1 ? 1 : r < 0 ? 0 : r;
		g = g > 1 ? 1 : g < 0 ? 0 : g;
		b = b > 1 ? 1 : b < 0 ? 0 : b;
	}

	template <typename Type> inline void Color<Type>::HexNormalize(void) {

		r = r > 255 ? 255 : r < 0 ? 0 : r;
		g = g > 255 ? 255 : g < 0 ? 0 : g;
		b = b > 255 ? 255 : b < 0 ? 0 : b;
	}

	template <typename Type> inline Color<Type>& Color<Type>::Lerp(const Color<Type>& c, Type t) {
		r = Mathf.Lerp(r, c.r, t);
		g = Mathf.Lerp(g, c.g, t);
		b = Mathf.Lerp(b, c.b, t);

		return *this;
	}

	template <typename Type> inline Color<Type>& Color<Type>::operator -() {
		r = 1 - r;
		g = 1 - g;
		b = 1 - b;

		return *this;
	}

	template <typename Type> inline Type Color<Type>::operator [] (int32 i) const {
		return (&r)[i];
	}

	template <typename Type> inline Type& Color<Type>::operator [] (int32 i) {
		return (&r)[i];
	}

	template <typename Type> inline Color<Type> Color<Type>::operator +(const Color<Type>& c) {

		return Color(r + c.r, g + c.g, b + c.b);
	}

	template <typename Type> inline Color<Type> Color<Type>::operator -(const Color<Type>& c) {

		return Color(r - c.r, g - c.g, b - c.b);
	}

	template <typename Type> inline Color<Type> Color<Type>::operator *(const Color<Type>& c) {

		return Color(r * c.r, g * c.g, b * c.b);
	}

	template <typename Type> inline Color<Type> Color<Type>::operator /(const Color<Type>& c) {
		Type cx = c.r, cy = c.g, cz = c.g;

		cx = cx != 0 ? 1 / cx : 0;
		cy = cy != 0 ? 1 / cy : 0;
		cz = cz != 0 ? 1 / cz : 0;

		return Color(r * cx, g * cy, b * cz);
	}

	template <typename Type> inline void Color<Type>::operator +=(const Color<Type>& c) {
		r += c.r;
		g += c.g;
		b += c.b;
	}

	template <typename Type> inline void Color<Type>::operator -=(const Color<Type>& c) {
		r -= c.r;
		g -= c.g;
		b -= c.b;
	}

	template <typename Type> inline void Color<Type>::operator *=(const Color<Type>& c) {
		r *= c.r;
		g *= c.g;
		b *= c.b;
	}

	template <typename Type> inline void Color<Type>::operator /=(const Color<Type>& c) {
		Type cx = c.r, cy = c.g, cz = c.b;

		r *= cx != 0 ? 1 / cx : 0;
		g *= cy != 0 ? 1 / cy : 0;
		b *= cz != 0 ? 1 / cz : 0;
	}


	template <typename Type> inline Color<Type> Color<Type>::operator +(Type s) {

		return Color(r + s, g + s, b + s);
	}

	template <typename Type> inline Color<Type> Color<Type>::operator -(Type s) {

		return Color(r - s, g - s, b - s);
	}

	template <typename Type> inline Color<Type> Color<Type>::operator *(Type s) {

		return Color(r * s, g * s, b * s);
	}

	template <typename Type> inline Color<Type> Color<Type>::operator /(Type s) {
		Type d = s != 0 ? 1 / s : 0;

		return Color(r * d, g * d, b * d);
	}

	template <typename Type> inline void Color<Type>::operator +=(Type s) {
		r += s;
		g += s;
		b += s;
	}

	template <typename Type> inline void Color<Type>::operator -=(Type s) {
		r -= s;
		g -= s;
		b -= s;
	}

	template <typename Type> inline void Color<Type>::operator *=(Type s) {
		r *= s;
		g *= s;
		b *= s;
	}

	template <typename Type> inline void Color<Type>::operator /=(Type s) {
		Type d = s != 0 ? 1 / s : 0;

		r *= d;
		g *= d;
		b *= d;
	}

	template <typename Type> inline Color<Type>& Color<Type>::operator =(const Color<Type>& c) {

		r = c.r;
		g = c.g;
		b = c.b;

		return *this;
	}

	template <typename Type> inline Color<Type>& Color<Type>::operator =(const Color<Type> && c) {

		r = std::move(c.r);
		g = std::move(c.g);
		b = std::move(c.b);

		return *this;
	}

	template <typename Type> inline bool Color<Type>::operator ==(const Color<Type>& c) {

		return !(r != c.r || g != c.g || b != c.b);
	}

	template <typename Type> inline bool Color<Type>::operator !=(const Color<Type>& c) {

		return r != c.r || g != c.g || b != c.b;
	}

	template <typename Type> inline std::string Color<Type>::ToString(int32 p) {

		return "Color(" + Util.ToString(r, p) + ", " + Util.ToString(g, p) + ", " + Util.ToString(b, p) + ")";
	}
}

#endif