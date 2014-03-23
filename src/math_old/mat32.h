#ifndef _ODIN_MAT32_H_
#define _ODIN_MAT32_H_

namespace Odin {

	class Mat32 {

		private:
			float32 m_mat[6];

		public:

			inline explicit Mat32(void);
			inline explicit Mat32(float32 m11, float32 m21, float32 m31, float32 m12, float32 m22, float32 m32);
			inline Mat32(const Mat2& m);
			inline Mat32(const Mat2& m, const Vec2& v);
			inline Mat32(const Vec2& v, float32 angle);
			inline Mat32(const Mat32& m);
			inline Mat32(const Mat32&& m);
			inline ~Mat32(void);

			inline Mat32& Identity(void);
			inline Mat32& SetTrace(float32 x, float32 y);

			inline Mat32& operator -();
			inline Mat32& Inverse(void);
			inline Mat32& Inverse(const Mat32& m);

			inline Mat32& Transpose(void);

			inline Mat32& Compose(const Vec2& position, const Vec2& scale, float32 angle);
			inline Mat32& Decompose(Vec2& position, Vec2& scale, float32& angle);

			inline Mat32& SetRotation(float32 a);
			inline float32 GetRotation(void);

			inline Mat32& SetPosition(const Vec2& v);
			inline Vec2 GetPosition(void);

			inline Mat32& Rotate(float32 a);

			inline static Mat32 MakeTranslation(float32 x, float32 y) {

				return Mat32(
				           0.0f, 0.0f, x,
				           0.0f, 0.0f, y
				       );
			}

			inline static Mat32 MakeScale(float32 x, float32 y) {

				return Mat32(
				           x, 0.0f, 0.0f,
				           0.0f, y, 0.0f
				       );
			}

			inline static Mat32 MakeRotation(float32 angle) {
				float32 c = cosf(angle),
				        s = sinf(angle);

				return Mat32(
				           c, -s, 0.0f,
				           s, c, 0.0f
				       );
			}

			inline static Mat32 MakeOrthographic(float32 left, float32 right, float32 top, float32 bottom) {
				Mat32 m;

				return m.Orthographic(left, right, top, bottom);
			}

			inline Mat32& Orthographic(float32 left, float32 right, float32 top, float32 bottom);

			inline float32 operator [] (int32 i) const;
			inline float32& operator [] (int32 i);

			inline Mat32 operator *(const Mat32& m);
			inline void operator *=(const Mat32& m);

			inline void operator *=(float32 s);
			inline void operator /=(float32 s);

			inline Mat32& operator =(const Mat32& m);
			inline Mat32& operator =(const Mat32 && m);

			inline bool operator ==(const Mat32& m);
			inline bool operator !=(const Mat32& m);

			inline std::string ToString(int32 p = 5);
	};
}

#endif