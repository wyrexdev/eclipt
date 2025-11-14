#include "Entity/Entity.hpp"

namespace Eclipt
{
    Entity::Entity() : position(0, 0, 0),
                       rotation(0, 0, 0),
                       scale(0, 0, 0)
    {
        QTX::Color backgroundColor = QTX::Color(255, 255, 255, 1);
        colors.insert({"backgroundColor", backgroundColor});

        for(Eclipt::Component comp : components) {
            comp.start();
        }
    }

    Entity::~Entity()
    {
        colors.clear();
        components.clear();
    }

    void Entity::draw()
    {
        for(Eclipt::Component comp : components) {
            comp.render();
        }
    }
}