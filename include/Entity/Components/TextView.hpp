#pragma once

#include "Headers/Headers.hpp"
#include "Entity/Component/Component.hpp"
#include "QTX/Ivecs/Ivec2.hpp"

namespace Eclipt
{
    class TextView : public Component
    {
    public:
        TextView();
        ~TextView();

        void onStart() override;
        void onRender() override;
    private:
    
    };
}
