#pragma once

#include "Headers/Headers.hpp"

namespace QTX
{
    class Color {
    public:
        // ------- Constructor -------
        Color(float r, float g, float b, float a) : color(r, g, b, a) {}
        Color(float r, float g, float b) : color(r, g, b, 1) {}
        Color(float _color[3]) : color(_color[0], _color[1], _color[2], _color[3]) {}
        //
        // ------- Destructor -------
        ~Color() {
            color.clear();
        }
        //
        // ------- GetColor START -------
        EcliptIHandlers::IColorHandler getColor() {
            EcliptIHandlers::IColorHandler c = {
                color.getX(),
                color.getY(),
                color.getZ(),
                color.getW()
            };

            return c;
        }
        // ------- GetColor END -------
    private:
        QTX::Quaternion color;
    };
}