#include "Core/Widgets/Widget.hpp"

namespace Eclipt {
    Widget::Widget() {
        
    }

    void Widget::onStart() {

    }

    void Widget::onRender() {

    }
    
    void Widget::render() {
        if(!isInitalized) {
            onStart();
            isInitalized = true;
        }
    }
}