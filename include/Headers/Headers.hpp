#pragma once

#define GLFW_INCLUDE_NONE
#include "Utils/Glad/Glad.h"

#include <string>
#include <memory>
#include <iostream>
#include <cmath>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>

#include <GLFW/glfw3.h>

#include "Entity/Component/Component.hpp"

#include "Utils/Enums/Enums.hpp"
#include "Utils/Structs/Structs.hpp"
#include "Utils/Shader/Shader.hpp"

#include "QTX/Quaternion/Quaternion.hpp"
#include "QTX/Vectors/Vec2.hpp"
#include "QTX/Vectors/Vec3.hpp"
#include "QTX/Color/Color.hpp"

#include "Entity/Entity.hpp"