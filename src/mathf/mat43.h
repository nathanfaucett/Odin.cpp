#ifndef ODIN_MAT43_H
#define ODIN_MAT43_H

namespace Odin {

	template <typename Type> class Mat43 {

		private:
			template<typename Type2>friend inline Mat43<Type2>& Mat43Inverse(const Mat43<Type2>& a, Mat43<Type2>& out);
			template<typename Type2>friend inline Mat3<Type2>& Mat3InverseMat43(const Mat43<Type2>& a, Mat3<Type2>& out);
			template<typename Type2>friend inline Mat43<Type2>& Mat43Mul(const Mat43<Type2>& a, const Mat43<Type2>& b, Mat43<Type2>& out);
			friend class Mat3<Type>;
			friend class Mat4<Type>;
			Type m_mat[12];
			
			Vec3<Type> m_LookAt_x, m_LookAt_y, m_LookAt_z;

		public:

			inline explicit Mat43(void);
			inline explicit Mat43(
			    Type m11, Type m21, Type m31, Type m41,
			    Type m12, Type m22, Type m32, Type m42,
			    Type m13, Type m23, Type m33, Type m43
			);
			inline Mat43(const Mat43<Type>& m);
			inline Mat43(const Mat43<Type>&& m);
			inline ~Mat43(void);
			
			inline const Type* GetArray(void) const {
				return m_mat;
			}

			inline Mat43<Type>& Identity(void);
			inline Mat43<Type>& SetTrace(Type x, Type y, Type z);

			inline Mat43<Type>& operator -(void);
			inline Mat43<Type>& Inverse(void);
			inline Mat43<Type>& Inverse(const Mat4<Type>& m);
			inline Mat43<Type>& Inverse(const Mat43<Type>& m);

			inline Mat43<Type>& Transpose(void);

			inline Mat43<Type>& Compose(const Vec3<Type>& position, const Vec3<Type>& scale, const Quat<Type>& rotation);
			inline Mat43<Type>& Compose(const Vec3<Type>& position, const Quat<Type>& rotation);
			inline Mat43<Type>& Decompose(Vec3<Type>& position, Vec3<Type>& scale, Quat<Type>& rotation);

			inline Mat43<Type>& SetPosition(const Vec3<Type>& v);
			inline Vec3<Type> GetPosition(void);
			inline Vec3<Type>& GetPosition(Vec3<Type>& v);

			inline Mat43<Type>& ExtractPosition(const Mat43<Type>& m);
			inline Mat43<Type>& ExtractRotation(const Mat43<Type>& m);
			inline Mat43<Type>& ExtractRotationWithScale(const Mat43<Type>& m);

			inline Mat43<Type>& Scale(const Vec2<Type>& v);
			inline Mat43<Type>& Scale(const Vec3<Type>& v);
			inline Mat43<Type>& Scale(const Vec4<Type>& v);

			inline Mat43<Type>& RotateX(Type angle);
			inline Mat43<Type>& RotateY(Type angle);
			inline Mat43<Type>& RotateZ(Type angle);
			inline Mat43<Type>& Rotate(Type x, Type y, Type z);
			
			inline Mat43<Type>& LookAt(Vec3<Type>& eye, Vec3<Type>& target, Vec3<Type>& up = Vec3<Type>::Up);

			inline Mat43<Type>& FromQuat(const Quat<Type>& q);

			inline static Mat43<Type> MakeTranslation(Type x, Type y, Type z) {

				return Mat43(
				           1, static_cast<Type>(0), static_cast<Type>(0), x,
				           static_cast<Type>(0), static_cast<Type>(1), static_cast<Type>(0), y,
				           static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1), z
				       );
			}

			inline static Mat43<Type> MakeScale(Type x, Type y, Type z) {

				return Mat43(
				           x, static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0),
				           static_cast<Type>(0), y, static_cast<Type>(0), static_cast<Type>(0),
				           static_cast<Type>(0), static_cast<Type>(0), z, static_cast<Type>(0)
				       );
			}

			inline static Mat43<Type> MakeRotationX(Type angle) {
				Type c = Mathf.Cos(angle),
				     s = Mathf.Sin(angle);

				return Mat43(
				           1, static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0),
				           static_cast<Type>(0), c, -s, static_cast<Type>(0),
				           static_cast<Type>(0), s, c, static_cast<Type>(0)
				       );
			}

			inline static Mat43<Type> MakeRotationY(Type angle) {
				Type c = Mathf.Cos(angle),
				     s = Mathf.Sin(angle);

				return Mat43(
				           c, static_cast<Type>(0), s, static_cast<Type>(0),
				           static_cast<Type>(0), static_cast<Type>(1), static_cast<Type>(0), static_cast<Type>(0),
				           -s, static_cast<Type>(0), c, static_cast<Type>(0)
				       );
			}

			inline static Mat43<Type> MakeRotationZ(Type angle) {
				Type c = Mathf.Cos(angle),
				     s = Mathf.Sin(angle);

				return Mat43(
				           c, -s, static_cast<Type>(0), static_cast<Type>(0),
				           s, c, static_cast<Type>(0), static_cast<Type>(0),
				           static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1), static_cast<Type>(0)
				       );
			}

			inline static Mat43<Type> MakeFrustum(Type left, Type right, Type top, Type bottom, Type near, Type far) {
				Mat43<Type> m;

				return m.Frustum(left, right, top, bottom, near, far);
			}

			inline static Mat43<Type> MakePerspective(Type fov, Type aspect, Type near, Type far) {
				Mat43<Type> m;

				return m.Perspective(fov, aspect, near, far);
			}

			inline static Mat43<Type> MakeOrthographic(Type left, Type right, Type top, Type bottom, Type near, Type far) {
				Mat43<Type> m;

				return m.Orthographic(left, right, top, bottom, near, far);
			}

			inline Mat43<Type>& Frustum(Type left, Type right, Type top, Type bottom, Type near, Type far);
			inline Mat43<Type>& Perspective(Type fov, Type aspect, Type near, Type far);
			inline Mat43<Type>& Orthographic(Type left, Type right, Type top, Type bottom, Type near, Type far);

			inline Type operator [] (int32 i) const;
			inline Type& operator [] (int32 i);

			inline Mat43<Type> operator *(const Vec2<Type>& v);
			inline Mat43<Type>& operator +=(const Vec2<Type>& v);

			inline Mat43<Type> operator *(const Vec3<Type>& v);
			inline Mat43<Type>& operator *=(const Vec3<Type>& v);

			inline Mat43<Type> operator *(const Vec4<Type>& v);
			inline Mat43<Type>& operator *=(const Vec4<Type>& v);

			inline Mat43<Type> operator *(const Mat43<Type>& m);
			inline Mat43<Type>& operator *=(const Mat43<Type>& m);

			inline Mat43<Type> operator *(const Mat4<Type>& m);
			inline Mat43<Type>& operator *=(const Mat4<Type>& m);

			inline Mat43<Type>& operator *=(Type s);
			inline Mat43<Type>& operator /=(Type s);

			inline Mat43<Type>& operator =(const Mat43<Type>& m);
			inline Mat43<Type>& operator =(const Mat43<Type> && m);

			inline bool operator ==(const Mat43<Type>& m);
			inline bool operator !=(const Mat43<Type>& m);

			inline std::string ToString(int32 p = 6);
	};
}

#endif