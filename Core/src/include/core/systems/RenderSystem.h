#pragma once

#include "../ECS.h"


namespace Core {

    class RenderSystem : public System {
    public:
        // The update function no longer needs a window reference
        void update(int width, int height);
    };

} // namespace core