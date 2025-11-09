#include "Entity/Entity.hpp"

namespace Eclipt
{
    Entity::Entity() : position(0, 0, 0),
                       rotation(0, 0, 0),
                       scale(0, 0, 0)
    {
    }

    Entity::~Entity()
    {
    }

    void Entity::draw()
    {
    }
}