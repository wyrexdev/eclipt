#include "Core/Widgets/EditText/EditText.hpp"

namespace Eclipt
{
    namespace Widgets
    {
        EditText::EditText()
        {
            hint = "";
            text = "";

            isEnabled = true;
            isFocused = false;
        }

        void EditText::onStart()
        {
            border = new Entity();
            textView = new Entity();

            transform = new Eclipt::Components::Transform();
            transform->setScale(QTX::Vec3(0.05f, 0.001f, 0.0f));

            textViewComp = new Eclipt::Components::TextView("Hello World", "fonts/nunito.ttf", 24, 64);
            textViewComp->setFontSize(100);

            border->addComponent(transform);
        }

        void EditText::onRender()
        {
            border->draw();
        }
    }
}