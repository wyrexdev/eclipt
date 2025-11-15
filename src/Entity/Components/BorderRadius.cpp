#include "Entity/Components/BorderRadius.hpp"

namespace Eclipt
{
    void BorderRadius::onStart() {

    }

    void BorderRadius::onRender() {
        glUniform1f(glGetUniformLocation(getEntity()->shaderProgram, "radiusTL"), borderRadius.leftTop);
        glUniform1f(glGetUniformLocation(getEntity()->shaderProgram, "radiusTR"), borderRadius.rightTop);
        glUniform1f(glGetUniformLocation(getEntity()->shaderProgram, "radiusBL"), borderRadius.leftBottom);
        glUniform1f(glGetUniformLocation(getEntity()->shaderProgram, "radiusBR"), borderRadius.rightBottom);
    }

    void BorderRadius::setBorderRadius(float degress) {
        borderRadius.leftBottom = degress;
        borderRadius.leftTop = degress;
        borderRadius.rightBottom = degress;
        borderRadius.rightTop = degress;
    }

    void BorderRadius::setLeftBorderRadius(float degress) {
        borderRadius.leftBottom = degress;
        borderRadius.leftTop = degress;
    }

    void BorderRadius::setRightBorderRadius(float degress) {
        borderRadius.rightBottom = degress;
        borderRadius.rightTop = degress;
    }

    void BorderRadius::setLeftBottomBorderRadius(float degress) {
        borderRadius.leftBottom = degress;
    }

    void BorderRadius::setLeftTopBorderRadius(float degress) {
        borderRadius.leftTop = degress;
    }

    void BorderRadius::setRightBottomBorderRadius(float degress) {
        borderRadius.rightBottom = degress;
    }

    void BorderRadius::setRightTopBorderRadius(float degress) {
        borderRadius.rightTop = degress;
    }

    void BorderRadius::setBorderRadius(Eclipt::IHandlers::IBorderRadiusHandler borderRadius) {
        this->borderRadius = borderRadius;
    }

    Eclipt::IHandlers::IBorderRadiusHandler BorderRadius::getBorderRadius() {
        return borderRadius;
    }
}