#include <gtest/gtest.h>
#include "core/Utils.h"

TEST(RandomTest, FloatReturnsValueInRange) {
    Utils::Random::Init();
    for (int i = 0; i < 100; ++i) {
        float val = Utils::Random::Float();
        EXPECT_GE(val, 0.0f);
        EXPECT_LE(val, 1.0f);
    }
}
