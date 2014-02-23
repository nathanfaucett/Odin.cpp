#ifndef ODIN_MAT2_H
#define ODIN_MAT2_H

namespace Odin {

	struct Mat2 {

		private:
			float mat[4];

		public:

			inline explicit Mat2(void);
			inline explicit Mat2(const float m11, const float m12, const float m21, const float m22);
			inline Mat2(const Mat2& m);
			inline ~Mat2(void);

			inline Mat2& Identity(void);
			inline Mat2& SetTrace(const float x, const float y);

			inline Mat2& operator -();
			inline Mat2& Inverse(void);
			inline Mat2& Inverse(const Mat2& m);

			inline Mat2& SetRotation(const float a);

			inline float GetRotation(void);

			inline Mat2& Rotate(const float a);

			inline const float operator [] (int i) const;

			inline float& operator [] (int i);

			inline Mat2 operator *(const Mat2& m);
			inline void operator *=(const Mat2& m);

			inline Mat2 operator *=(const float s);
			inline Mat2 operator /=(const float s);

			inline bool operator ==(const Mat2& m);
			inline bool operator !=(const Mat2& m);

			inline std::string ToString(int p = 5);
	};
}

#endif