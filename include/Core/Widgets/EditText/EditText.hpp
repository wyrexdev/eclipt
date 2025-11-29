#pragma once

#include "Headers/Headers.hpp"

#include "Core/Widgets/Widget.hpp"

#include "Entity/Components/Transform.hpp"
#include "Entity/Components/TextView.hpp"
#include "Entity/Components/BorderRadius.hpp"

namespace Eclipt
{
    namespace Widgets
    {
        class EditText : public Widget
        {
        public:
            EditText();

            void onStart() override;
            void onRender() override;

            bool isFocused = false;
            bool isEnabled = true;

            std::string text = "";
            std::string hint = "";

        private:
            Entity *border;
            Entity *textView;

            Eclipt::Components::TextView *textViewComp;

            Eclipt::Components::Transform *transform;
        };
    }
}