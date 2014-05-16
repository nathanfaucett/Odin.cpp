#ifndef ODIN_MAT4_H
#define ODIN_MAT4_H

namespace Odin {

	template <typename Type> class Mat4 {

		private:
			template<typename Type2>friend inline Mat4<Type2>& Mat4Inverse(const Mat4<Type2>& a, Mat4<Type2>& out);
			template<typename Type2>friend inline Mat3<Type2>& Mat3InverseMat4(const Mat4<Type2>& a, Mat3<Type2>& out);
			template<typename Type2>friend inline Mat4<Type2>& Mat4Mul(const Mat4<Type2>& a, const Mat4<Type2>& b, Mat4<Type2>& out);
			friend class Mat3<Type>;
			friend class Mat43<Type>;
			Type m_mat[16];
			
			Vec3<Type> m_LookAt_x, m_LookAt_y, m_LookAt_z;

		public:

			inline explicit Mat4(void);
			inline explicit Mat4(
			    Type m11, Type m21, Type m31, Type m41,
			    Type m12, Type m22, Type m32, Type m42,
			    Type m13, Type m23, Type m33, Type m43,
			    Type m14, Type m24, Type m34, Type m44
			);
			inline Mat4(const Mat4<Type>& m);
			inline Mat4(const Mat4<Type>&& m);
			inline ~Mat4(void);
			
			inline const Type* GetArray(void) const {
				return m_mat;
			}

			inline Mat4<Type>& Identity(void);
			inline Mat4<Type>& SetTrace(Type x, Type y, Type z, Type w);

			inline Mat4<Type>& operator -(void);
			inline Mat4<Type>& Inverse(void);
			inline Mat4<Type>& Inverse(const Mat4<Type>& m);

			inline Mat4<Type>& Transpose(void);

			inline Mat4<Type>& Compose(const Vec3<Type>& position, const Vec3<Type>& scale, const Quat<Type>& rotation);
			inline Mat4<Type>& Compose(const Vec3<Type>& position, const Quat<Type>& rotation);
			inline Mat4<Type>& Decompose(Vec3<Type>& position, Vec3<Type>& scale, Quat<Type>& rotation);

			inline Mat4<Type>& SetPosition(const Vec3<Type>& v);
			inline Vec3<Type> GetPosition(void);
			inline Vec3<Type>& GetPosition(Vec3<Type>& v);

			inline Mat4<Type>& ExtractPosition(const Mat4<Type>& m);
			inline Mat4<Type>& ExtractRotation(const Mat4<Type>& m);
			inline Mat4<Type>& ExtractRotationWithScale(const Mat4<Type>& m);

			inline Mat4<Type>& Scale(const Vec2<Type>& v);
			inline Mat4<Type>& Scale(const Vec3<Type>& v);
			inline Mat4<Type>& Scale(const Vec4<Type>& v);

			inline Mat4<Type>& RotateX(Type angle);
			inline Mat4<Type>& RotateY(Type angle);
			inline Mat4<Type>& RotateZ(Type angle);
			inline Mat4<Type>& Rotate(Type x, Type y, Type z);
			
			inline Mat4<Type>& LookAt(Vec3<Type>& eye, Vec3<Type>& target, Vec3<Type>& up = Vec3<Type>::Up);

			inline Mat4<Type>& FromQuat(const Quat<Type>& q);

			inline static Mat4<Type> MakeTranslation(Type x, Type y, Type z) {

				return Mat4(
				           1, static_cast<Type>(0), static_cast<Type>(0), x,
				           static_cast<Type>(0), static_cast<Type>(1), static_cast<Type>(0), y,
				           static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1), z,
				           static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1)
				       );
			}

			inline static Mat4<Type> MakeScale(Type x, Type y, Type z) {

				return Mat4(
				           x, static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0),
				           static_cast<Type>(0), y, static_cast<Type>(0), static_cast<Type>(0),
				           static_cast<Type>(0), static_cast<Type>(0), z, static_cast<Type>(0),
				           static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1)
				       );
			}

			inline static Mat4<Type> MakeRotationX(Type angle) {
				Type c = Mathf.Cos(angle),
				     s = Mathf.Sin(angle);

				return Mat4(
				           1, static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0),
				           static_cast<Type>(0), c, -s, static_cast<Type>(0),
				           static_cast<Type>(0), s, c, static_cast<Type>(0),
				           static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1)
				       );
			}

			inline static Mat4<Type> MakeRotationY(Type angle) {
				Type c = Mathf.Cos(angle),
				     s = Mathf.Sin(angle);

				return Mat4(
				           c, static_cast<Type>(0), s, static_cast<Type>(0),
				           static_cast<Type>(0), static_cast<Type>(1), static_cast<Type>(0), static_cast<Type>(0),
				           -s, static_cast<Type>(0), c, static_cast<Type>(0),
				           static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1)
				       );
			}

			inline static Mat4<Type> MakeRotationZ(Type angle) {
				Type c = Mathf.Cos(angle),
				     s = Mathf.Sin(angle);

				return Mat4(
				           c, -s, static_cast<Type>(0), static_cast<Type>(0),
				           s, c, static_cast<Type>(0), static_cast<Type>(0),
				           static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1), static_cast<Type>(0),
				           static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1)
				       );
			}

			inline static Mat4<Type> MakeFrustum(Type left, Type right, Type top, Type bottom, Type near, Type far) {
				Mat4<Type> m;

				return m.Frustum(left, right, top, bottom, near, far);
			}

			inline static Mat4<Type> MakePerspective(Type fov, Type aspect, Type near, Type far) {
				Mat4<Type> m;

				return m.Perspective(fov, aspect, near, far);
			}

			inline static Mat4<Type> MakeOrthographic(Type left, Type right, Type top, Type bottom, Type near, Type far) {
				Mat4<Type> m;

				return m.Orthographic(left, right, top, bottom, near, far);
			}

			inline Mat4<Type>& Frustum(Type left, Type right, Type top, Type bottom, Type near, Type far);
			inline Mat4<Type>& Perspective(Type fov, Type aspect, Type near, Type far);
			inline Mat4<Type>& Orthographic(Type left, Type right, Type top, Type bottom, Type near, Type far);

			inline Type operator [] (int32 i) const;
			inline Type& operator [] (int32 i);

			inline Mat4<Type> operator *(const Vec2<Type>& v);
			inline Mat4<Type>& operator +=(const Vec2<Type>& v);

			inline Mat4<Type> operator *(const Vec3<Type>& v);
			inline Mat4<Type>& operator *=(const Vec3<Type>& v);

			inline Mat4<Type> operator *(const Vec4<Type>& v);
			inline Mat4<Type>& operator *=(const Vec4<Type>& v);

			inline Mat4<Type> operator *(const Mat4<Type>& m);
			inline Mat4<Type>& operator *=(const Mat4<Type>& m);

			inline Mat4<Type> operator *(const Mat43<Type>& m);
			inline Mat4<Type>& operator *=(const Mat43<Type>& m);

			inline Mat4<Type>& operator *=(Type s);
			inline Mat4<Type>& operator /=(Type s);

			inline Mat4<Type>& operator =(const Mat4<Type>& m);
			inline Mat4<Type>& operator =(const Mat4<Type> && m);

			inline bool operator ==(const Mat4<Type>& m);
			inline bool operator !=(const Mat4<Type>& m);

			inline std::string ToString(int32 p = 6);
	};
}

#endif