#include "Headers/Headers.hpp"

namespace Eclipt
{
    class Shader
    {
    public:
        Shader();
        ~Shader();

        void loadShader(const std::string &shader, Eclipt::Enums::ShaderType type);
        void compile();
    };
}