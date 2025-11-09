#include "Headers/Headers.hpp"

namespace Eclipt
{
    class Entity
    {
    public:
        Entity();
        ~Entity();

        void draw();
    private:
        QTX::Vec3 position;
        QTX::Vec3 rotation;
        QTX::Vec3 scale;
    };
}