#pragma once

#include <cmath>

namespace Eclipt
{
    namespace QTX
    {
        class Mat2
        {
        public:
            float m[2][2];

            // -------------------------
            // Constructors
            // -------------------------
            Mat2()
            {
                m[0][0] = m[0][1] = 0.0f;
                m[1][0] = m[1][1] = 0.0f;
            }

            Mat2(float diag)
            {
                m[0][0] = diag;
                m[0][1] = 0.0f;
                m[1][0] = 0.0f;
                m[1][1] = diag;
            }

            static Mat2 identity()
            {
                return Mat2(1.0f);
            }

            // -------------------------
            // Scale
            // -------------------------
            static Mat2 scale(float sx, float sy)
            {
                Mat2 r = Mat2::identity();
                r.m[0][0] = sx;
                r.m[1][1] = sy;
                return r;
            }

            // -------------------------
            // Rotation (2D)
            // -------------------------
            static Mat2 rotate(float deg)
            {
                float rad = deg * (3.14159265f / 180.0f);
                float c = cos(rad);
                float s = sin(rad);

                Mat2 r;
                r.m[0][0] = c;
                r.m[0][1] = -s;
                r.m[1][0] = s;
                r.m[1][1] = c;

                return r;
            }

            // -------------------------
            // Matrix multiplication
            // -------------------------
            Mat2 operator*(const Mat2 &o) const
            {
                Mat2 r;

                r.m[0][0] = m[0][0] * o.m[0][0] + m[0][1] * o.m[1][0];
                r.m[0][1] = m[0][0] * o.m[0][1] + m[0][1] * o.m[1][1];

                r.m[1][0] = m[1][0] * o.m[0][0] + m[1][1] * o.m[1][0];
                r.m[1][1] = m[1][0] * o.m[0][1] + m[1][1] * o.m[1][1];

                return r;
            }

            // -------------------------
            // Transform vec2
            // -------------------------
            inline void transform(float &x, float &y) const
            {
                float nx = m[0][0] * x + m[0][1] * y;
                float ny = m[1][0] * x + m[1][1] * y;
                x = nx;
                y = ny;
            }
        };
    }
}