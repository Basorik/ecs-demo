#include "core/systems/RenderSystem.h"
#include "core/Coordinator.h"
#include "core/components/Transform.h"
#include "core/components/Sprite.h"
#include <raylib.h>
#include "core/Logger.h"
extern Core::Coordinator gCoordinator;
namespace Core {
    
    void RenderSystem::update(int width, int height) {
        // Iterate over all entities the system is interested in
        for (auto const& entity : mEntities) {
            // Get the components for the entity
            auto& transform = gCoordinator.getComponent<TransformComponent>(entity);
            auto& sprite = gCoordinator.getComponent<SpriteComponent>(entity);
            Vector2 position = { (transform.position.x / 100) * width, (transform.position.y / 100) * height };

            // Use the average of scale.x and scale.y for uniform scaling, or choose one axis
            float scale = (transform.scale.x / 100 * width + transform.scale.y / 100 * width) / 2.0f;

            // Draw the texture with scaling
            DrawTextureEx(*sprite.texture, position, 0.0f, scale, sprite.tint);
            // Draw the texture using Raylib's functions
            //DrawTextureV(*sprite.texture, { (transform.position.x / 100) * width, (transform.position.y / 100) * height }, sprite.tint);
            //DrawRectangleV({ (transform.position.x/100)*width, (transform.position.y/100)*height }, { transform.scale.x/100*width, transform.scale.y/100*width }, sprite.tint);
        }
    }

} // namespace core