#pragma once

#include "Headers/Headers.hpp"

#include "Entity/Component/Component.hpp"

namespace Eclipt {
    namespace Components
    {
        class TextView : Component {
            TextView();
            ~TextView();

            void onStart() override;
            void onRender() override;
        };
    }
}