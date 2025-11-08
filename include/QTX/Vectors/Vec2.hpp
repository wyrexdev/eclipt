#include "Headers/Headers.hpp"

namespace QTX
{
    class Vec2
    {
    public:
        // ------- Constructor -------
        Vec2(float _x, float _y) : x(_x), y(_y) {}
        //
        // ================== FUNCTIONS START ==================
        //
        // ------- Get Functions START -------
        float getX() { return x; }
        float getY() { return y; }
        // ------- Get Functions END -------
        //
        // ------- Length START -------
        float length() const
        {
            return std::sqrt(x * x + y * y);
        }
        // ------- Length END -------
        //
        // ------- Normalize START -------
        void normalize()
        {
            float len = length();
            if (len > 1e-8f)
            {
                x /= len;
                y /= len;
            }
        }
        //
        Vec2 normalized() const
        {
            float len = length();
            return (len > 1e-8f) ? Vec2(x / len, y / len) : Vec2(0, 0);
        }
        // ------- Normalize END -------
        //
        // ================== FUNCTIONS END ==================
        //
        // ================== STATIC FUNCTIONS START ==================
        //
        // ------- Zero START -------
        static Vec2 zero() { return {0, 0}; }
        // ------- Zero END -------
        //
        // ------- One START -------
        static Vec2 one() { return {1, 1}; }
        // ------- One END -------
        //
        // ------- Up START -------
        static Vec2 up() { return {0, 1}; }
        // ------- Up END -------
        //
        // ------- Down START -------
        static Vec2 down() { return {0, -1}; }
        // ------- Down END -------
        //
        // ------- Left START -------
        static Vec2 left() { return {-1, 0}; }
        // ------- Left END -------
        //
        // ------- Right START -------
        static Vec2 right() { return {1, 0}; }
        // ------- Right END -------
        //
        // ================== STATIC FUNCTIONS END ==================
    private:
        float x;
        float y;
    };
}