#ifndef ODIN_MAT3_H
#define ODIN_MAT3_H

namespace Odin {

    inline Mat3& Mat3::Inverse(const Mat4& m) {
        float m11 = m.mat[0], m12 = m.mat[4], m13 = m.mat[8],
              m21 = m.mat[1], m22 = m.mat[5], m23 = m.mat[9],
              m31 = m.mat[2], m32 =m. mat[6], m33 = m.mat[10],

              m0 = m22 * m33 - m23 * m32,
              m3 = m13 * m32 - m12 * m33,
              m6 = m12 * m23 - m13 * m22,

              det = m11 * m0 + m21 * m3 + m31 * m6;

        det = det !== 0 ? 1 / det : 1;

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

    inline Mat3& Mat3::ExtractRotation(const Mat4& m) {
        Vec3 vec;
        float lx = Mathf.V3LengthSq(m.mat[0], m.mat[1], m.mat[2]),
              ly = Mathf.V3LengthSq(m.mat[4], m.mat[5], m.mat[6]),
              lz = Mathf.V3LengthSq(m.mat[8], m.mat[9], m.mat[10]),

              scaleX = lx > 0 ? 1 / std::sqrt(lx) : 0,
              scaleY = ly > 0 ? 1 / std::sqrt(ly) : 0,
              scaleZ = lz > 0 ? 1 / std::sqrt(lz) : 0;

        mat[0] = m.mat[0] * scaleX;
        mat[1] = m.mat[1] * scaleX;
        mat[2] = m.mat[2] * scaleX;

        mat[3] = m.mat[4] * scaleY;
        mat[4] = m.mat[5] * scaleY;
        mat[5] = m.mat[6] * scaleY;

        mat[6] = m.mat[8] * scaleZ;
        mat[7] = m.mat[9] * scaleZ;
        mat[8] = m.mat[10] * scaleZ;

        return *this;
    }

    inline Mat3& Mat3::ExtractRotationWithScale(const Mat4& m) {

        mat[0] = m.mat[0];
        mat[1] = m.mat[1];
        mat[2] = m.mat[2];

        mat[3] = m.mat[4];
        mat[4] = m.mat[5];
        mat[5] = m.mat[6];

        mat[6] = m.mat[8];
        mat[7] = m.mat[9];
        mat[8] = m.mat[10];

        return *this;
    }
}

#endif