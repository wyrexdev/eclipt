#pragma once

namespace Eclipt
{
    class Component
    {
    public:
        ~Component();
        
        void start();
        void render();

        virtual void onStart() {}
        virtual void onRender() {}
    };
}