#ifndef _ODIN_MAT3_H
#define _ODIN_MAT3_H

namespace Odin {

	class Mat3 {

		private:
			friend inline Mat3& Mat3Inverse(const Mat3& a, Mat3& out);
			friend inline Mat3& Mat3InverseMat4(const Mat4& a, Mat3& out);
			friend inline Mat3& Mat3Mul(const Mat3& a, const Mat3& b, Mat3& out);
			friend class Mat4;
			float32 m_mat[9];

		public:

			inline explicit Mat3(void);
			inline explicit Mat3(
			    float32 m11, float32 m21, float32 m31,
			    float32 m12, float32 m22, float32 m32,
			    float32 m13, float32 m23, float32 m33
			);
			inline Mat3(const Mat3& m);
			inline Mat3(const Mat3&& m);

			inline ~Mat3(void);

			inline Mat3& Identity(void);
			inline Mat3& SetTrace(float32 x, float32 y, float32 z);

			inline Mat3& operator -();
			inline Mat3& Inverse(void);
			inline Mat3& Inverse(const Mat3& m);
			inline Mat3& Inverse(const Mat4& m);

			inline Mat3& Transpose(void);

			inline Mat3& ExtractRotation(const Mat3& m);
			inline Mat3& ExtractRotation(const Mat4& m);
			inline Mat3& ExtractRotationWithScale(const Mat4& m);

			inline Mat3& Scale(const Vec2& v);
			inline Mat3& Scale(const Vec3& v);
			inline Mat3& Scale(const Vec4& v);
			inline Mat3& FromQuat(const Quat& q);

			inline static Mat3 MakeScale(float32 x, float32 y, float32 z) {

				return Mat3(
				           x, 0.0f, 0.0f,
				           0.0f, y, 0.0f,
				           0.0f, 0.0f, z
				       );
			}

			inline static Mat3 MakeRotationX(float32 angle) {
				float32 c = cosf(angle),
				        s = sinf(angle);

				return Mat3(
				           1, 0.0f, 0.0f,
				           0.0f, c, -s,
				           0.0f, s, c
				       );
			}

			inline static Mat3 MakeRotationY(float32 angle) {
				float32 c = cosf(angle),
				        s = sinf(angle);

				return Mat3(
				           c, 0.0f, s,
				           0.0f, 1.0f, 0.0f,
				           -s, 0.0f, c
				       );
			}

			inline static Mat3 MakeRotationZ(float32 angle) {
				float32 c = cosf(angle),
				        s = sinf(angle);

				return Mat3(
				           c, -s, 0.0f,
				           s, c, 0.0f,
				           0.0f, 0.0f, 1.0f
				       );
			}

			inline float32 operator [] (int32 i) const;
			inline float32& operator [] (int32 i);

			inline Mat3 operator *(const Mat3& m);
			inline void operator *=(const Mat3& m);

			inline void operator *=(float32 s);
			inline void operator /=(float32 s);

			inline Mat3& operator =(const Mat3& m);
			inline Mat3& operator =(const Mat3 && m);

			inline bool operator ==(const Mat3& m);
			inline bool operator !=(const Mat3& m);

			inline std::string ToString(int32 p = 5);
	};
}

#endif