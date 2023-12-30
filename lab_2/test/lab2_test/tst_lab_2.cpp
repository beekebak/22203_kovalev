#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

TEST(lab_2, lab_2)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

