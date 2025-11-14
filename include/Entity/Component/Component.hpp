#pragma once

namespace Eclipt
{
    class Component
    {
    public:
        void start();
        void render();

        virtual void onStart() {}
        virtual void onRender() {}
    };
}