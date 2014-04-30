#ifndef ODIN_COLOR_CPP
#define ODIN_COLOR_CPP


namespace Odin {
	
	
	template <typename Type> const Color<Type> Color<Type>::Black(static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0));
	template <typename Type> const Color<Type> Color<Type>::White(static_cast<Type>(1), static_cast<Type>(1), static_cast<Type>(1));
	template <typename Type> const Color<Type> Color<Type>::Red(static_cast<Type>(1), static_cast<Type>(0), static_cast<Type>(0));
	template <typename Type> const Color<Type> Color<Type>::Green(static_cast<Type>(0), static_cast<Type>(1), static_cast<Type>(0));
	template <typename Type> const Color<Type> Color<Type>::Blue(static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1));
	template <typename Type> const Color<Type> Color<Type>::Yellow(static_cast<Type>(1), static_cast<Type>(1), static_cast<Type>(0));
	template <typename Type> const Color<Type> Color<Type>::Orange(static_cast<Type>(0), static_cast<Type>(0.5), static_cast<Type>(0));

	template <typename Type> inline Color<Type>::Color(void) {
		r = static_cast<Type>(0);
		g = static_cast<Type>(0);
		b = static_cast<Type>(0);
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
		b = static_cast<Type>(0);
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

	template <typename Type> inline Color<Type>::~Color<Type>(void) {}
	
	template <typename Type> inline Color<Type>& Color<Type>::Set(Type R, Type G, Type B) {
		r = R;
		g = G;
		b = B;

		return *this;
	}
	
	template <typename Type> inline Color<Type>& Color<Type>::Set(std::string value) {
		
		return *this;
	}

	template <typename Type> inline Color<Type>& Color<Type>::Zero(void) {
		r = static_cast<Type>(0);
		g = static_cast<Type>(0);
		b = static_cast<Type>(0);

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

		return lenSq == static_cast<Type>(0) ? static_cast<Type>(0) : Mathf.Sqrt(lenSq);
	}

	template <typename Type> inline Type Color<Type>::Normalize(void) {
		Type lenSq = r * r + g * g + b * b;

		if (lenSq == static_cast<Type>(0)) {
			return static_cast<Type>(0);
		}

		Type len = Mathf.Sqrt(lenSq), invLen = static_cast<Type>(1) / len;

		r *= invLen;
		g *= invLen;
		b *= invLen;

		return len;
	}

	template <typename Type> inline void Color<Type>::CNormalize(void) {

		r = r > static_cast<Type>(1) ? static_cast<Type>(1) : r < static_cast<Type>(0) ? static_cast<Type>(0) : r;
		g = g > static_cast<Type>(1) ? static_cast<Type>(1) : g < static_cast<Type>(0) ? static_cast<Type>(0) : g;
		b = b > static_cast<Type>(1) ? static_cast<Type>(1) : b < static_cast<Type>(0) ? static_cast<Type>(0) : b;
	}

	template <typename Type> inline void Color<Type>::HexNormalize(void) {

		r = r > static_cast<Type>(255) ? static_cast<Type>(255) : r < static_cast<Type>(0) ? static_cast<Type>(0) : r;
		g = g > static_cast<Type>(255) ? static_cast<Type>(255) : g < static_cast<Type>(0) ? static_cast<Type>(0) : g;
		b = b > static_cast<Type>(255) ? static_cast<Type>(255) : b < static_cast<Type>(0) ? static_cast<Type>(0) : b;
	}

	template <typename Type> inline Color<Type>& Color<Type>::Lerp(const Color<Type>& c, Type t) {
		r = Mathf.Lerp(r, c.r, t);
		g = Mathf.Lerp(g, c.g, t);
		b = Mathf.Lerp(b, c.b, t);

		return *this;
	}

	template <typename Type> inline Color<Type>& Color<Type>::operator -() {
		r = static_cast<Type>(1) - r;
		g = static_cast<Type>(1) - g;
		b = static_cast<Type>(1) - b;

		return *this;
	}

	template <typename Type> inline Type Color<Type>::operator [] (int32 i) const {
		return (&r)[i];
	}

	template <typename Type> inline Type& Color<Type>::operator [] (int32 i) {
		return (&r)[i];
	}

	template <typename Type> inline Color<Type> Color<Type>::operator +(const Color<Type>& c) {

		return Color<Type>(r + c.r, g + c.g, b + c.b);
	}

	template <typename Type> inline Color<Type> Color<Type>::operator -(const Color<Type>& c) {

		return Color<Type>(r - c.r, g - c.g, b - c.b);
	}

	template <typename Type> inline Color<Type> Color<Type>::operator *(const Color<Type>& c) {

		return Color<Type>(r * c.r, g * c.g, b * c.b);
	}

	template <typename Type> inline Color<Type> Color<Type>::operator /(const Color<Type>& c) {
		Type cx = c.r, cy = c.g, cz = c.g;

		cx = cx != static_cast<Type>(0) ? static_cast<Type>(1) / cx : static_cast<Type>(0);
		cy = cy != static_cast<Type>(0) ? static_cast<Type>(1) / cy : static_cast<Type>(0);
		cz = cz != static_cast<Type>(0) ? static_cast<Type>(1) / cz : static_cast<Type>(0);

		return Color<Type>(r * cx, g * cy, b * cz);
	}

	template <typename Type> inline void Color<Type>::operator +=(const Color<Type>& c) {
		r += c.r;
		g += c.g;
		b += c.b;

		return *this;
	}

	template <typename Type> inline void Color<Type>::operator -=(const Color<Type>& c) {
		r -= c.r;
		g -= c.g;
		b -= c.b;

		return *this;
	}

	template <typename Type> inline void Color<Type>::operator *=(const Color<Type>& c) {
		r *= c.r;
		g *= c.g;
		b *= c.b;

		return *this;
	}

	template <typename Type> inline void Color<Type>::operator /=(const Color<Type>& c) {
		Type cx = c.r, cy = c.g, cz = c.b;

		r *= cx != static_cast<Type>(0) ? static_cast<Type>(1) / cx : static_cast<Type>(0);
		g *= cy != static_cast<Type>(0) ? static_cast<Type>(1) / cy : static_cast<Type>(0);
		b *= cz != static_cast<Type>(0) ? static_cast<Type>(1) / cz : static_cast<Type>(0);
	}


	template <typename Type> inline Color<Type> Color<Type>::operator +(Type s) {

		return Color<Type>(r + s, g + s, b + s);
	}

	template <typename Type> inline Color<Type> Color<Type>::operator -(Type s) {

		return Color<Type>(r - s, g - s, b - s);
	}

	template <typename Type> inline Color<Type> Color<Type>::operator *(Type s) {

		return Color<Type>(r * s, g * s, b * s);
	}

	template <typename Type> inline Color<Type> Color<Type>::operator /(Type s) {
		Type d = s != static_cast<Type>(0) ? static_cast<Type>(1) / s : static_cast<Type>(0);

		return Color<Type>(r * d, g * d, b * d);
	}

	template <typename Type> inline void Color<Type>::operator +=(Type s) {
		r += s;
		g += s;
		b += s;

		return *this;
	}

	template <typename Type> inline void Color<Type>::operator -=(Type s) {
		r -= s;
		g -= s;
		b -= s;

		return *this;
	}

	template <typename Type> inline void Color<Type>::operator *=(Type s) {
		r *= s;
		g *= s;
		b *= s;

		return *this;
	}

	template <typename Type> inline void Color<Type>::operator /=(Type s) {
		Type d = s != static_cast<Type>(0) ? static_cast<Type>(1) / s : static_cast<Type>(0);

		r *= d;
		g *= d;
		b *= d;

		return *this;
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

		return "Color(" + Odin::ToString(r, p) + ", " + Odin::ToString(g, p) + ", " + Odin::ToString(b, p) + ")";
	}
}

#endif