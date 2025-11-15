#include "Entity/Components/Color.hpp"

namespace Eclipt
{
    Color::Color()
    {
    }

    void Color::onStart()
    {
           getEntity()->colors = colors;
    }

    void Color::onRender()
    {
        getEntity()->colors = colors;
    }

    void Color::setBackgroundColor(QTX::Color bgColor)
    {
        colors.insert_or_assign("backgroundColor", bgColor);
    }

    void Color::setBackgroundColor(float r, float b, float g, float a)
    {
        colors.insert_or_assign("backgroundColor", QTX::Color(r, g, b, a));
    }

    void Color::setBackgroundColor(float r, float b, float g)
    {
        colors.insert_or_assign("backgroundColor", QTX::Color(r, g, b, 1.0f));
    }

    void Color::setBackgroundColor(std::string hex)
    {
        QTX::Color bgColor(1, 1, 1, 1);
        bgColor.setColor(hex);

        colors.insert_or_assign("backgroundColor", bgColor);
    }

    std::unordered_map<std::string, std::variant<QTX::Color, std::string>> Color::getBackgroundColor()
    {
        std::unordered_map<std::string, std::variant<QTX::Color, std::string>> c;

        QTX::Color backgroundColor = colors.at("backgroundColor");

        c.insert_or_assign("hexColor", backgroundColor.getHexColor());
        c.insert_or_assign("rgbaColor", backgroundColor.getColor());

        return c;
    }
}