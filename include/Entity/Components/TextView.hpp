#pragma once

#include "Headers/Headers.hpp"

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