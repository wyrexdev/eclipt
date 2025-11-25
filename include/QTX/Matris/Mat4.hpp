#pragma once

#include "Headers/Headers.hpp"

namespace Eclipt
{
    namespace QTX
    {
        class Mat4
        {
        public:
            float m[4][4];

            // -------------------------
            // Constructors
            // -------------------------
            Mat4()
            {
                for (int i = 0; i < 4; i++)
                    for (int j = 0; j < 4; j++)
                        m[i][j] = 0.0f;
            }

            Mat4(float diag)
            {
                for (int i = 0; i < 4; i++)
                    for (int j = 0; j < 4; j++)
                        m[i][j] = (i == j) ? diag : 0.0f;
            }

            static Mat4 identity()
            {
                return Mat4(1.0f);
            }

            static Mat4 orthographic(float left, float right, float bottom, float top, float near, float far)
            {
                Mat4 result = identity();
                result.m[0][0] = 2.0f / (right - left);
                result.m[1][1] = 2.0f / (top - bottom);
                result.m[2][2] = -2.0f / (far - near);
                result.m[3][0] = -(right + left) / (right - left);
                result.m[3][1] = -(top + bottom) / (top - bottom);
                result.m[3][2] = -(far + near) / (far - near);
                return result;
            }

            // -------------------------
            // Translation
            // -------------------------
            static Mat4 translate(float x, float y, float z)
            {
                Mat4 r = Mat4::identity();
                r.m[0][3] = x;
                r.m[1][3] = y;
                r.m[2][3] = z;
                return r;
            }

            // -------------------------
            // Scale
            // -------------------------
            static Mat4 scale(float x, float y, float z)
            {
                Mat4 r = Mat4::identity();
                r.m[0][0] = x;
                r.m[1][1] = y;
                r.m[2][2] = z;
                return r;
            }

            // -------------------------
            // Rotation X
            // -------------------------
            static Mat4 rotateX(float deg)
            {
                float r = deg * (3.14159265f / 180.0f);
                Mat4 m = Mat4::identity();

                m.m[1][1] = cos(r);
                m.m[1][2] = -sin(r);
                m.m[2][1] = sin(r);
                m.m[2][2] = cos(r);

                return m;
            }

            // -------------------------
            // Rotation Y
            // -------------------------
            static Mat4 rotateY(float deg)
            {
                float r = deg * (3.14159265f / 180.0f);
                Mat4 m = Mat4::identity();

                m.m[0][0] = cos(r);
                m.m[0][2] = sin(r);
                m.m[2][0] = -sin(r);
                m.m[2][2] = cos(r);

                return m;
            }

            // -------------------------
            // Rotation Z
            // -------------------------
            static Mat4 rotateZ(float deg)
            {
                float r = deg * (3.14159265f / 180.0f);
                Mat4 m = Mat4::identity();

                m.m[0][0] = cos(r);
                m.m[0][1] = -sin(r);
                m.m[1][0] = sin(r);
                m.m[1][1] = cos(r);

                return m;
            }

            // -------------------------
            // Matrix multiplication
            // -------------------------
            Mat4 operator*(const Mat4 &o) const
            {
                Mat4 r;

                for (int row = 0; row < 4; row++)
                {
                    for (int col = 0; col < 4; col++)
                    {
                        r.m[row][col] =
                            m[row][0] * o.m[0][col] +
                            m[row][1] * o.m[1][col] +
                            m[row][2] * o.m[2][col] +
                            m[row][3] * o.m[3][col];
                    }
                }

                return r;
            }

            // -------------------------
            // Transform a vec3
            // -------------------------
            inline void transform(float &x, float &y, float &z) const
            {
                float nx = m[0][0] * x + m[0][1] * y + m[0][2] * z + m[0][3];
                float ny = m[1][0] * x + m[1][1] * y + m[1][2] * z + m[1][3];
                float nz = m[2][0] * x + m[2][1] * y + m[2][2] * z + m[2][3];
                x = nx;
                y = ny;
                z = nz;
            }
        };
    }
}