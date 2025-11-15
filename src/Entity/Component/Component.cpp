#include "Entity/Component/Component.hpp"

namespace Eclipt
{
    Component::Component(Eclipt::Entity e) {
        entity = e;
    }

    Component::~Component() {

    }

    void Component::start() {
        onStart();
    }

    void Component::render() {
        onRender();
    }

    Eclipt::Entity Component::getEntity() {
        return entity;
    }
}