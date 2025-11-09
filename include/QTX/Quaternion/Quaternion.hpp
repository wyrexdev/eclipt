#pragma once

#include "Headers/Headers.hpp"

namespace QTX
{
    class Quaternion
    {
    public:
        // ------- Constructor -------
        Quaternion(float _x, float _y, float _z, float _w)
            : x(_x), y(_y), z(_z), w(_w) {}
        //
        // ------- Destructor -------
        ~Quaternion()
        {
            x = 0;
            y = 0;
            z = 0;
            w = 0;
        }
        //
        // ================== FUNCTIONS START ==================
        //
        // ------- Get Functions START -------
        float getX() { return x; }
        float getY() { return y; }
        float getZ() { return z; }
        float getW() { return w; }
        // ------- Get Functions END -------
        //
        // ------- Length START -------
        float length() const
        {
            return std::sqrt(x * x + y * y + z * z + w * w);
        }
        // ------- Length END -------
        //
        // ------- Indetity START -------
        void make_identity()
        {
            x = 0;
            y = 0;
            z = 0;
            w = 1;
        }
        // ------- Indetity END -------
        //
        // ------- FromAxisAngle START -------
        void make_from_axis_angle(float axis[3], float angle)
        {
            float half = angle * 0.5f;
            float s = std::sin(half);
            x = axis[0] * s;
            y = axis[1] * s;
            z = axis[2] * s;
            w = std::cos(half);
        }
        // ------- FromAxisAngle END -------
        //
        // ------- Mul START -------
        void make_mul(const Quaternion &b)
        {
            float _x = w * b.x + x * b.w + y * b.z - z * b.y;
            float _y = w * b.y - x * b.z + y * b.w + z * b.x;
            float _z = w * b.z + x * b.y - y * b.x + z * b.w;
            float _w = w * b.w - x * b.x - y * b.y - z * b.z;

            x = _x;
            y = _y;
            z = _z;
            w = _w;
        }
        // ------- Mul END -------
        //
        // ------- Conjugate START -------
        void make_conjugate()
        {
            x = -x;
            y = -y;
            z = -z;
        }
        // ------- Conjugate END -------
        //
        // ------- Inverse START -------
        void make_inverse()
        {
            float lengthSq = x * x + y * y + z * z + w * w;
            if (lengthSq == 0)
                return;

            x = -x / lengthSq;
            y = -y / lengthSq;
            z = -z / lengthSq;
            w = w / lengthSq;
        }
        // ------- Inverse END -------
        //
        // ------- Normalize START -------
        void make_normalize()
        {
            float length = std::sqrt(x * x + y * y + z * z + w * w);

            x = x / length;
            y = y / length;
            z = z / length;
            w = w / length;
        }
        // ------- Normalize END -------
        //
        // ------- Clear START -------
        void clear() {
            x = 0;
            y = 0;
            z = 0;
            w = 0;
        }
        // ------- Clear END -------
        //
        // ------- Operators START -------
        //
        // ------- + -------
        Quaternion operator+(const Quaternion &q) const
        {
            return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w);
        }
        // ------- - -------
        Quaternion operator-(const Quaternion &q) const
        {
            return Quaternion(x - q.x, y - q.y, z - q.z, w - q.w);
        }
        // ------- * -------
        Quaternion operator*(const Quaternion &q) const
        {
            return Quaternion(
                w * q.x + x * q.w + y * q.z - z * q.y,
                w * q.y - x * q.z + y * q.w + z * q.x,
                w * q.z + x * q.y - y * q.x + z * q.w,
                w * q.w - x * q.x - y * q.y - z * q.z);
        }
        // ------- * -------
        Quaternion operator*(float s) const
        {
            return Quaternion(x * s, y * s, z * s, w * s);
        }
        // ------- / -------
        Quaternion operator/(float s) const
        {
            if (s == 0.0f)
                return Quaternion(0, 0, 0, 1);
            float inv = 1.0f / s;
            return Quaternion(x * inv, y * inv, z * inv, w * inv);
        }
        // ------- *= -------
        Quaternion &operator*=(const Quaternion &q)
        {
            float _x = w * q.x + x * q.w + y * q.z - z * q.y;
            float _y = w * q.y - x * q.z + y * q.w + z * q.x;
            float _z = w * q.z + x * q.y - y * q.x + z * q.w;
            float _w = w * q.w - x * q.x - y * q.y - z * q.z;
            x = _x;
            y = _y;
            z = _z;
            w = _w;
            return *this;
        }
        // ------- *= -------
        Quaternion &operator*=(float s)
        {
            x *= s;
            y *= s;
            z *= s;
            w *= s;
            return *this;
        }
        // ------- /= -------
        Quaternion &operator/=(float s)
        {
            if (s == 0.0f)
                return *this;
            float inv = 1.0f / s;
            x *= inv;
            y *= inv;
            z *= inv;
            w *= inv;
            return *this;
        }
        // ------- == -------
        bool operator==(const Quaternion &q) const
        {
            constexpr float EPS = 1e-6f;
            return (std::fabs(x - q.x) < EPS) &&
                   (std::fabs(y - q.y) < EPS) &&
                   (std::fabs(z - q.z) < EPS) &&
                   (std::fabs(w - q.w) < EPS);
        }
        // ------- != -------
        bool operator!=(const Quaternion &q) const
        {
            return !(*this == q);
        }
        //
        // ------- Operators END -------
        //
        // ================== FUNCTIONS END ==================
        //
        // ================== STATIC FUNCTIONS START ==================
        //
        // ------- Indetity START -------
        static Quaternion quat_identity()
        {
            return {0, 0, 0, 1};
        }
        // ------- Indetity END -------
        //
        // ------- FromAxisAngle START -------
        static Quaternion quat_from_axis_angle(float axis[3], float angle)
        {
            float half = angle * 0.5f;
            float s = std::sin(half);
            return {axis[0] * s, axis[1] * s, axis[2] * s, std::cos(half)};
        }
        // ------- FromAxisAngle END -------
        //
        // ------- Mul START -------
        static void quat_mul(Quaternion &a, const Quaternion &b)
        {
            float _x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
            float _y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x;
            float _z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w;
            float _w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;

            a.x = _x;
            a.y = _y;
            a.z = _z;
            a.w = _w;
        }
        // ------- Mul END -------
        //
        // ------- Conjugate START -------
        static void quat_conjugate(Quaternion &q)
        {
            q.x = -q.x;
            q.y = -q.y;
            q.z = -q.z;
        }
        // ------- Conjugate END -------
        //
        // ------- Inverse START -------
        static void quat_inverse(Quaternion &q)
        {
            float lengthSq = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
            if (lengthSq == 0)
                return;

            q.x = -q.x / lengthSq;
            q.y = -q.y / lengthSq;
            q.z = -q.z / lengthSq;
            q.w = q.w / lengthSq;
        }
        // ------- Inverse END -------
        //
        // ------- Normalize START -------
        static void quat_normalize(Quaternion &q)
        {
            float length = std::sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);

            q.x = q.x / length;
            q.y = q.y / length;
            q.z = q.z / length;
            q.w = q.w / length;
        }
        //
        static Quaternion quat_normalized(Quaternion &q)
        {
            float length = std::sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
            return {q.x / length, q.y / length, q.z / length, q.w / length};
        }
        // ------- Normalize END -------
        //
        // ================== STATIC FUNCTIONS END ==================
    private:
        float x;
        float y;
        float z;
        float w;
    };
}