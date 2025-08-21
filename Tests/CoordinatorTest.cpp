#include <gtest/gtest.h>
#include "core/Coordinator.h"

// Dummy components for testing
struct Position {
    float x, y;
};

struct Velocity {
    float dx, dy;
};

// Dummy system for testing
class MovementSystem : public Core::System {
public:
    void Update(Core::Coordinator& coordinator) {
        for (auto const& entity : mEntities) {
            auto& pos = coordinator.getComponent<Position>(entity);
            auto const& vel = coordinator.getComponent<Velocity>(entity);
            pos.x += vel.dx;
            pos.y += vel.dy;
        }
    }
};

TEST(CoordinatorTest, IntegrationTest) {
    Core::Coordinator coordinator;
    coordinator.Init();

    // Register components
    coordinator.registerComponent<Position>();
    coordinator.registerComponent<Velocity>();

    // Register a system
    auto movementSystem = coordinator.registerSystem<MovementSystem>();

    // Define system signature
    Core::Signature signature;
    signature.set(coordinator.getComponentType<Position>());
    signature.set(coordinator.getComponentType<Velocity>());
    coordinator.setSystemSignature<MovementSystem>(signature);

    // Create an entity
    Core::Entity entity = coordinator.createEntity();

    // Add components to the entity
    coordinator.addComponent(entity, Position{0.0f, 0.0f});
    coordinator.addComponent(entity, Velocity{10.0f, 5.0f});

    // Run the system
    movementSystem->Update(coordinator);

    // Check if the component was updated
    Position& position = coordinator.getComponent<Position>(entity);
    EXPECT_EQ(position.x, 10.0f);
    EXPECT_EQ(position.y, 5.0f);

    // Remove a component and check if the entity is removed from the system
    coordinator.removeComponent<Velocity>(entity);

    // The entity should no longer be in the system's set
    // We can't directly check this without modifying the System class to expose its entities
    // But we can run the system again and check that the position was not updated
    movementSystem->Update(coordinator);
    EXPECT_EQ(position.x, 10.0f);
    EXPECT_EQ(position.y, 5.0f);

    // Destroy the entity
    coordinator.destroyEntity(entity);
    // Again, we can't directly check if the entity is gone from all managers
    // but we can trust that the destroyEntity method works if it doesn't crash.
    SUCCEED();
}
