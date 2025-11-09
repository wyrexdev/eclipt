#pragma once

#include "Headers/Headers.hpp"

namespace QTX
{
    class Vec3
    {
    public:
        // ------- Constructor -------
        Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
        //
        // ================== FUNCTIONS START ==================
        //
        // ------- Get Functions START -------
        float getX() { return x; }
        float getY() { return y; }
        float getZ() { return z; }
        // ------- Get Functions END -------
        //
        // ------- Length START -------
        float length() const
        {
            return std::sqrt(x * x + y * y + z * z);
        }
        // ------- Length END -------
        //
        // ------- LengthSquared START -------
        float length_squared() const {
            return x * x + y * y + z * z;
        }
        // ------- LengthSquared END -------
        //
        // ------- Operators START -------
        //
        // ------- + -------
        Vec3 operator+(const Vec3 &v) const
        {
            return Vec3(x + v.x, y + v.y, z + v.z);
        }
        // ------- - -------
        Vec3 operator-(const Vec3 &v) const
        {
            return Vec3(x - v.x, y - v.y, z - v.z);
        }
        // ------- * -------
        Vec3 operator*(float s) const
        {
            return Vec3(x * s, y * s, z * s);
        }
        // ------- / -------
        Vec3 operator/(float s) const
        {
            if (s == 0.0f)
                return Vec3(0.0f, 0.0f, 0.0f);
            float inv = 1.0f / s;
            return Vec3(x * inv, y * inv, z * inv);
        }
        // ------- += -------
        Vec3 &operator+=(const Vec3 &v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }
        // ------- -= -------
        Vec3 &operator-=(const Vec3 &v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }
        // ------- *= -------
        Vec3 &operator*=(float s)
        {
            x *= s;
            y *= s;
            z *= s;
            return *this;
        }
        // ------- /= -------
        Vec3 &operator/=(float s)
        {
            if (s == 0.0f)
                return *this;
            float inv = 1.0f / s;
            x *= inv;
            y *= inv;
            z *= inv;
            return *this;
        }
        // ------- == -------
        bool operator==(const Vec3 &v) const
        {
            constexpr float EPSILON = 1e-6f;
            return (std::fabs(x - v.x) < EPSILON) &&
                   (std::fabs(y - v.y) < EPSILON) &&
                   (std::fabs(z - v.z) < EPSILON);
        }
        // ------- != -------
        bool operator!=(const Vec3 &v) const
        {
            return !(*this == v);
        }
        //
        // ------- Operators END -------
        //
        // ================== FUNCTIONS END ==================
        //
        // ================== STATIC FUNCTIONS START ==================
        //
        // ------- Zero START -------
        static Vec3 zero()
        {
            return {0, 0, 0};
        }
        // ------- Zero END -------
        //
        // ------- One START -------
        static Vec3 one()
        {
            return {0, 0, 0};
        }
        // ------- One END -------
        //
        // ================== STATIC FUNCTIONS END ==================
    private:
        float x;
        float y;
        float z;
    };
}