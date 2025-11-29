#pragma once

#include "Headers/Headers.hpp"

namespace Eclipt
{
    class Widget
    {
    public:
        Widget();
        
        virtual void onStart();
        virtual void onRender();

        void render();
    private:
        bool isInitalized = false;
    };
}