#pragma once

#include "raylib.h"

namespace Core {

    struct TransformComponent {
        Vector2 position;
        Vector2 rotation;
        Vector2 scale;
        // Add rotation and scale here if needed
    };

} // namespace core