#ifndef _ODIN_MAT2_H
#define _ODIN_MAT2_H

namespace Odin {

	class Mat2 {

		private:
			float32 m_mat[4];

		public:

			inline explicit Mat2(void);
			inline explicit Mat2(float32 m11, float32 m21, float32 m12, float32 m22);
			inline Mat2(const Mat2& m);
			inline Mat2(const Mat2&& m);
			inline ~Mat2(void);

			inline Mat2& Identity(void);
			inline Mat2& SetTrace(float32 x, float32 y);

			inline Mat2& operator -();
			inline Mat2& Inverse(void);
			inline Mat2& Inverse(const Mat2& m);

			inline Mat2& Transpose(void);

			inline Mat2& SetRotation(float32 a);

			inline float32 GetRotation(void);

			inline Mat2& Rotate(float32 a);

			inline float32 operator [] (int32 i) const;

			inline float32& operator [] (int32 i);

			inline Mat2 operator *(const Mat2& m);
			inline void operator *=(const Mat2& m);

			inline void operator *=(float32 s);
			inline void operator /=(float32 s);

			inline Mat2& operator =(const Mat2& m);
			inline Mat2& operator =(const Mat2 && m);

			inline bool operator ==(const Mat2& m);
			inline bool operator !=(const Mat2& m);

			inline std::string ToString(int32 p = 5);
	};
}

#endif