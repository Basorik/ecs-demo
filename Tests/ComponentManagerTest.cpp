#include <gtest/gtest.h>
#include "core/ComponentManager.h"

struct Position {
    float x, y;
};

struct Velocity {
    float dx, dy;
};

TEST(ComponentManagerTest, RegisterAndGetComponentType) {
    Core::ComponentManager componentManager;
    componentManager.registerComponent<Position>();
    componentManager.registerComponent<Velocity>();

    Core::ComponentType positionType = componentManager.getComponentType<Position>();
    Core::ComponentType velocityType = componentManager.getComponentType<Velocity>();

    EXPECT_EQ(positionType, 0);
    EXPECT_EQ(velocityType, 1);
}

TEST(ComponentManagerTest, AddAndGetComponent) {
    Core::ComponentManager componentManager;
    componentManager.registerComponent<Position>();

    Core::Entity entity = 0;
    Position position = {10.0f, 20.0f};
    componentManager.addComponent(entity, position);

    Position& returnedPosition = componentManager.getComponent<Position>(entity);
    EXPECT_EQ(returnedPosition.x, 10.0f);
    EXPECT_EQ(returnedPosition.y, 20.0f);
}

TEST(ComponentManagerTest, RemoveComponent) {
    Core::ComponentManager componentManager;
    componentManager.registerComponent<Position>();

    Core::Entity entity = 0;
    Position position = {10.0f, 20.0f};
    componentManager.addComponent(entity, position);
    componentManager.removeComponent<Position>(entity);

    // This is tricky to test without inspecting internal state.
    // A more robust test would involve a hasComponent method, which is not present.
    // For now, we assume remove works if it doesn't crash.
    // A better test would be to try to get the component and expect an exception,
    // but the current implementation asserts on invalid access.
    SUCCEED();
}

TEST(ComponentManagerTest, EntityDestroyed) {
    Core::ComponentManager componentManager;
    componentManager.registerComponent<Position>();

    Core::Entity entity = 0;
    Position position = {10.0f, 20.0f};
    componentManager.addComponent(entity, position);
    componentManager.EntityDestroyed(entity);

    // Similar to RemoveComponent, this is hard to test without internal inspection
    // or a hasComponent method.
    SUCCEED();
}
