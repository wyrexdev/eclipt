#include "Utils/Shader/Shader.hpp"

namespace Eclipt
{
    Shader::Shader()
    {
    }

    Shader::~Shader()
    {
    }

    std::string Shader::loadShader(std::string path)
    {
        std::ifstream file(path);
        if (!file.is_open())
            return "";

        std::string content;
        std::string line;

        content.reserve(2048);

        bool firstLine = true;

        while (std::getline(file, line))
        {
            if (!firstLine)
                content += '\n';
            firstLine = false;

            content += line;
        }

        return content;
    }

    void Shader::compile(const std::string &shader, Eclipt::Enums::ShaderType type)
    {
    }
}