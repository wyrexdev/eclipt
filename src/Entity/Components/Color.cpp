#include "Entity/Components/Color.hpp"

namespace Eclipt {
    std::unordered_map<std::string, std::variant<QTX::Color, std::string>> Color::getBackgroundColor() {
        getEntity().colors.at("backgroundColor");
    }
}