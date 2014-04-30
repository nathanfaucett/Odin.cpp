#ifndef ODIN_MAT2_H
#define ODIN_MAT2_H

namespace Odin {

	template <typename Type> class Mat2 {

		private:
			Type m_mat[4];

		public:

			inline explicit Mat2(void);
			inline explicit Mat2(Type m11, Type m21, Type m12, Type m22);
			inline Mat2(const Mat2<Type>& m);
			inline Mat2(const Mat2<Type>&& m);
			inline ~Mat2(void);

			inline Mat2<Type>& Identity(void);
			inline Mat2<Type>& SetTrace(Type x, Type y);

			inline Mat2<Type>& operator -(void);
			inline Mat2<Type>& Inverse(void);
			inline Mat2<Type>& Inverse(const Mat2<Type>& m);

			inline Mat2<Type>& Transpose(void);

			inline Mat2<Type>& SetRotation(Type a);

			inline Type GetRotation(void);

			inline Mat2<Type>& Rotate(Type a);

			inline Type operator [] (int32 i) const;

			inline Type& operator [] (int32 i);

			inline Mat2<Type> operator *(const Mat2<Type>& m);
			inline Mat2<Type>& operator *=(const Mat2<Type>& m);

			inline Mat2<Type>& operator *=(Type s);
			inline Mat2<Type>& operator /=(Type s);

			inline Mat2<Type>& operator =(const Mat2<Type>& m);
			inline Mat2<Type>& operator =(const Mat2<Type> && m);

			inline bool operator ==(const Mat2<Type>& m);
			inline bool operator !=(const Mat2<Type>& m);

			inline std::string ToString(int32 p = 6);
	};
}

#endif