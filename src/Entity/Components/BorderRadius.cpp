#include "Entity/Components/BorderRadius.hpp"

namespace Eclipt
{
    namespace Components
    {
        void BorderRadius::onStart()
        {
        }

        void BorderRadius::onRender()
        {
            glUniform1f(glGetUniformLocation(getEntity()->shaderProgram, "radiusTL"), borderRadius.leftTop);
            glUniform1f(glGetUniformLocation(getEntity()->shaderProgram, "radiusTR"), borderRadius.rightTop);
            glUniform1f(glGetUniformLocation(getEntity()->shaderProgram, "radiusBL"), borderRadius.leftBottom);
            glUniform1f(glGetUniformLocation(getEntity()->shaderProgram, "radiusBR"), borderRadius.rightBottom);

            glUniform1f(glGetUniformLocation(getEntity()->shaderProgram, "borderSize"), thickness);
            glUniform4f(glGetUniformLocation(getEntity()->shaderProgram, "borderColor"), 1, 1, 1, 1);
            glUniform1i(glGetUniformLocation(getEntity()->shaderProgram, "drawBorder"), true);
        }

        void BorderRadius::setBorder(Eclipt::Enums::BorderType type)
        {
        }

        void BorderRadius::setBorderThickness(float th) {
            thickness = th;
        }

        void BorderRadius::setBorderRadius(float degress)
        {
            borderRadius.leftBottom = degress;
            borderRadius.leftTop = degress;
            borderRadius.rightBottom = degress;
            borderRadius.rightTop = degress;
        }

        void BorderRadius::setLeftBorderRadius(float degress)
        {
            borderRadius.leftBottom = degress;
            borderRadius.leftTop = degress;
        }

        void BorderRadius::setRightBorderRadius(float degress)
        {
            borderRadius.rightBottom = degress;
            borderRadius.rightTop = degress;
        }

        void BorderRadius::setLeftBottomBorderRadius(float degress)
        {
            borderRadius.leftBottom = degress;
        }

        void BorderRadius::setLeftTopBorderRadius(float degress)
        {
            borderRadius.leftTop = degress;
        }

        void BorderRadius::setRightBottomBorderRadius(float degress)
        {
            borderRadius.rightBottom = degress;
        }

        void BorderRadius::setRightTopBorderRadius(float degress)
        {
            borderRadius.rightTop = degress;
        }

        void BorderRadius::setBorderRadius(Eclipt::IHandlers::IBorderRadiusHandler borderRadius)
        {
            this->borderRadius = borderRadius;
        }

        Eclipt::IHandlers::IBorderRadiusHandler BorderRadius::getBorderRadius()
        {
            return borderRadius;
        }
    }
}