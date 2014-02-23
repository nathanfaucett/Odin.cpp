#ifndef ODIN_MAT32_H
#define ODIN_MAT32_H

namespace Odin {

	struct Mat32 {

		private:
			float mat[6];

		public:

			inline explicit Mat32(void);
			inline explicit Mat32(const float m11, const float m12, const float m21, const float m22, const float m31, const float m32);
			inline Mat32(const Mat2& m);
			inline Mat32(const Mat2& m, const Vec2& v);
			inline Mat32(const Vec2& v, const float angle);
			inline Mat32(const Mat32& m);
			inline ~Mat32(void);

			inline Mat32& Identity(void);
			inline Mat32& SetTrace(const float x, const float y);

			inline Mat32& operator -();
			inline Mat32& Inverse(void);
			inline Mat32& Inverse(const Mat32& m);

			inline Mat32& Compose(const Vec2& position, const Vec2& scale, const float angle);
			inline Mat32& Decompose(Vec2& position, Vec2& scale, float& angle);

			inline Mat32& SetRotation(const float a);
			inline float GetRotation(void);
			inline Mat32& SetPosition(const Vec2& v);
			inline Vec2 GetPosition(void);
			inline Mat32& Rotate(const float a);

			inline const float operator [] (int i) const;
			inline float& operator [] (int i);

			inline Mat32 operator *(const Mat32& m);
			inline void operator *=(const Mat32& m);

			inline Mat32 operator *=(const float s);
			inline Mat32 operator /=(const float s);

			inline bool operator ==(const Mat32& m);
			inline bool operator !=(const Mat32& m);

			inline std::string ToString(int p = 5);
	};
}

#endif