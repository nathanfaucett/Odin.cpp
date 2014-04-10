#ifndef ODIN_MAT32_H
#define ODIN_MAT32_H

namespace Odin {

	template <typename Type> class Mat32 {

		private:
			Type m_mat[6];

		public:

			inline explicit Mat32(void);
			inline explicit Mat32(Type m11, Type m21, Type m31, Type m12, Type m22, Type m32);
			inline Mat32(const Mat2<Type>& m);
			inline Mat32(const Mat2<Type>& m, const Vec2<Type>& v);
			inline Mat32(const Vec2<Type>& v, Type angle);
			inline Mat32(const Mat32<Type>& m);
			inline Mat32(const Mat32<Type>&& m);
			inline ~Mat32(void);

			inline Mat32<Type>& Identity(void);
			inline Mat32<Type>& SetTrace(Type x, Type y);

			inline Mat32<Type>& operator -();
			inline Mat32<Type>& Inverse(void);
			inline Mat32<Type>& Inverse(const Mat32<Type>& m);

			inline Mat32<Type>& Transpose(void);

			inline Mat32<Type>& Compose(const Vec2<Type>& position, const Vec2<Type>& scale, Type angle);
			inline Mat32<Type>& Decompose(Vec2<Type>& position, Vec2<Type>& scale, Type& angle);

			inline Mat32<Type>& SetRotation(Type a);
			inline Type GetRotation(void);

			inline Mat32<Type>& SetPosition(const Vec2<Type>& v);
			inline Vec2<Type> GetPosition(void);

			inline Mat32<Type>& Rotate(Type a);

			inline static Mat32<Type> MakeTranslation(Type x, Type y) {

				return Mat32(
				           0, 0, x,
				           0, 0, y
				       );
			}

			inline static Mat32<Type> MakeScale(Type x, Type y) {

				return Mat32(
				           x, 0, 0,
				           0, y, 0
				       );
			}

			inline static Mat32<Type> MakeRotation(Type angle) {
				Type c = Mathf.Cos(angle),
				     s = Mathf.Sin(angle);

				return Mat32(
				           c, -s, 0,
				           s, c, 0
				       );
			}

			inline static Mat32<Type> MakeOrthographic(Type left, Type right, Type top, Type bottom) {
				Mat32<Type> m;

				return m.Orthographic(left, right, top, bottom);
			}

			inline Mat32<Type>& Orthographic(Type left, Type right, Type top, Type bottom);

			inline Type operator [] (int32 i) const;
			inline Type& operator [] (int32 i);

			inline Mat32<Type> operator *(const Mat32<Type>& m);
			inline void operator *=(const Mat32<Type>& m);

			inline void operator *=(Type s);
			inline void operator /=(Type s);

			inline Mat32<Type>& operator =(const Mat32<Type>& m);
			inline Mat32<Type>& operator =(const Mat32<Type> && m);

			inline bool operator ==(const Mat32<Type>& m);
			inline bool operator !=(const Mat32<Type>& m);

			inline std::string ToString(int32 p = 5);
	};
}

#endif