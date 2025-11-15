#pragma once

#include "Headers/Headers.hpp"
#include "Entity/Entity.hpp"
#include "QTX/Vectors/Vec3.hpp"

namespace Eclipt
{
    class Transform : public Component
    {
    public:
        Transform();
        
        void onStart() override;
        void onRender() override;

        void setPosition(QTX::Vec3 pos);
        QTX::Vec3 getPosition();

        void setRotation(QTX::Vec3 rot);
        QTX::Vec3 getRotation();

        void setScale(QTX::Vec3 scale);
        QTX::Vec3 getScale();

    private:
        QTX::Vec3 position;
        QTX::Vec3 rotation;
        QTX::Vec3 scale;
    };
}