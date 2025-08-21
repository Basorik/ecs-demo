#include <gtest/gtest.h>
#include "core/EntityManager.h"

TEST(EntityManagerTest, CreateAndDestroyEntity) {
    Core::EntityManager entityManager;

    Core::Entity entity1 = entityManager.createEntity();
    EXPECT_EQ(entity1, 0);

    Core::Entity entity2 = entityManager.createEntity();
    EXPECT_EQ(entity2, 1);

    entityManager.destroyEntity(entity1);

    Core::Entity entity3 = entityManager.createEntity();
    EXPECT_EQ(entity3, 0);
}

TEST(EntityManagerTest, SetAndGetSignature) {
    Core::EntityManager entityManager;
    Core::Entity entity = entityManager.createEntity();

    Core::Signature signature;
    signature.set(1, true);
    signature.set(5, true);

    entityManager.setSignature(entity, signature);

    Core::Signature returnedSignature = entityManager.getSignature(entity);
    EXPECT_EQ(signature, returnedSignature);
}
