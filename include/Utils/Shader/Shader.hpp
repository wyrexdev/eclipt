#pragma once

#include "Headers/Headers.hpp"
#include "Utils/Enums/Enums.hpp"

#include "QTX/Matris/Mat4.hpp"
#include "QTX/Vectors/Vec3.hpp"

namespace Eclipt
{
    class Shader
    {
    public:
        unsigned int ID;

        Shader();
        ~Shader();

        std::string loadShader(const std::string& path);

        void compile(const std::string& source, Eclipt::Enums::ShaderType type);
        void link();
        void use();

        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setVec3(const std::string& name, const Eclipt::QTX::Vec3& value) const;
        void setMat4(const std::string& name, const Eclipt::QTX::Mat4& mat) const;

    private:
        unsigned int vertexID;
        unsigned int fragmentID;
    };
}
