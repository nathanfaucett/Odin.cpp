#ifndef ODIN_VEC2_CPP
#define ODIN_VEC2_CPP

namespace Odin{
	
	inline Vec2 Vec2::operator *(const Mat2& m) {
		
		return Vec2(
			x * m[0] + y * m[2],
			x * m[1] + y * m[3]
		);
	}
	
	inline Vec2& Vec2::operator *=(const Mat2& m) {
		float tx = x, ty = y;
		
		x = tx * m[0] + ty * m[2];
		y = tx * m[1] + ty * m[3];
		
		return *this;
	}
	
	inline Vec2 Vec2::operator *(const Mat32& m) {
		
		return Vec2(
			x * m[0] + y * m[2] + m[4],
			x * m[1] + y * m[3] + m[5]
		);
	}
	
	inline Vec2& Vec2::operator *=(const Mat32& m) {
		float tx = x, ty = y;
		
		x = tx * m[0] + ty * m[2] + m[4];
		y = tx * m[1] + ty * m[3] + m[5];
		
		return *this;
	}
	
	inline Vec2 Vec2::operator *(const Mat4& m) {
		
		return Vec2(
			x * m[0] + y * m[4] + m[12],
			x * m[1] + y * m[5] + m[13]
		);
	}
	
	inline Vec2& Vec2::operator *=(const Mat4& m) {
		float tx = x, ty = y;
		
		x = tx * m[0] + ty * m[4] + m[12];
		y = tx * m[1] + ty * m[5] + m[13];
		
		return *this;
	}
}

#endif