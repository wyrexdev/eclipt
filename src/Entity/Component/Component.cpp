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
}