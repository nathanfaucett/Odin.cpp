#ifndef _ODIN_MAT4_H
#define _ODIN_MAT4_H

namespace Odin {

	class Mat4 {

		private:
			friend inline Mat4& Mat4Inverse(const Mat4& a, Mat4& out);
			friend inline Mat3& Mat3InverseMat4(const Mat4& a, Mat3& out);
			friend inline Mat4& Mat4Mul(const Mat4& a, const Mat4& b, Mat4& out);
			friend class Mat3;
			float32 m_mat[16];

		public:

			inline explicit Mat4(void);
			inline explicit Mat4(
			    float32 m11, float32 m21, float32 m31, float32 m41,
			    float32 m12, float32 m22, float32 m32, float32 m42,
			    float32 m13, float32 m23, float32 m33, float32 m43,
			    float32 m14, float32 m24, float32 m34, float32 m44
			);
			inline Mat4(const Mat4& m);
			inline Mat4(const Mat4&& m);
			inline ~Mat4(void);

			inline Mat4& Identity(void);
			inline Mat4& SetTrace(float32 x, float32 y, float32 z, float32 w);

			inline Mat4& operator -();
			inline Mat4& Inverse(void);
			inline Mat4& Inverse(const Mat4& m);

			inline Mat4& Transpose(void);

			inline Mat4& Compose(const Vec3& position, const Vec3& scale, const Quat& rotation);
			inline Mat4& Decompose(Vec3& position, Vec3& scale, Quat& rotation);

			inline Mat4& SetPosition(const Vec3& v);
			inline Vec3 GetPosition(void);

			inline Mat4& ExtractPosition(const Mat4& m);
			inline Mat4& ExtractRotation(const Mat4& m);
			inline Mat4& ExtractRotationWithScale(const Mat4& m);

			inline Mat4& Scale(const Vec2& v);
			inline Mat4& Scale(const Vec3& v);
			inline Mat4& Scale(const Vec4& v);

			inline Mat4& RotateX(float32 angle);
			inline Mat4& RotateY(float32 angle);
			inline Mat4& RotateZ(float32 angle);

			inline Mat4& FromQuat(const Quat& q);

			inline static Mat4 MakeTranslation(float32 x, float32 y, float32 z) {

				return Mat4(
				           1.0f, 0.0f, 0.0f, x,
				           0.0f, 1.0f, 0.0f, y,
				           0.0f, 0.0f, 1.0f, z,
				           0.0f, 0.0f, 0.0f, 1.0f
				       );
			}

			inline static Mat4 MakeScale(float32 x, float32 y, float32 z) {

				return Mat4(
				           x, 0.0f, 0.0f, 0.0f,
				           0.0f, y, 0.0f, 0.0f,
				           0.0f, 0.0f, z, 0.0f,
				           0.0f, 0.0f, 0.0f, 1.0f
				       );
			}

			inline static Mat4 MakeRotationX(float32 angle) {
				float32 c = cosf(angle),
				        s = sinf(angle);

				return Mat4(
				           1.0f, 0.0f, 0.0f, 0.0f,
				           0.0f, c, -s, 0.0f,
				           0.0f, s, c, 0.0f,
				           0.0f, 0.0f, 0.0f, 1.0f
				       );
			}

			inline static Mat4 MakeRotationY(float32 angle) {
				float32 c = cosf(angle),
				        s = sinf(angle);

				return Mat4(
				           c, 0.0f, s, 0.0f,
				           0.0f, 1.0f, 0.0f, 0.0f,
				           -s, 0.0f, c, 0.0f,
				           0.0f, 0.0f, 0.0f, 1.0f
				       );
			}

			inline static Mat4 MakeRotationZ(float32 angle) {
				float32 c = cosf(angle),
				        s = sinf(angle);

				return Mat4(
				           c, -s, 0.0f, 0.0f,
				           s, c, 0.0f, 0.0f,
				           0.0f, 0.0f, 1.0f, 0.0f,
				           0.0f, 0.0f, 0.0f, 1.0f
				       );
			}

			inline static Mat4 MakeFrustum(float32 left, float32 right, float32 top, float32 bottom, float32 near, float32 far) {
				Mat4 m;

				return m.Frustum(left, right, top, bottom, near, far);
			}

			inline static Mat4 MakePerspective(float32 fov, float32 aspect, float32 near, float32 far) {
				Mat4 m;

				return m.Perspective(fov, aspect, near, far);
			}

			inline static Mat4 MakeOrthographic(float32 left, float32 right, float32 top, float32 bottom, float32 near, float32 far) {
				Mat4 m;

				return m.Orthographic(left, right, top, bottom, near, far);
			}

			inline Mat4& Frustum(float32 left, float32 right, float32 top, float32 bottom, float32 near, float32 far);
			inline Mat4& Perspective(float32 fov, float32 aspect, float32 near, float32 far);
			inline Mat4& Orthographic(float32 left, float32 right, float32 top, float32 bottom, float32 near, float32 far);

			inline float32 operator [] (int32 i) const;

			inline float32& operator [] (int32 i);

			inline Mat4 operator *(const Vec2& v);
			inline Mat4& operator +=(const Vec2& v);

			inline Mat4 operator *(const Vec3& v);
			inline void operator *=(const Vec3& v);

			inline Mat4 operator *(const Vec4& v);
			inline void operator *=(const Vec4& v);

			inline Mat4 operator *(const Mat4& m);
			inline void operator *=(const Mat4& m);

			inline void operator *=(float32 s);
			inline void operator /=(float32 s);

			inline Mat4& operator =(const Mat4& m);
			inline Mat4& operator =(const Mat4 && m);

			inline bool operator ==(const Mat4& m);
			inline bool operator !=(const Mat4& m);

			inline std::string ToString(int32 p = 5);
	};
}

#endif