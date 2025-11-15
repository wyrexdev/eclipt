#pragma once

#include "Headers/Headers.hpp"

#include "Entity/Component/Component.hpp"

#include "Utils/Shader/Shader.hpp"

#include "QTX/Vectors/Vec3.hpp"
#include "QTX/Color/Color.hpp"

namespace Eclipt
{
    class Component;
    
    class Entity
    {
    public:
        Entity();
        ~Entity();

        void draw();
        void addComponent(Eclipt::Component *comp);

        Eclipt::QTX::Vec3 position;
        Eclipt::QTX::Vec3 rotation;
        Eclipt::QTX::Vec3 scale;

        std::unordered_map<std::string, QTX::Color> colors;
        std::vector<Eclipt::Component*> components;

    private:
        Eclipt::Shader shader;

        unsigned int shaderProgram;
        unsigned int VAO, VBO, EBO;
    };
}