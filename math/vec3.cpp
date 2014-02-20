#ifndef ODIN_VEC3_CPP
#define ODIN_VEC3_CPP

namespace Odin {

    inline Vec3 Vec3::operator *(const Mat2& m) {

        return Vec3(
                   x * m[0] + y * m[2],
                   x * m[1] + y * m[3],
                   0
               );
    }

    inline Vec3& Vec3::operator *=(const Mat2& m) {
        float tx = x, ty = y;

        x = tx * m[0] + ty * m[2];
        y = tx * m[1] + ty * m[3];

        return *this;
    }

    inline Vec3 Vec3::operator *(const Mat32& m) {

        return Vec3(
                   x * m[0] + y * m[2] + m[4],
                   x * m[1] + y * m[3] + m[5],
                   0
               );
    }

    inline Vec3& Vec3::operator *=(const Mat32& m) {
        float tx = x, ty = y;

        x = tx * m[0] + ty * m[2] + m[4];
        y = tx * m[1] + ty * m[3] + m[5];

        return *this;
    }

    inline Vec3 Vec3::operator *(const Mat4& m) {

        return Vec3(
                   x * m[0] + y * m[4] + z * m[8] + m[12],
                   x * m[1] + y * m[5] + z * m[9] + m[13],
                   x * m[2] + y * m[6] + z * m[10] + m[14]
               );
    }

    inline Vec3& Vec3::operator *=(const Mat4& m) {
        float tx = x, ty = y, tz = z;

        x = tx * m[0] + ty * m[4] + tz * m[8] + m[12];
        y = tx * m[1] + ty * m[5] + tz * m[9] + m[13];
        z = tx * m[2] + ty * m[6] + tz * m[10] + m[14];

        return *this;
    }
}

#endif