#include "hash_table.hpp"
#include <gtest/gtest.h>

TEST(hash_table_test, Constructors){
    hash_table first;
    ASSERT_TRUE(first.empty()) << "YAY";
}

int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
