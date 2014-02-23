#ifndef ODIN_MAT3_H
#define ODIN_MAT3_H

namespace Odin {

	struct Mat3 {

		private:
			float mat[9];

		public:

			inline explicit Mat3(void);
			inline explicit Mat3(
			    const float m11, const float m21, const float m31,
			    const float m12, const float m22, const float m32,
			    const float m13, const float m23, const float m33
			);
			inline Mat3(const Mat3& m);

			inline ~Mat3(void);

			inline Mat3& Identity(void);
			inline Mat3& SetTrace(const float x, const float y, const float z);

			inline Mat3& operator -();
			inline Mat3& Inverse(void);
			inline Mat3& Inverse(const Mat3& m);
			inline Mat3& Inverse(const Mat4& m);

			inline Mat3& ExtractRotation(const Mat3& m);
			inline Mat3& ExtractRotation(const Mat4& m);
			inline Mat3& ExtractRotationWithScale(const Mat4& m);

			inline Mat3& Scale(const Vec2& v);
			inline Mat3& Scale(const Vec3& v);
			inline Mat3& Scale(const Vec4& v);
			inline Mat3& FromQuat(const Quat& q);

			inline static Mat3 MakeScale(const float x, const float y, const float z) {

				return Mat3(
				           x, 0.0f, 0.0f,
				           0.0f, y, 0.0f,
				           0.0f, 0.0f, z
				       );
			}

			inline static Mat3 MakeRotationX(const float angle) {
				float c = cosf(angle),
				      s = sinf(angle);

				return Mat3(
				           1, 0.0f, 0.0f,
				           0.0f, c, -s,
				           0.0f, s, c
				       );
			}

			inline static Mat3 MakeRotationY(const float angle) {
				float c = cosf(angle),
				      s = sinf(angle);

				return Mat3(
				           c, 0.0f, s,
				           0.0f, 1.0f, 0.0f,
				           -s, 0.0f, c
				       );
			}

			inline static Mat3 MakeRotationZ(const float angle) {
				float c = cosf(angle),
				      s = sinf(angle);

				return Mat3(
				           c, -s, 0.0f,
				           s, c, 0.0f,
				           0.0f, 0.0f, 1.0f
				       );
			}

			inline const float operator [] (int i) const;
			inline float& operator [] (int i);

			inline Mat3 operator *(const Mat3& m);
			inline void operator *=(const Mat3& m);

			inline Mat3 operator *=(const float s);
			inline Mat3 operator /=(const float s);

			inline bool operator ==(const Mat3& m);
			inline bool operator !=(const Mat3& m);

			inline std::string ToString(int p = 5);
	};
}

#endif