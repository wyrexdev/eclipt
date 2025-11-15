#include "Entity/Components/Color.hpp"

namespace Eclipt {
    Color::Color() {

    }

    void Color::onStart() {

    }

    void Color::onRender() {
        
    }

    void Color::setBackgroundColor(QTX::Color bgColor) {
        getEntity()->colors.insert_or_assign("backgroundColor", bgColor);
    }

    void Color::setBackgroundColor(float r, float b, float g, float a) {
        getEntity()->colors.insert_or_assign("backgroundColor", QTX::Color(r, g, b, a));
    }

    void Color::setBackgroundColor(float r, float b, float g) {
        getEntity()->colors.insert_or_assign("backgroundColor", QTX::Color(r, g, b, 1.0f));
    }

    void Color::setBackgroundColor(std::string hex) {
        QTX::Color bgColor(1, 1, 1, 1);
        bgColor.setColor(hex);

        getEntity()->colors.insert_or_assign("backgroundColor", bgColor);
    }

    std::unordered_map<std::string, std::variant<QTX::Color, std::string>> Color::getBackgroundColor() {
        QTX::Color backgroundColor = getEntity()->colors.at("backgroundColor");
        std::unordered_map<std::string, std::variant<QTX::Color, std::string>> colors;

        colors.insert_or_assign("hexColor", backgroundColor.getHexColor());
        colors.insert_or_assign("rgbaColor", backgroundColor.getColor());

        return colors;
    }
}