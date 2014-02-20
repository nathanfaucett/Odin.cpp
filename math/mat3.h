#ifndef ODIN_MAT3_H
#define ODIN_MAT3_H

namespace Odin {

    struct Mat3 {

        private:
            float mat[9];

        public:

            inline Mat3(void) {
                mat[0] = 1;
                mat[3] = 0;
                mat[6] = 0;
                mat[1] = 0;
                mat[4] = 1;
                mat[7] = 0;
                mat[2] = 0;
                mat[5] = 0;
                mat[8] = 1;
            }

            inline Mat3(
                const float m11, const float m21, const float m31,
                const float m12, const float m22, const float m32,
                const float m13, const float m23, const float m33
            ) {
                mat[0] = m11;
                mat[3] = m21;
                mat[6] = m31;
                mat[1] = m12;
                mat[4] = m22;
                mat[7] = m32;
                mat[2] = m13;
                mat[5] = m23;
                mat[8] = m33;
            }

            inline Mat3(const Mat3& m) {
                mat[0] = m.mat[0];
                mat[3] = m.mat[3];
                mat[6] = m.mat[6];
                mat[1] = m.mat[1];
                mat[4] = m.mat[4];
                mat[7] = m.mat[7];
                mat[2] = m.mat[2];
                mat[5] = m.mat[5];
                mat[8] = m.mat[8];
            }

            inline ~Mat3(void) {}

            inline Mat3& Identity() {
                mat[0] = 1;
                mat[3] = 0;
                mat[6] = 0;
                mat[1] = 0;
                mat[4] = 1;
                mat[7] = 0;
                mat[2] = 0;
                mat[5] = 0;
                mat[8] = 1;

                return *this;
            }

            inline Mat3& SetTrace(const float x, const float y, const float z, const float w) {
                mat[0] = x;
                mat[4] = y;
                mat[8] = z;

                return *this;
            }

            inline Mat3& operator -() {
                float m11 = mat[0], m12 = mat[3], m13 = mat[6],
                      m21 = mat[1], m22 = mat[4], m23 = mat[7],
                      m31 = mat[2], m32 = mat[5], m33 = mat[8],

                      m0 = m22 * m33 - m23 * m32,
                      m3 = m13 * m32 - m12 * m33,
                      m6 = m12 * m23 - m13 * m22,

                      det = m11 * m0 + m21 * m3 + m31 * m6;

                det = det != 0 ? 1 / det : 1;

                mat[0] = m0 * det;
                mat[1] = (m23 * m31 - m21 * m33) * det;
                mat[2] = (m21 * m32 - m22 * m31) * det;

                mat[3] = m3 * det;
                mat[4] = (m11 * m33 - m13 * m31) * det;
                mat[5] = (m12 * m31 - m11 * m32) * det;

                mat[6] = m6 * det;
                mat[7] = (m13 * m21 - m11 * m23) * det;
                mat[8] = (m11 * m22 - m12 * m21) * det;

                return *this;
            }

            inline Mat3& Inverse() {
                float m11 = mat[0], m12 = mat[3], m13 = mat[6],
                      m21 = mat[1], m22 = mat[4], m23 = mat[7],
                      m31 = mat[2], m32 = mat[5], m33 = mat[8],

                      m0 = m22 * m33 - m23 * m32,
                      m3 = m13 * m32 - m12 * m33,
                      m6 = m12 * m23 - m13 * m22,

                      det = m11 * m0 + m21 * m3 + m31 * m6;

                det = det != 0 ? 1 / det : 1;

                mat[0] = m0 * det;
                mat[1] = (m23 * m31 - m21 * m33) * det;
                mat[2] = (m21 * m32 - m22 * m31) * det;

                mat[3] = m3 * det;
                mat[4] = (m11 * m33 - m13 * m31) * det;
                mat[5] = (m12 * m31 - m11 * m32) * det;

                mat[6] = m6 * det;
                mat[7] = (m13 * m21 - m11 * m23) * det;
                mat[8] = (m11 * m22 - m12 * m21) * det;

                return *this;
            }

            inline Mat3& Inverse(const Mat3& m) {
                float m11 = m.mat[0], m12 = m.mat[3], m13 = m.mat[6],
                      m21 = m.mat[1], m22 = m.mat[4], m23 = m.mat[7],
                      m31 = m.mat[2], m32 =m. mat[5], m33 = m.mat[8],

                      m0 = m22 * m33 - m23 * m32,
                      m3 = m13 * m32 - m12 * m33,
                      m6 = m12 * m23 - m13 * m22,

                      det = m11 * m0 + m21 * m3 + m31 * m6;

                det = det != 0 ? 1 / det : 1;

                mat[0] = m0 * det;
                mat[1] = (m23 * m31 - m21 * m33) * det;
                mat[2] = (m21 * m32 - m22 * m31) * det;

                mat[3] = m3 * det;
                mat[4] = (m11 * m33 - m13 * m31) * det;
                mat[5] = (m12 * m31 - m11 * m32) * det;

                mat[6] = m6 * det;
                mat[7] = (m13 * m21 - m11 * m23) * det;
                mat[8] = (m11 * m22 - m12 * m21) * det;

                return *this;
            }

