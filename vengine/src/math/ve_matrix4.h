#pragma once

#include "common/ve_common.h"
#include "ve_vector.h"

// clang-format off

#define M4_3X3MINOR(x, c0, c1, c2, r0, r1, r2) \
    (x[c0 * 4 + r0] * (x[c1 * 4 + r1] * x[c2 * 4 + r2] - x[c1 * 4 + r2] * x[c2 * 4 + r1]) - \
     x[c1 * 4 + r0] * (x[c0 * 4 + r1] * x[c2 * 4 + r2] - x[c0 * 4 + r2] * x[c2 * 4 + r1]) + \
     x[c2 * 4 + r0] * (x[c0 * 4 + r1] * x[c1 * 4 + r2] - x[c0 * 4 + r2] * x[c1 * 4 + r1]))

namespace VE {
    struct Matrix4 {
        __forceinline Matrix4() noexcept : xx(1), xy(0), xz(0), xw(0),
                    yx(0), yy(1), yz(0), yw(0),
                    zx(0), zy(0), zz(1), zw(0),
                    tx(0), ty(0), tz(0), tw(1) {}

        __forceinline Matrix4(float _00, float _01, float _02, float _03,
                float _10, float _11, float _12, float _13,
                float _20, float _21, float _22, float _23,
                float _30, float _31, float _32, float _33) noexcept :
                xx(_00), xy(_01), xz(_02), xw(_03),
                yx(_10), yy(_11), yz(_12), yw(_13),
                zx(_20), zy(_21), zz(_22), zw(_23),
                tx(_30), ty(_31), tz(_32), tw(_33) {}

        __forceinline Matrix4(const float *fv) noexcept :
                xx(fv[0]), xy(fv[1]), xz(fv[2]), xw(fv[3]),
                yx(fv[4]), yy(fv[5]), yz(fv[6]), yw(fv[7]),
                zx(fv[8]), zy(fv[9]), zz(fv[10]), zw(fv[11]),
                tx(fv[12]), ty(fv[13]), tz(fv[14]), tw(fv[15]) {}

        __forceinline bool operator==(const Matrix4 &other) const noexcept {
            for (size_t i = 0; i < 16; ++i) {
                if (fabsf(this->v[i] - other.v[i]) > VE::EPSILON) return false;
            }
            return true;
        }

        __forceinline bool operator!=(const Matrix4 &other) const noexcept {
            return !(*this == other);
        }

        __forceinline Matrix4 operator+(const Matrix4 &other) const noexcept {
            return Matrix4(
                    this->xx + other.xx, this->xy + other.xy, this->xz + other.xz, this->xw + other.xw,
                    this->yx + other.yx, this->yy + other.yy, this->yz + other.yz, this->yw + other.yw,
                    this->zx + other.zx, this->zy + other.zy, this->zz + other.zz, this->zw + other.zw,
                    this->tx + other.tx, this->ty + other.ty, this->tz + other.tz, this->tw + other.tw
            );
        }

        __forceinline Matrix4 operator-(const Matrix4 &other) const noexcept {
            return Matrix4(
                    this->xx - other.xx, this->xy - other.xy, this->xz - other.xz, this->xw - other.xw,
                    this->yx - other.yx, this->yy - other.yy, this->yz - other.yz, this->yw - other.yw,
                    this->zx - other.zx, this->zy - other.zy, this->zz - other.zz, this->zw - other.zw,
                    this->tx - other.tx, this->ty - other.ty, this->tz - other.tz, this->tw - other.tw
            );
        }

        __forceinline Matrix4 operator*(float f) const noexcept {
            return Matrix4(
                    xx * f, xy * f, xz * f, xw * f,
                    yx * f, yy * f, yz * f, yw * f,
                    zx * f, zy * f, zz * f, zw * f,
                    tx * f, ty * f, tz * f, tw * f
            );
        }

        __forceinline Matrix4 operator/(float f) const noexcept {
            f = 1.0f / f;
            return Matrix4(
                    xx * f, xy * f, xz * f, xw * f,
                    yx * f, yy * f, yz * f, yw * f,
                    zx * f, zy * f, zz * f, zw * f,
                    tx * f, ty * f, tz * f, tw * f
            );
        }

