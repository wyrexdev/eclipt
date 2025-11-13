#pragma once

namespace Eclipt {
    class Component {
        void start();
        void render();

        virtual void onStart() = 0;
        virtual void onRender() = 0;
    };
}