            inline Mat3& Inverse(const Mat4& m);

            inline Mat3& ExtractRotation(const Mat3& m) {
                Vec3 vec;
                float lx = Mathf.V3LengthSq(m.mat[0], m.mat[1], m.mat[2]),
                      ly = Mathf.V3LengthSq(m.mat[3], m.mat[4], m.mat[5]),
                      lz = Mathf.V3LengthSq(m.mat[6], m.mat[7], m.mat[8]),

                      scaleX = lx > 0 ? 1 / std::sqrt(lx) : 0,
                      scaleY = ly > 0 ? 1 / std::sqrt(ly) : 0,
                      scaleZ = lz > 0 ? 1 / std::sqrt(lz) : 0;

                mat[0] = m.mat[0] * scaleX;
                mat[1] = m.mat[1] * scaleX;
                mat[2] = m.mat[2] * scaleX;

                mat[3] = m.mat[3] * scaleY;
                mat[4] = m.mat[4] * scaleY;
                mat[5] = m.mat[5] * scaleY;

                mat[6] = m.mat[6] * scaleZ;
                mat[7] = m.mat[7] * scaleZ;
                mat[8] = m.mat[8] * scaleZ;

                return *this;
            }

            inline Mat3& ExtractRotation(const Mat4& m);

            inline Mat3& ExtractRotationWithScale(const Mat4& m);

            inline Mat3& Scale(const Vec2& v) {
                float x = v.x, y = v.y;

                mat[0] *= x;
                mat[3] *= y;
                mat[1] *= x;
                mat[4] *= y;
                mat[2] *= x;
                mat[5] *= y;

                return *this;
            }

            inline Mat3& Scale(const Vec3& v) {
                float x = v.x, y = v.y, z = v.z;

                mat[0] *= x;
                mat[3] *= y;
                mat[6] *= z;
                mat[1] *= x;
                mat[4] *= y;
                mat[7] *= z;
                mat[2] *= x;
                mat[5] *= y;
                mat[8] *= z;

                return *this;
            }

            inline Mat3& Scale(const Vec4& v) {
                float x = v.x, y = v.y, z = v.z;

                mat[0] *= x;
                mat[3] *= y;
                mat[6] *= z;
                mat[1] *= x;
                mat[4] *= y;
                mat[7] *= z;
                mat[2] *= x;
                mat[5] *= y;
                mat[8] *= z;

                return *this;
            }

            inline Mat3& FromQuat(const Quat& q) {
                float x = q.x,
                      y = q.y,
                      z = q.z,
                      w = q.w,
                      x2 = x + x,
                      y2 = y + y,
                      z2 = z + z,
                      xx = x * x2,
                      xy = x * y2,
                      xz = x * z2,
                      yy = y * y2,
                      yz = y * z2,
                      zz = z * z2,
                      wx = w * x2,
                      wy = w * y2,
                      wz = w * z2;

                mat[0] = 1 - (yy + zz);
                mat[3] = xy - wz;
                mat[6] = xz + wy;

                mat[1] = xy + wz;
                mat[4] = 1 - (xx + zz);
                mat[7] = yz - wx;

                mat[2] = xz - wy;
                mat[5] = yz + wx;
                mat[8] = 1 - (xx + yy);

                return *this;
            }

            inline static Mat3 MakeScale(const float x, const float y, const float z) {

                return Mat3(
                           x, 0, 0,
                           0, y, 0,
                           0, 0, z
                       );
            }

            inline static Mat3 MakeRotationX(const float angle) {
                float c = std::cos(angle),
                      s = std::sin(angle);

                return Mat3(
                           1, 0, 0,
                           0, c, -s,
                           0, s, c
                       );
            }

            inline static Mat3 MakeRotationY(const float angle) {
                float c = std::cos(angle),
                      s = std::sin(angle);

                return Mat3(
                           c, 0, s,
                           0, 1, 0,
                           -s, 0, c
                       );
            }

            inline static Mat3 MakeRotationZ(const float angle) {
                float c = std::cos(angle),
                      s = std::sin(angle);

                return Mat3(
                           c, -s, 0,
                           s, c, 0,
                           0, 0, 1
                       );
            }

            inline const float operator [] (int i) const {
                return mat[i];
            }

            inline float& operator [] (int i) {
                return mat[i];
            }

