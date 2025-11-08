#include "Headers/Headers.hpp"

class Shader {
public:
    Shader();
    ~Shader();
    
    void loadShader(const std::string &shader, ShaderType type);
    void compile();
};