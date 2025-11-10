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
        Eclipt::QTX::Vec3 position;
        Eclipt::QTX::Vec3 rotation;
        Eclipt::QTX::Vec3 scale;

        std::unordered_map<std::string, QTX::Color> colors;
    };
}