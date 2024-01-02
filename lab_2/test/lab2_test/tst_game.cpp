#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "game.h"

using namespace testing;

TEST(game, game)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

