#ifndef _ODIN_MAT3_H_
#define _ODIN_MAT3_H_

namespace Odin {

	template <typename Type> class Mat3 {

		private:
			template<typename Type2>friend inline Mat3<Type2>& Mat3Inverse(const Mat3<Type2>& a, Mat3<Type2>& out);
			template<typename Type2>friend inline Mat3<Type2>& Mat3InverseMat4(const Mat4<Type2>& a, Mat3<Type2>& out);
			template<typename Type2>friend inline Mat3<Type2>& Mat3Mul(const Mat3<Type2>& a, const Mat3<Type2>& b, Mat3<Type2>& out);
			friend class Mat4<Type>;
			Type m_mat[9];

		public:

			inline explicit Mat3(void);
			inline explicit Mat3(
			    Type m11, Type m21, Type m31,
			    Type m12, Type m22, Type m32,
			    Type m13, Type m23, Type m33
			);
			inline Mat3(const Mat3<Type>& m);
			inline Mat3(const Mat3<Type>&& m);

			inline ~Mat3(void);

			inline Mat3<Type>& Identity(void);
			inline Mat3<Type>& SetTrace(Type x, Type y, Type z);

			inline Mat3<Type>& operator -();
			inline Mat3<Type>& Inverse(void);
			inline Mat3<Type>& Inverse(const Mat3<Type>& m);
			inline Mat3<Type>& Inverse(const Mat4<Type>& m);

			inline Mat3<Type>& Transpose(void);

			inline Mat3<Type>& ExtractRotation(const Mat3<Type>& m);
			inline Mat3<Type>& ExtractRotation(const Mat4<Type>& m);
			inline Mat3<Type>& ExtractRotationWithScale(const Mat4<Type>& m);

			inline Mat3<Type>& Scale(const Vec2<Type>& v);
			inline Mat3<Type>& Scale(const Vec3<Type>& v);
			inline Mat3<Type>& Scale(const Vec4<Type>& v);
			inline Mat3<Type>& FromQuat(const Quat<Type>& q);

			inline static Mat3<Type> MakeScale(Type x, Type y, Type z) {

				return Mat3(
				           x, 0, 0,
				           0, y, 0,
				           0, 0, z
				       );
			}

			inline static Mat3<Type> MakeRotationX(Type angle) {
				Type c = Mathf.Cos(angle),
				     s = Mathf.Sin(angle);

				return Mat3(
				           1, 0, 0,
				           0, c, -s,
				           0, s, c
				       );
			}

			inline static Mat3<Type> MakeRotationY(Type angle) {
				Type c = Mathf.Cos(angle),
				     s = Mathf.Sin(angle);

				return Mat3(
				           c, 0, s,
				           0, 1, 0,
				           -s, 0, c
				       );
			}

			inline static Mat3<Type> MakeRotationZ(Type angle) {
				Type c = Mathf.Cos(angle),
				     s = Mathf.Sin(angle);

				return Mat3(
				           c, -s, 0,
				           s, c, 0,
				           0, 0, 1
				       );
			}

			inline Type operator [] (int32 i) const;
			inline Type& operator [] (int32 i);

			inline Mat3<Type> operator *(const Mat3<Type>& m);
			inline void operator *=(const Mat3<Type>& m);

			inline void operator *=(Type s);
			inline void operator /=(Type s);

			inline Mat3<Type>& operator =(const Mat3<Type>& m);
			inline Mat3<Type>& operator =(const Mat3<Type> && m);

			inline bool operator ==(const Mat3<Type>& m);
			inline bool operator !=(const Mat3<Type>& m);

			inline std::string ToString(int32 p = 5);
	};
}

#endif