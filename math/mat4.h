#ifndef ODIN_MAT4_H
#define ODIN_MAT4_H

namespace Odin {

	struct Mat4 {

		private:
			friend struct Quat;
			friend struct Mat3;
			float mat[16];

		public:

			inline Mat4(void);
			inline Mat4(
			    const float m11, const float m21, const float m31, const float m41,
			    const float m12, const float m22, const float m32, const float m42,
			    const float m13, const float m23, const float m33, const float m43,
			    const float m14, const float m24, const float m34, const float m44
			);
			inline Mat4(const Mat4& m);
			inline ~Mat4(void);

			inline Mat4& Identity();
			inline Mat4& SetTrace(const float x, const float y, const float z, const float w);

			inline Mat4& operator -();
			inline Mat4& Inverse();
			inline Mat4& Inverse(const Mat4& m);

			inline Mat4& Compose(const Vec3& position, const Vec3& scale, const Quat& rotation);
			inline Mat4& Decompose(Vec3& position, Vec3& scale, Quat& rotation);

			inline Mat4& SetPosition(const Vec3& v);
			inline Vec3 GetPosition();

			inline Mat4& ExtractPosition(const Mat4& m);
			inline Mat4& ExtractRotation(const Mat4& m);
			inline Mat4& ExtractRotationWithScale(const Mat4& m);

			inline Mat4& Scale(const Vec2& v);
			inline Mat4& Scale(const Vec3& v);
			inline Mat4& Scale(const Vec4& v);

			inline Mat4& RotateX(const float angle);
			inline Mat4& RotateY(const float angle);
			inline Mat4& RotateZ(const float angle);

			inline Mat4& FromQuat(const Quat& q);

			inline static Mat4 MakeTranslation(const float x, const float y, const float z) {
		
				return Mat4(
						   1, 0, 0, x,
						   0, 1, 0, y,
						   0, 0, 1, z,
						   0, 0, 0, 1
					   );
			}
		
			inline static Mat4 MakeScale(const float x, const float y, const float z) {
		
				return Mat4(
						   x, 0, 0, 0,
						   0, y, 0, 0,
						   0, 0, z, 0,
						   0, 0, 0, 1
					   );
			}
		
			inline static Mat4 MakeRotationX(const float angle) {
				float c = std::cos(angle),
					  s = std::sin(angle);
		
				return Mat4(
						   1, 0, 0, 0,
						   0, c, -s, 0,
						   0, s, c, 0,
						   0, 0, 0, 1
					   );
			}
		
			inline static Mat4 MakeRotationY(const float angle) {
				float c = std::cos(angle),
					  s = std::sin(angle);
		
				return Mat4(
						   c, 0, s, 0,
						   0, 1, 0, 0,
						   -s, 0, c, 0,
						   0, 0, 0, 1
					   );
			}
		
			inline static Mat4 MakeRotationZ(const float angle) {
				float c = std::cos(angle),
					  s = std::sin(angle);
		
				return Mat4(
						   c, -s, 0, 0,
						   s, c, 0, 0,
						   0, 0, 1, 0,
						   0, 0, 0, 1
					   );
			}
		
			inline static Mat4 MakeFrustum(const float left, const float right, const float top, const float bottom, const float near, const float far) {
				Mat4 m;
		
				return m.Frustum(left, right, top, bottom, near, far);
			}
		
			inline static Mat4 MakePerspective(const float fov, const float aspect, const float near, const float far) {
				Mat4 m;
		
				return m.Perspective(fov, aspect, near, far);
			}
		
			inline static Mat4 MakeOrthographic(const float left, const float right, const float top, const float bottom, const float near, const float far) {
				Mat4 m;
		
				return m.Orthographic(left, right, top, bottom, near, far);
			}
			
			inline Mat4& Frustum(const float left, const float right, const float top, const float bottom, const float near, const float far);
			inline Mat4& Perspective(const float fov, const float aspect, const float near, const float far);
			inline Mat4& Orthographic(const float left, const float right, const float top, const float bottom, const float near, const float far);

			inline const float operator [] (int i) const;

			inline float& operator [] (int i);

			inline Mat4 operator *(const Vec2& v);
			inline Mat4& operator +=(const Vec2& v);

			inline Mat4 operator *(const Vec3& v);
			inline Mat4& operator *=(const Vec3& v);

			inline Mat4 operator *(const Vec4& v);
			inline Mat4& operator *=(const Vec4& v);

			inline Mat4 operator *(const Mat4& m);
			inline void operator *=(const Mat4& m);

			inline Mat4 operator *=(const float s);
			inline Mat4 operator /=(const float s);

			inline Mat4 operator =(const Mat4& m);
			inline bool operator ==(const Mat4& m);
			inline bool operator !=(const Mat4& m);

			inline std::string ToString(int p = 5);
	};
}

#endif