        __forceinline Matrix4 &operator+=(const Matrix4 &other) noexcept {
            for (size_t i = 0; i < 16; ++i) {
                this->v[i] += other.v[i];
            }
            return *this;
        }

        __forceinline Matrix4 &operator-=(const Matrix4 &other) noexcept {
            for (size_t i = 0; i < 16; ++i) {
                this->v[i] -= other.v[i];
            }
            return *this;
        }

        __forceinline Matrix4 &operator*=(float f) noexcept {
            for (size_t i = 0; i < 16; ++i) {
                this->v[i] *= f;
            }
            return *this;
        }

        __forceinline Matrix4 &operator/=(float f) noexcept {
            f = 1.0f / f;
            for (size_t i = 0; i < 16; ++i) {
                this->v[i] *= f;
            }
            return *this;
        }

        __forceinline Matrix4 operator*(const Matrix4 &other) const noexcept {
            return Matrix4(
                    this->v[0] * other.v[0] + this->v[4] * other.v[1] + this->v[8] * other.v[2] + this->v[12] * other.v[3], //0
                    this->v[1] * other.v[0] + this->v[5] * other.v[1] + this->v[9] * other.v[2] + this->v[13] * other.v[3], // 1
                    this->v[2] * other.v[0] + this->v[6] * other.v[1] + this->v[10] * other.v[2] + this->v[14] * other.v[3], // 2
                    this->v[3] * other.v[0] + this->v[7] * other.v[1] + this->v[11] * other.v[2] + this->v[15] * other.v[3], //3
                    this->v[0] * other.v[4] + this->v[4] * other.v[5] + this->v[8] * other.v[6] + this->v[12] * other.v[7], // 4
                    this->v[1] * other.v[4] + this->v[5] * other.v[5] + this->v[9] * other.v[6] + this->v[13] * other.v[7], // 5
                    this->v[2] * other.v[4] + this->v[6] * other.v[5] + this->v[10] * other.v[6] + this->v[14] * other.v[7], // 6
                    this->v[3] * other.v[4] + this->v[7] * other.v[5] + this->v[11] * other.v[6] + this->v[15] * other.v[7], // 7
                    this->v[0] * other.v[8] + this->v[4] * other.v[9] + this->v[8] * other.v[10] + this->v[12] * other.v[11], // 8
                    this->v[1] * other.v[8] + this->v[5] * other.v[9] + this->v[9] * other.v[10] + this->v[13] * other.v[11], // 9
                    this->v[2] * other.v[8] + this->v[6] * other.v[9] + this->v[10] * other.v[10] + this->v[14] * other.v[11], // 10
                    this->v[3] * other.v[8] + this->v[7] * other.v[9] + this->v[11] * other.v[10] + this->v[15] * other.v[11], // 11
                    this->v[0] * other.v[12] + this->v[4] * other.v[13] + this->v[8] * other.v[14] + this->v[12] * other.v[15], // 12
                    this->v[1] * other.v[12] + this->v[5] * other.v[13] + this->v[9] * other.v[14] + this->v[13] * other.v[15], // 13
                    this->v[2] * other.v[12] + this->v[6] * other.v[13] + this->v[10] * other.v[14] + this->v[14] * other.v[15], // 14
                    this->v[3] * other.v[12] + this->v[7] * other.v[13] + this->v[11] * other.v[14] + this->v[15] * other.v[15]); // 15
        }

        __forceinline Vector4 operator*(const Vector4 &other) const noexcept {
            return Vector4{this->v[0] * other.v[0] + this->v[4] * other.v[1] + this->v[8] * other.v[2] + this->v[12] * other.v[3],
                           this->v[1] * other.v[0] + this->v[5] * other.v[1] + this->v[9] * other.v[2] + this->v[13] * other.v[3],
                           this->v[2] * other.v[0] + this->v[6] * other.v[1] + this->v[10] * other.v[2] + this->v[14] * other.v[3],
                           this->v[3] * other.v[0] + this->v[7] * other.v[1] + this->v[11] * other.v[2] + this->v[15] * other.v[3]};
        }

