#pragma once

#include "raylib.h"

namespace Core {

    struct RigidBodyComponent {
        Vector2 velocity;
        Vector2 acceleration;
    };

} // namespace core