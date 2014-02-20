#ifndef ODIN_VEC2_CPP
#define ODIN_VEC2_CPP

namespace Odin {

    inline Quat& Quat::FromMatrix(const Mat3& m) {
        float m11 = m.mat[0],
              m12 = m.mat[3],
              m13 = m.mat[6],
              m21 = m.mat[1],
              m22 = m.mat[4],
              m23 = m.mat[7],
              m31 = m.mat[2],
              m32 = m.mat[5],
              m33 = m.mat[8],
              trace = m11 + m22 + m33,
              s, invS;

        if (trace > 0) {
            s = 0.5 / sqrt(trace + 1);

            w = 0.25 / s;
            x = (m32 - m23) * s;
            y = (m13 - m31) * s;
            z = (m21 - m12) * s;
        } else if (m11 > m22 && m11 > m33) {
            s = 2 * sqrt(1 + m11 - m22 - m33);
            invS = 1 / s;

            w = (m32 - m23) * invS;
            x = 0.25 * s;
            y = (m12 + m21) * invS;
            z = (m13 + m31) * invS;
        } else if (m22 > m33) {
            s = 2 * sqrt(1 + m22 - m11 - m33);
            invS = 1 / s;

            w = (m13 - m31) * invS;
            x = (m12 + m21) * invS;
            y = 0.25 * s;
            z = (m23 + m32) * invS;
        } else {
            s = 2 * sqrt(1 + m33 - m11 - m22);
            invS = 1 / s;

            w = (m21 - m12) * invS;
            x = (m13 + m31) * invS;
            y = (m23 + m32) * invS;
            z = 0.25 * s;
        }

        return *this;
    }

    inline Quat& Quat::FromMatrix(const Mat4& m) {
        float m11 = m.mat[0],
              m12 = m.mat[4],
              m13 = m.mat[8],
              m21 = m.mat[1],
              m22 = m.mat[5],
              m23 = m.mat[9],
              m31 = m.mat[2],
              m32 = m.mat[6],
              m33 = m.mat[10],
              trace = m11 + m22 + m33,
              s, invS;

        if (trace > 0) {
            s = 0.5 / sqrt(trace + 1);

            w = 0.25 / s;
            x = (m32 - m23) * s;
            y = (m13 - m31) * s;
            z = (m21 - m12) * s;
        } else if (m11 > m22 && m11 > m33) {
            s = 2 * sqrt(1 + m11 - m22 - m33);
            invS = 1 / s;

            w = (m32 - m23) * invS;
            x = 0.25 * s;
            y = (m12 + m21) * invS;
            z = (m13 + m31) * invS;
        } else if (m22 > m33) {
            s = 2 * sqrt(1 + m22 - m11 - m33);
            invS = 1 / s;

            w = (m13 - m31) * invS;
            x = (m12 + m21) * invS;
            y = 0.25 * s;
            z = (m23 + m32) * invS;
        } else {
            s = 2 * sqrt(1 + m33 - m11 - m22);
            invS = 1 / s;

            w = (m21 - m12) * invS;
            x = (m13 + m31) * invS;
            y = (m23 + m32) * invS;
            z = 0.25 * s;
        }

        return *this;
    }
}

#endif