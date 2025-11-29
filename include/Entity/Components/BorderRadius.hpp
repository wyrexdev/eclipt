#pragma once

#include "Headers/Headers.hpp"

#include "Entity/Component/Component.hpp"

namespace Eclipt
{
    namespace Components
    {
        class BorderRadius : public Component
        {
        public:
            void onStart() override;
            void onRender() override;

            void setBorder(Eclipt::Enums::BorderType type);

            void setBorderRadius(float degress);
            void setBorderThickness(float thickness);

            void setLeftBorderRadius(float degress);
            void setLeftTopBorderRadius(float degress);
            void setLeftBottomBorderRadius(float degress);

            void setRightBorderRadius(float degress);
            void setRightTopBorderRadius(float degress);
            void setRightBottomBorderRadius(float degress);

            void setBorderRadius(Eclipt::IHandlers::IBorderRadiusHandler borderRadius);

            Eclipt::IHandlers::IBorderRadiusHandler getBorderRadius();

        private:
            Eclipt::IHandlers::IBorderRadiusHandler borderRadius;
            
            float thickness = 0;
        };
    }
}