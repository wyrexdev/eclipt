#include "Utils/Shader/Shader.hpp"

namespace Eclipt
{
    Shader::Shader()
    {
        ID = 0;
        vertexID = 0;
        fragmentID = 0;
    }

    Shader::~Shader()
    {
        if (ID)
            glDeleteProgram(ID);
        if (vertexID)
            glDeleteShader(vertexID);
        if (fragmentID)
            glDeleteShader(fragmentID);
    }

    // ------------------------ Shader Load ------------------------
    std::string Shader::loadShader(const std::string &path)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            std::cout << "Failed to load shader: " << path << std::endl;
            return "";
        }

        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    // ------------------------ Shader Compile ------------------------
    void Shader::compile(const std::string &source, Eclipt::Enums::ShaderType type)
    {
        unsigned int shader = 0;

        if (type == Enums::ShaderType::vertexShader)
            shader = glCreateShader(GL_VERTEX_SHADER);
        else if (type == Enums::ShaderType::fragmentShader)
            shader = glCreateShader(GL_FRAGMENT_SHADER);

        const char *code = source.c_str();
        glShaderSource(shader, 1, &code, nullptr);
        glCompileShader(shader);

        // Check errors
        int success;
        char infoLog[1024];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "Shader compilation error: " << infoLog << std::endl;
        }

        if (type == Enums::ShaderType::vertexShader)
            vertexID = shader;
        else if (type == Enums::ShaderType::fragmentShader)
            fragmentID = shader;
    }

    // ------------------------ Shader Link ------------------------
    void Shader::link()
    {
        ID = glCreateProgram();
        glAttachShader(ID, vertexID);
        glAttachShader(ID, fragmentID);
        glLinkProgram(ID);

        int success;
        char infoLog[1024];
        glGetProgramiv(ID, GL_LINK_STATUS, &success);

        if (!success)
        {
            glGetProgramInfoLog(ID, 1024, nullptr, infoLog);
            std::cout << "Shader Linking Failed: " << infoLog << std::endl;
        }

        glDeleteShader(vertexID);
        glDeleteShader(fragmentID);

        vertexID = 0;
        fragmentID = 0;
    }

    // ------------------------ Use Shader ------------------------
    void Shader::use()
    {
        glUseProgram(ID);
    }

    // ------------------------ Uniforms ------------------------
    void Shader::setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void Shader::setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void Shader::setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void Shader::setVec3(const std::string &name, const Eclipt::QTX::Vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value.x);
    }

    void Shader::setMat4(const std::string &name, const Eclipt::QTX::Mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat.m[0][0]);
    }

}
