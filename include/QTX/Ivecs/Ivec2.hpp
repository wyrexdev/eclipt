#pragma once

#include "Headers/Headers.hpp"

namespace Eclipt
{
    namespace QTX
    {
        class Ivec2
        {
        public:
            // ------- Constructor -------
            Ivec2(int _x, int _y) : x(_x), y(_y) {}
            Ivec2() : x(0), y(0) {}
            //
            // ================== FUNCTIONS START ==================
            //
            // ------- Get Functions START -------
            int getX() const { return x; }
            int getY() const { return y; }
            // ------- Get Functions END -------
            //
            // ------- Length START -------
            float length() const
            {
                return std::sqrt(float(x * x + y * y));
            }
            // ------- Length END -------
            //
            // ------- Operators START -------
            //
            // ------- + -------
            Ivec2 operator+(const Ivec2 &v) const
            {
                return Ivec2(x + v.x, y + v.y);
            }
            // ------- - -------
            Ivec2 operator-(const Ivec2 &v) const
            {
                return Ivec2(x - v.x, y - v.y);
            }
            // ------- * -------
            Ivec2 operator*(int s) const
            {
                return Ivec2(x * s, y * s);
            }
            // ------- / -------
            Ivec2 operator/(int s) const
            {
                if (s == 0)
                    return Ivec2(0, 0);
                return Ivec2(x / s, y / s);
            }
            // ------- += -------
            Ivec2 &operator+=(const Ivec2 &v)
            {
                x += v.x;
                y += v.y;
                return *this;
            }
            // ------- -= -------
            Ivec2 &operator-=(const Ivec2 &v)
            {
                x -= v.x;
                y -= v.y;
                return *this;
            }
            // ------- *= -------
            Ivec2 &operator*=(int s)
            {
                x *= s;
                y *= s;
                return *this;
            }
            // ------- /= -------
            Ivec2 &operator/=(int s)
            {
                if (s == 0)
                    return *this;
                x /= s;
                y /= s;
                return *this;
            }
            // ------- == -------
            bool operator==(const Ivec2 &v) const
            {
                return (x == v.x) && (y == v.y);
            }
            // ------- != -------
            bool operator!=(const Ivec2 &v) const
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
            static Ivec2 zero() { return {0, 0}; }
            // ------- Zero END -------
            //
            // ------- One START -------
            static Ivec2 one() { return {1, 1}; }
            // ------- One END -------
            //
            // ------- Up START -------
            static Ivec2 up() { return {0, 1}; }
            // ------- Up END -------
            //
            // ------- Down START -------
            static Ivec2 down() { return {0, -1}; }
            // ------- Down END -------
            //
            // ------- Left START -------
            static Ivec2 left() { return {-1, 0}; }
            // ------- Left END -------
            //
            // ------- Right START -------
            static Ivec2 right() { return {1, 0}; }
            // ------- Right END -------
            //
            // ================== STATIC FUNCTIONS END ==================
        private:
            int x;
            int y;
        };
    }
}
