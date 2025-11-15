#pragma once

#include "Entity/Entity.hpp"

namespace Eclipt
{
    class Component
    {
    public:
        Component(Eclipt::Entity e);
        ~Component();

        void start();
        void render();

        virtual void onStart() {}
        virtual void onRender() {}

        Eclipt::Entity getEntity();

    private:
        Eclipt::Entity entity;
    };
}