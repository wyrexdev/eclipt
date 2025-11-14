#pragma once

#include "Headers/Headers.hpp"

#include "Utils/Enums/Enums.hpp"

namespace Eclipt
{
    class Shader
    {
    public:
        Shader();
        ~Shader();

        std::string loadShader(std::string path);
        void compile(const std::string &shader, Eclipt::Enums::ShaderType type);
    };
}