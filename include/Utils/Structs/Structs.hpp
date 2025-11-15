#pragma once

namespace Eclipt
{
    namespace IHandlers
    {
        struct IColorHandler
        {
            float r = 0;
            float g = 0;
            float b = 0;
            float a = 0;
        };

        struct IBorderRadiusHandler {
            float leftTop = 0;
            float leftBottom = 0;
            float rightTop = 0;
            float rightBottom = 0;
        };
    }
}