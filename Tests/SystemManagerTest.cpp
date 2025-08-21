#include <gtest/gtest.h>
#include "core/SystemManager.h"

class TestSystem : public Core::System {
public:
    bool entityPresent(Core::Entity entity) {
        return mEntities.count(entity) > 0;
    }
};

TEST(SystemManagerTest, RegisterAndSetSignature) {
    Core::SystemManager systemManager;
    auto testSystem = systemManager.registerSystem<TestSystem>();
    ASSERT_NE(testSystem, nullptr);

    Core::Signature signature;
    signature.set(1, true);
    systemManager.setSignature<TestSystem>(signature);

    // Cannot get signature back, so this test is limited.
    // We mainly test that registration and setting signature don't crash.
    SUCCEED();
}

TEST(SystemManagerTest, EntitySignatureChanged) {
    Core::SystemManager systemManager;
    auto testSystem = systemManager.registerSystem<TestSystem>();

    Core::Signature systemSignature;
    systemSignature.set(1, true);
    systemManager.setSignature<TestSystem>(systemSignature);

    Core::Entity entity = 0;
    Core::Signature entitySignature;

    // Entity signature does not match system signature
    systemManager.entitySignatureChanged(entity, entitySignature);
    EXPECT_FALSE(testSystem->entityPresent(entity));

    // Entity signature matches system signature
    entitySignature.set(1, true);
    systemManager.entitySignatureChanged(entity, entitySignature);
    EXPECT_TRUE(testSystem->entityPresent(entity));

    // Entity signature no longer matches system signature
    entitySignature.set(1, false);
    systemManager.entitySignatureChanged(entity, entitySignature);
    EXPECT_FALSE(testSystem->entityPresent(entity));
}

TEST(SystemManagerTest, EntityDestroyed) {
    Core::SystemManager systemManager;
    auto testSystem = systemManager.registerSystem<TestSystem>();

    Core::Signature systemSignature;
    systemSignature.set(1, true);
    systemManager.setSignature<TestSystem>(systemSignature);

    Core::Entity entity = 0;
    Core::Signature entitySignature;
    entitySignature.set(1, true);
    systemManager.entitySignatureChanged(entity, entitySignature);
    EXPECT_TRUE(testSystem->entityPresent(entity));

    systemManager.entityDestroyed(entity);
    EXPECT_FALSE(testSystem->entityPresent(entity));
}
