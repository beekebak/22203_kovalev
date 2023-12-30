#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "choose_table.h"

using namespace testing;

TEST(ChooseTable, ChooseTableCreation)
{
    EXPECT_ANY_THROW(ChooseTable("FOO"));
    EXPECT_NO_THROW(ChooseTable("/home/beekebak/main/table.json"));
}

