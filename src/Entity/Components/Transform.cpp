#include "Entity/Components/Transform.hpp"

namespace Eclipt
{
    void Transform::setPosition(QTX::Vec3 pos) {
        position = pos;
    }

    QTX::Vec3 Transform::getPosition() {
        return position;
    }

    void Transform::setRotation(QTX::Vec3 rot) {
        rotation = rot;
    }

    QTX::Vec3 Transform::getRotation() {
        return rotation;
    }

    void Transform::setScale(QTX::Vec3 scale) {
        this->scale = scale;
    }

    QTX::Vec3 Transform::getScale() {
        return scale;
    }
}