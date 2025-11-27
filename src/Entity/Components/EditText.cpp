#include "Entity/Components/EditText.hpp"

namespace Eclipt {
    EditText::EditText() {
        hint = "";
        text = "";

        isEnabled = true;
        isFocused = false;
    }

    void EditText::onStart() {
        editText = new Entity();
        transform = new Transform();
        textView = new TextView("Hello World", "fonts/nunito.ttf", 24, 64);
        
        transform->setScale(QTX::Vec3(0.05f, 0.001f, 0.0f));

        textView->setFontSize(100);

        editText->addComponent(transform);
        editText->addComponent(textView);
    }

    void EditText::onRender() {
        editText->draw();
    }
}