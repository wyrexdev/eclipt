#pragma once

#include <cmath>

namespace Eclipt
{
    namespace QTX
    {
        class Mat3
        {
        public:
            float m[3][3];

            // -------------------------
            // Constructors
            // -------------------------
            Mat3()
            {
                for (int i = 0; i < 3; i++)
                    for (int j = 0; j < 3; j++)
                        m[i][j] = 0.0f;
            }

            Mat3(float diag)
            {
                for (int i = 0; i < 3; i++)
                    for (int j = 0; j < 3; j++)
                        m[i][j] = (i == j) ? diag : 0.0f;
            }

            static Mat3 identity()
            {
                return Mat3(1.0f);
            }

            // -------------------------
            // Translation (2D)
            // -------------------------
            static Mat3 translate(float tx, float ty)
            {
                Mat3 r = Mat3::identity();
                r.m[0][2] = tx;
                r.m[1][2] = ty;
                return r;
            }

            // -------------------------
            // Scale (2D)
            // -------------------------
            static Mat3 scale(float sx, float sy)
            {
                Mat3 r = Mat3::identity();
                r.m[0][0] = sx;
                r.m[1][1] = sy;
                return r;
            }

            // -------------------------
            // Rotation (2D)
            // -------------------------
            static Mat3 rotate(float deg)
            {
                float rad = deg * (3.14159265f / 180.0f);
                float c = cos(rad);
                float s = sin(rad);

                Mat3 r = Mat3::identity();

                r.m[0][0] = c;
                r.m[0][1] = -s;
                r.m[1][0] = s;
                r.m[1][1] = c;

                return r;
            }

            // -------------------------
            // Matrix multiplication
            // -------------------------
            Mat3 operator*(const Mat3 &o) const
            {
                Mat3 r;

                for (int row = 0; row < 3; row++)
                {
                    for (int col = 0; col < 3; col++)
                    {
                        r.m[row][col] =
                            m[row][0] * o.m[0][col] +
                            m[row][1] * o.m[1][col] +
                            m[row][2] * o.m[2][col];
                    }
                }

                return r;
            }

            // -------------------------
            // Transform vec2
            // -------------------------
            inline void transform2D(float &x, float &y) const
            {
                float nx = m[0][0] * x + m[0][1] * y + m[0][2];
                float ny = m[1][0] * x + m[1][1] * y + m[1][2];
                x = nx;
                y = ny;
            }

            // -------------------------
            // Transform vec3 (homogeneous)
            // -------------------------
            inline void transform3D(float &x, float &y, float &z) const
            {
                float nx = m[0][0] * x + m[0][1] * y + m[0][2] * z;
                float ny = m[1][0] * x + m[1][1] * y + m[1][2] * z;
                float nz = m[2][0] * x + m[2][1] * y + m[2][2] * z;
                x = nx;
                y = ny;
                z = nz;
            }
        };
    }
}