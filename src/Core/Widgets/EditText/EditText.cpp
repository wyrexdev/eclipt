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
            transform->setScale(QTX::Vec3(0.3f, 0.3f, 0.0f));

            border->addComponent(transform);

            Eclipt::Components::BorderRadius *b = new Eclipt::Components::BorderRadius();
            b->setBorderRadius(0.1f);
            b->setBorderThickness(0.005f);
            b->setBorder(Eclipt::Enums::BorderType::solid);

            border->addComponent(b);
                
            textViewComp = new Eclipt::Components::TextView("Hello World", "fonts/nunito.ttf", 24, 64);
            textViewComp->setFontSize(100);

            Eclipt::Components::Transform *tTransform = new Eclipt::Components::Transform();
            tTransform->setPosition(QTX::Vec3(0, 0, 0));
            tTransform->setScale(QTX::Vec3(0.1f, 0.1f, 0.0f));

            textView->addComponent(textViewComp);
            textView->addComponent(tTransform); 
        }

        void EditText::onRender()
        {
            textView->draw();
            border->draw();
        }
    }
}