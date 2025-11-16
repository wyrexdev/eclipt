#pragma once

#include "Headers/Headers.hpp"

namespace Eclipt
{
    namespace QTX
    {
        class Ivec3
        {
        public:
            // ------- Constructor -------
            Ivec3(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
            Ivec3() : x(0), y(0), z(0) {}
            //
            // ================== FUNCTIONS START ==================
            //
            // ------- Get Functions START -------
            int getX() const { return x; }
            int getY() const { return y; }
            int getZ() const { return z; }
            // ------- Get Functions END -------
            //
            // ------- Length START -------
            float length() const
            {
                return std::sqrt(float(x * x + y * y + z * z));
            }
            // ------- Length END -------
            //
            // ------- LengthSquared START -------
            float length_squared() const
            {
                return float(x * x + y * y + z * z);
            }
            // ------- LengthSquared END -------
            //
            // ------- Operators START -------
            //
            // ------- + -------
            Ivec3 operator+(const Ivec3 &v) const
            {
                return Ivec3(x + v.x, y + v.y, z + v.z);
            }
            // ------- - -------
            Ivec3 operator-(const Ivec3 &v) const
            {
                return Ivec3(x - v.x, y - v.y, z - v.z);
            }
            // ------- * (int) -------
            Ivec3 operator*(int s) const
            {
                return Ivec3(x * s, y * s, z * s);
            }
            // ------- / (int) -------
            Ivec3 operator/(int s) const
            {
                if (s == 0)
                    return Ivec3(0, 0, 0);
                return Ivec3(x / s, y / s, z / s);
            }
            // ------- += -------
            Ivec3 &operator+=(const Ivec3 &v)
            {
                x += v.x;
                y += v.y;
                z += v.z;
                return *this;
            }
            // ------- -= -------
            Ivec3 &operator-=(const Ivec3 &v)
            {
                x -= v.x;
                y -= v.y;
                z -= v.z;
                return *this;
            }
            // ------- *= -------
            Ivec3 &operator*=(int s)
            {
                x *= s;
                y *= s;
                z *= s;
                return *this;
            }
            // ------- /= -------
            Ivec3 &operator/=(int s)
            {
                if (s == 0)
                    return *this;
                x /= s;
                y /= s;
                z /= s;
                return *this;
            }
            // ------- == -------
            bool operator==(const Ivec3 &v) const
            {
                return (x == v.x) && (y == v.y) && (z == v.z);
            }
            // ------- != -------
            bool operator!=(const Ivec3 &v) const
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
            static Ivec3 zero()
            {
                return {0, 0, 0};
            }
            // ------- Zero END -------
            //
            // ------- One START -------
            static Ivec3 one()
            {
                return {1, 1, 1};
            }
            // ------- One END -------
            //
            // ================== STATIC FUNCTIONS END ==================
        private:
            int x;
            int y;
            int z;
        };
    }
}