            inline Mat3 operator *(const Mat3& m) {
                float a11 = mat[0], a12 = mat[3], a13 = mat[6],
                      a21 = mat[1], a22 = mat[4], a23 = mat[7],
                      a31 = mat[2], a32 = mat[5], a33 = mat[8],

                      b11 = m.mat[0], b12 = m.mat[3], b13 = m.mat[6],
                      b21 = m.mat[1], b22 = m.mat[4], b23 = m.mat[7],
                      b31 = m.mat[2], b32 = m.mat[5], b33 = m.mat[8];

                return Mat3(
                           a11 * b11 + a21 * b12 + a31 * b13,
                           a12 * b11 + a22 * b12 + a32 * b13,
                           a13 * b11 + a23 * b12 + a33 * b13,

                           a11 * b21 + a21 * b22 + a31 * b23,
                           a12 * b21 + a22 * b22 + a32 * b23,
                           a13 * b21 + a23 * b22 + a33 * b23,

                           a11 * b31 + a21 * b32 + a31 * b33,
                           a12 * b31 + a22 * b32 + a32 * b33,
                           a13 * b31 + a23 * b32 + a33 * b33
                       );
            }

            inline void operator *=(const Mat3& m) {
                float a11 = mat[0], a12 = mat[3], a13 = mat[6],
                      a21 = mat[1], a22 = mat[4], a23 = mat[7],
                      a31 = mat[2], a32 = mat[5], a33 = mat[8],

                      b11 = m.mat[0], b12 = m.mat[3], b13 = m.mat[6],
                      b21 = m.mat[1], b22 = m.mat[4], b23 = m.mat[7],
                      b31 = m.mat[2], b32 = m.mat[5], b33 = m.mat[8];

                mat[0] = a11 * b11 + a21 * b12 + a31 * b13;
                mat[3] = a12 * b11 + a22 * b12 + a32 * b13;
                mat[6] = a13 * b11 + a23 * b12 + a33 * b13;

                mat[1] = a11 * b21 + a21 * b22 + a31 * b23;
                mat[4] = a12 * b21 + a22 * b22 + a32 * b23;
                mat[7] = a13 * b21 + a23 * b22 + a33 * b23;

                mat[2] = a11 * b31 + a21 * b32 + a31 * b33;
                mat[5] = a12 * b31 + a22 * b32 + a32 * b33;
                mat[8] = a13 * b31 + a23 * b32 + a33 * b33;
            }

            inline Mat3 operator *=(const float s) {
                mat[0] *= s;
                mat[1] *= s;
                mat[2] *= s;
                mat[3] *= s;
                mat[4] *= s;
                mat[5] *= s;
                mat[6] *= s;
                mat[7] *= s;
                mat[8] *= s;
            }

            inline Mat3 operator /=(const float s) {
                float d = s != 0 ? 1 / s : 0;

                mat[0] *= d;
                mat[1] *= d;
                mat[2] *= d;
                mat[3] *= d;
                mat[4] *= d;
                mat[5] *= d;
                mat[6] *= d;
                mat[7] *= d;
                mat[8] *= d;
            }

            inline Mat3 operator =(const Mat3& m) {
                mat[0] = m.mat[0];
                mat[3] = m.mat[3];
                mat[6] = m.mat[6];
                mat[1] = m.mat[1];
                mat[4] = m.mat[4];
                mat[7] = m.mat[7];
                mat[2] = m.mat[2];
                mat[5] = m.mat[5];
                mat[8] = m.mat[8];
            }

            inline bool operator ==(const Mat3& m) {
                return !(
                           mat[0] != m.mat[0] || mat[3] != m.mat[3] || mat[6] != m.mat[6] ||
                           mat[1] != m.mat[1] || mat[4] != m.mat[4] || mat[7] != m.mat[7] ||
                           mat[2] != m.mat[2] || mat[5] != m.mat[5] || mat[8] != m.mat[8]
                       );
            }

            inline bool operator !=(const Mat3& m) {
                return (
                           mat[0] != m.mat[0] || mat[3] != m.mat[3] || mat[6] != m.mat[6] ||
                           mat[1] != m.mat[1] || mat[4] != m.mat[4] || mat[7] != m.mat[7] ||
                           mat[2] != m.mat[2] || mat[5] != m.mat[5] || mat[8] != m.mat[8]
                       );
            }

            inline std::string ToString(int p = 5) {

                return (
                           "Mat3[\n"
                           "  "+ util.ToString(mat[0], p) +", "+ util.ToString(mat[3], p) +", "+ util.ToString(mat[6], p) +",\n"+
                           "  "+ util.ToString(mat[1], p) +", "+ util.ToString(mat[4], p) +", "+ util.ToString(mat[7], p) +",\n"+
                           "  "+ util.ToString(mat[2], p) +", "+ util.ToString(mat[5], p) +", "+ util.ToString(mat[8], p) +"\n"+
                           "]"
                       );
            }
    };
}

#endif