#pragma once

#include "Headers/Headers.hpp"
#include "Entity/Component/Component.hpp"
#include "QTX/Color/Color.hpp"

namespace Eclipt
{
    namespace Components
    {
        class Color : public Component
        {
        public:
            Color();

            void onStart() override;
            void onRender() override;

            void setBackgroundColor(QTX::Color color);
            void setBackgroundColor(float r, float b, float g, float a);
            void setBackgroundColor(float r, float g, float b);
            void setBackgroundColor(std::string hex);

            std::unordered_map<std::string, std::variant<QTX::Color, std::string>> getBackgroundColor();

        private:
            std::unordered_map<std::string, QTX::Color> colors;
        };
    }
}