#include "Entity/Components/Transform.hpp"

namespace Eclipt
{
    namespace Components
    {
        Transform::Transform() : position(0, 0, 0), rotation(0, 0, 0), scale(0, 0, 0)
        {
        }

        void Transform::onStart()
        {
        }

        void Transform::onRender()
        {
            getEntity()->position = position;
            getEntity()->scale = scale;
            getEntity()->rotation = rotation;
        }

        void Transform::setPosition(QTX::Vec3 pos)
        {
            position = pos;
        }

        QTX::Vec3 Transform::getPosition()
        {
            return position;
        }

        void Transform::setRotation(QTX::Vec3 rot)
        {
            rotation = rot;
        }

        QTX::Vec3 Transform::getRotation()
        {
            return rotation;
        }

        void Transform::setScale(QTX::Vec3 scale)
        {
            this->scale = scale;
        }

        QTX::Vec3 Transform::getScale()
        {
            return scale;
        }
    }
}