        __forceinline Vector3 transformPoint(const Vector3 &vector) const noexcept {
            return Vector3(this->v[0] * vector.v[0] + this->v[4] * vector.v[1] + this->v[8] * vector.v[2] + this->v[12] * 1.0f,
                           this->v[1] * vector.v[0] + this->v[5] * vector.v[1] + this->v[9] * vector.v[2] + this->v[13] * 1.0f,
                           this->v[2] * vector.v[0] + this->v[6] * vector.v[1] + this->v[10] * vector.v[2] + this->v[14] * 1.0f);
        }

        __forceinline Vector3 transformVector(const Vector3 &vector) const noexcept {
        return Vector3(this->v[0] * vector.v[0] + this->v[4] * vector.v[1] + this->v[8] * vector.v[2],
                       this->v[1] * vector.v[0] + this->v[5] * vector.v[1] + this->v[9] * vector.v[2],
                       this->v[2] * vector.v[0] + this->v[6] * vector.v[1] + this->v[10] * vector.v[2]);
      }

        __forceinline Vector3 transformVector(const Vector3 &vector, float &w) const noexcept {
            float tmpw = w;
            w = this->v[3] * vector.v[0] + this->v[7] * vector.v[1] + this->v[11] * vector.v[2] + this->v[15] * tmpw;

            return Vector3(this->v[0] * vector.v[0] + this->v[4] * vector.v[1] + this->v[8] * vector.v[2] + this->v[12] * tmpw,
                           this->v[1] * vector.v[0] + this->v[5] * vector.v[1] + this->v[9] * vector.v[2] + this->v[13] * tmpw,
                           this->v[2] * vector.v[0] + this->v[6] * vector.v[1] + this->v[10] * vector.v[2] + this->v[14] * tmpw);
        }

        __forceinline Matrix4 getTransposed() const noexcept {
            return Matrix4(xx, yx, zx, tx,
                           xy, yy, zy, ty,
                           xz, yz, zz, tz,
                           xw, yw, zw, tw);
        }

        __forceinline Matrix4 &transpose() noexcept {
            std::swap(yx, xy);
            std::swap(zx, xz);
            std::swap(tx, xw);
            std::swap(zy, yz);
            std::swap(ty, yw);
            std::swap(tz, zw);

            return *this;
        }

        __forceinline float determinant() const noexcept {
            return this->v[0] * M4_3X3MINOR(this->v, 1, 2, 3, 1, 2, 3)
                   - this->v[4] * M4_3X3MINOR(this->v, 0, 2, 3, 1, 2, 3)
                   + this->v[8] * M4_3X3MINOR(this->v, 0, 1, 3, 1, 2, 3)
                   - this->v[12] * M4_3X3MINOR(this->v, 0, 1, 2, 1, 2, 3);
        }

        __forceinline Matrix4 getInversed() const noexcept {
            float det = this->determinant();
            if (det == 0.0f) {
                return Matrix4();
            }

            //Cof (M[i, j]) = Minor(M[i, j]] * pow(-1, i + j)
            Matrix4 cofactor;
            cofactor.v[0] = M4_3X3MINOR(this->v, 1, 2, 3, 1, 2, 3);
            cofactor.v[4] = -M4_3X3MINOR(this->v, 1, 2, 3, 0, 2, 3);
            cofactor.v[8] = M4_3X3MINOR(this->v, 1, 2, 3, 0, 1, 3);
            cofactor.v[12] = -M4_3X3MINOR(this->v, 1, 2, 3, 0, 1, 2);

            cofactor.v[1] = -M4_3X3MINOR(this->v, 0, 2, 3, 1, 2, 3);
            cofactor.v[5] = M4_3X3MINOR(this->v, 0, 2, 3, 0, 2, 3);
            cofactor.v[9] = -M4_3X3MINOR(this->v, 0, 2, 3, 0, 1, 3);
            cofactor.v[13] = M4_3X3MINOR(this->v, 0, 2, 3, 0, 1, 2);

            cofactor.v[2] = M4_3X3MINOR(this->v, 0, 1, 3, 1, 2, 3);
            cofactor.v[6] = -M4_3X3MINOR(this->v, 0, 1, 3, 0, 2, 3);
            cofactor.v[10] = M4_3X3MINOR(this->v, 0, 1, 3, 0, 1, 3);
            cofactor.v[14] = -M4_3X3MINOR(this->v, 0, 1, 3, 0, 1, 2);

            cofactor.v[3] = -M4_3X3MINOR(this->v, 0, 1, 2, 1, 2, 3);
            cofactor.v[7] = M4_3X3MINOR(this->v, 0, 1, 2, 0, 2, 3);
            cofactor.v[11] = -M4_3X3MINOR(this->v, 0, 1, 2, 0, 1, 3);
            cofactor.v[15] = M4_3X3MINOR(this->v, 0, 1, 2, 0, 1, 2);

            return cofactor * (1.0f / det);
        }

