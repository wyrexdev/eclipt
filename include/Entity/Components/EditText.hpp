#pragma once

#include "Headers/Headers.hpp"
#include "Entity/Component/Component.hpp"

#include "Entity/Components/Transform.hpp"
#include "Entity/Components/TextView.hpp"

namespace Eclipt
{
    class EditText : public Component {
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

        Transform *transform;
    };
}