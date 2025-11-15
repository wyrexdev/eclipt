#pragma once

#include "Headers/Headers.hpp"

#include "Utils/Structs/Structs.hpp"

#include "QTX/Quaternion/Quaternion.hpp"
#include "QTX/Vectors/Vec2.hpp"
#include "QTX/Vectors/Vec3.hpp"

namespace Eclipt
{
    namespace QTX
    {
        class Color
        {
        public:
            // ------- Constructor -------
            Color(float r, float g, float b, float a) : color(r, g, b, a) {}
            Color(float r, float g, float b) : color(r, g, b, 1) {}
            Color(float _color[3]) : color(_color[0], _color[1], _color[2], _color[3]) {}
            Color(Eclipt::IHandlers::IColorHandler _color) : color(_color.r, _color.g, _color.b, _color.a) {}
            //
            // ------- Destructor -------
            ~Color()
            {
                color.clear();
            }
            //
            // ================== FUNCTIONS START ==================
            //
            // ------- GetColor START -------
            Eclipt::IHandlers::IColorHandler getColor()
            {
                Eclipt::IHandlers::IColorHandler c = {
                    color.getX(),
                    color.getY(),
                    color.getZ(),
                    color.getW()};

                return c;
            }
            //
            std::string getHexColor()
            {
                auto toHex = [](float v)
                {
                    int val;

                    if (v <= 1.0f)
                        val = std::round(v * 255.0f);
                    else
                        val = static_cast<int>(v);

                    char buf[3];
                    snprintf(buf, sizeof(buf), "%02X", val);
                    return std::string(buf);
                };

                float r = color.getX();
                float g = color.getY();
                float b = color.getZ();
                float a = color.getW();

                return toHex(r) + toHex(g) + toHex(b) + toHex(a);
            }
            // ------- GetColor END -------
            //
            // ------- SetColor START -------
            void setColor(std::string hex)
            {
                if (hex.empty())
                    return;
                if (hex[0] == '#')
                    hex.erase(0, 1);

                if (hex.size() < 6)
                    return;

                float r = std::stoi(hex.substr(0, 2), nullptr, 16) / 255.0f;
                float g = std::stoi(hex.substr(2, 2), nullptr, 16) / 255.0f;
                float b = std::stoi(hex.substr(4, 2), nullptr, 16) / 255.0f;

                float a = 1.0f;
                if (hex.size() >= 8)
                    a = std::stoi(hex.substr(6, 2), nullptr, 16) / 255.0f;

                color = QTX::Quaternion(r, g, b, a);
            }
            // ------- SetColor END -------
            //
            void setColor(float _color[3])
            {
                color = QTX::Quaternion(_color[0], _color[1], _color[2], _color[3]);
            }
            //
            void setColor(float r, float g, float b, float a)
            {
                color = QTX::Quaternion(r, g, b, a);
            }
            //
            void setColor(float r, float g, float b)
            {
                color = QTX::Quaternion(r, g, b, 1.0f);
            }
            //
            void setColor(Eclipt::IHandlers::IColorHandler _color)
            {
                color = QTX::Quaternion(_color.r, _color.g, _color.b, _color.a);
            }
            // ------- SetColor END -------
            //
            // ================== FUNCTIONS END ==================
        private:
            Eclipt::QTX::Quaternion color;
        };
    }
}