        __forceinline Matrix4 &inverse() noexcept {
            *this = this->getInversed();
            return *this;
        }

        __forceinline Matrix4 &setZero() noexcept {
            v[0] = 0;
            v[1] = 0;
            v[2] = 0;
            v[3] = 0;
            v[4] = 0;
            v[5] = 0;
            v[6] = 0;
            v[7] = 0;
            v[8] = 0;
            v[9] = 0;
            v[10] = 0;
            v[11] = 0;
            v[12] = 0;
            v[13] = 0;
            v[14] = 0;
            v[15] = 0;
            return *this;
        }

        __forceinline Matrix4 &setIdentity() noexcept {
            v[0] = 1;
            v[1] = 0;
            v[2] = 0;
            v[3] = 0;
            v[4] = 0;
            v[5] = 1;
            v[6] = 0;
            v[7] = 0;
            v[8] = 0;
            v[9] = 0;
            v[10] = 1;
            v[11] = 0;
            v[12] = 0;
            v[13] = 0;
            v[14] = 0;
            v[15] = 1;
            return *this;
        }

        __forceinline const float *data() const noexcept {
            return v;
        }

        __forceinline float *data() {
            return v;
        }

        __forceinline static constexpr std::size_t size() noexcept{
            return 16;
        }

        __forceinline void print() const noexcept {
            std::cout << std::endl;
            std::cout << v[0] << "\t" << v[1] << "\t" << v[2] << "\t" << v[3] << std::endl;
            std::cout << v[4] << "\t" << v[5] << "\t" << v[6] << "\t" << v[7] << std::endl;
            std::cout << v[8] << "\t" << v[9] << "\t" << v[10] << "\t" << v[11] << std::endl;
            std::cout << v[12] << "\t" << v[13] << "\t" << v[14] << "\t" << v[15] << std::endl;
            std::cout << std::endl;
        }

       Vector3& GetAxisX() { return vec[0].xyz; }
       Vector3& GetAxisY() { return vec[1].xyz; }
       Vector3& GetAxisZ() { return vec[2].xyz; }
       Vector3& GetOrigin() { return vec[3].xyz; }
       
        union {
            float v[16] = {0};
           struct {
              SVector4 right;
              SVector4 forward;
              SVector4 up;
              SVector4 position;
           };
           struct {
              SVector4 vec[4];
           };
            struct {
                float _00;
                float _10;
                float _20;
                float _30;
                float _01;
                float _11;
                float _21;
                float _31;
                float _02;
                float _12;
                float _22;
                float _32;
                float _03;
                float _13;
                float _23;
                float _33;
            };
            struct {
                float xx;
                float xy;
                float xz;
                float xw;
                float yx;
                float yy;
                float yz;
                float yw;
                float zx;
                float zy;
                float zz;
                float zw;
                float tx;
                float ty;
                float tz;
                float tw;
            };
        };
    };

    inline Vector4 operator*(const Vector4 &b, const Matrix4 &a) {
        return Vector4{a.v[0] * b.v[0] + a.v[1] * b.v[1] + a.v[2] * b.v[2] + a.v[3] * b.v[3],
                       a.v[4] * b.v[0] + a.v[5] * b.v[1] + a.v[6] * b.v[2] + a.v[7] * b.v[3],
                       a.v[8] * b.v[0] + a.v[9] * b.v[1] + a.v[10] * b.v[2] + a.v[11] * b.v[3],
                       a.v[12] * b.v[0] + a.v[13] * b.v[1] + a.v[14] * b.v[2] + a.v[15] * b.v[3]};
    }
}


// clang-format on