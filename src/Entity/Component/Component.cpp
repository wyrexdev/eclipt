#include "Entity/Component/Component.hpp"

namespace Eclipt
{
    Component::~Component() {

    }

    void Component::start() {
        onStart();
    }

    void Component::render() {
        onRender();
    }

    void Component::setEntity(Eclipt::Entity *e) {
        entity = e;
    }

    Eclipt::Entity *Component::getEntity() {
        return entity;
    }
}