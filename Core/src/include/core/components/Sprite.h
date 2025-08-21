#pragma once

#include "raylib.h"
#include <memory>

namespace Core {

    struct SpriteComponent {
        // Using shared_ptr for texture to allow multiple sprites to share the same texture resource
        std::shared_ptr<Texture2D> texture;
        Color tint;
    };

} // namespace core