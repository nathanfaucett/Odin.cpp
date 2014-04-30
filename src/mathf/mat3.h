#ifndef ODIN_MAT3_H
#define ODIN_MAT3_H

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

			inline Mat3<Type>& RotateX(Type angle);
			inline Mat3<Type>& RotateY(Type angle);
			inline Mat3<Type>& RotateZ(Type angle);
			inline Mat3<Type>& Rotate(Type x, Type y, Type z);

			inline static Mat3<Type> MakeScale(Type x, Type y, Type z) {

				return Mat3(
				           x, static_cast<Type>(0), static_cast<Type>(0),
				           static_cast<Type>(0), y, static_cast<Type>(0),
				           static_cast<Type>(0), static_cast<Type>(0), z
				       );
			}

			inline static Mat3<Type> MakeRotationX(Type angle) {
				Type c = Mathf.Cos(angle),
				     s = Mathf.Sin(angle);

				return Mat3(
				           static_cast<Type>(1), static_cast<Type>(0), static_cast<Type>(0),
				           static_cast<Type>(0), c, -s,
				           static_cast<Type>(0), s, c
				       );
			}

			inline static Mat3<Type> MakeRotationY(Type angle) {
				Type c = Mathf.Cos(angle),
				     s = Mathf.Sin(angle);

				return Mat3(
				           c, static_cast<Type>(0), s,
				           static_cast<Type>(0), static_cast<Type>(1), static_cast<Type>(0),
				           -s, static_cast<Type>(0), c
				       );
			}

			inline static Mat3<Type> MakeRotationZ(Type angle) {
				Type c = Mathf.Cos(angle),
				     s = Mathf.Sin(angle);

				return Mat3(
				           c, -s, static_cast<Type>(0),
				           s, c, static_cast<Type>(0),
				           static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1)
				       );
			}

			inline Type operator [] (int32 i) const;
			inline Type& operator [] (int32 i);

			inline Mat3<Type> operator *(const Mat3<Type>& m);
			inline Mat3<Type>& operator *=(const Mat3<Type>& m);

			inline Mat3<Type>& operator *=(Type s);
			inline Mat3<Type>& operator /=(Type s);

			inline Mat3<Type>& operator =(const Mat3<Type>& m);
			inline Mat3<Type>& operator =(const Mat3<Type> && m);

			inline bool operator ==(const Mat3<Type>& m);
			inline bool operator !=(const Mat3<Type>& m);

			inline std::string ToString(int32 p = 6);
	};
}

#endif