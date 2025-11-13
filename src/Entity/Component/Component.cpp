#include "Entity/Component/Component.hpp"

namespace Eclipt
{
    void Component::start() {
        onStart();
    }

    void Component::render() {
        onRender();
    }
}