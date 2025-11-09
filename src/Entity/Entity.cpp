#include "Entity/Entity.hpp"

namespace Eclipt
{
    Entity::Entity() : position(0, 0, 0),
                       rotation(0, 0, 0),
                       scale(0, 0, 0)
    {
        QTX::Color backgroundColor = QTX::Color(255, 255, 255, 1);
        colors.insert({"backgroundColor", backgroundColor});
    }

    Entity::~Entity()
    {
        colors.clear();
    }

    void Entity::draw()
    {
    }
}