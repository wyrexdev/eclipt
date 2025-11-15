#pragma once

#include "Entity/Entity.hpp"

namespace Eclipt
{
    class Entity;
    
    class Component
    {
    public:
        ~Component();

        void start();
        void render();

        virtual void onStart() {}
        virtual void onRender() {}

        void setEntity(Eclipt::Entity *e);
        Eclipt::Entity *getEntity();

    private:
        Eclipt::Entity *entity;
    };
}