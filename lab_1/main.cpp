#include "hash_table.hpp"
#include "googletest/googletest/include/gtest/gtest.h"


TEST(hash_table_test, Constructors){
    hash_table first;
    ASSERT_TRUE(first.empty());
    hash_table second;
    ASSERT_TRUE(first == second);
    second.insert(std::string("abgriz"), value(20,100,100));
    hash_table third(second);
    hash_table fourth(std::move(second));
    ASSERT_TRUE(third == fourth);
    ASSERT_TRUE(second.empty());
    ASSERT_TRUE(third != first);
    hash_table fifth = hash_table();
    hash_table sixth = third;
    ASSERT_TRUE(fifth.empty());
    ASSERT_TRUE(sixth == third);
}

/*TEST(hash_table_test, presence&adding operators){
    hash_table first_t2;
    for(int i = 0; i < 1e4; i++){
        ASSERT_TRUE(first_t2.insert(std::to_string(i), value(i,i,i)));
        ASSERT_TRUE(first_t2.contains(value(i,i,i)));
        value temp = first_t2[std::to_string(i)];
        ASSERT_TRUE(temp == first_t2.at(value(i,i,i)));
        first_t2[std::to_string(i)] = value(1,2,3);
        temp = first_t2[std::to_string(i)];
        ASSERT_TRUE(temp == value(1,2,3));
    }
    const hash_table second_t2;
    ASSERT_ANY_THROW(second.at("arbuz"));
    const hash_table third(first_t2);
    ASSERT_NO_THROW(third.at(std::to_string(1)));
    for(int i = 0; i < 1e4; i++){
        ASSERT_TRUE(first_t2.erase(std::to_string(i)));
        ASSERT_ANY_THROW(first_t2.at(std::to_string(i)));
        ASSERT_FALSE(first_t2.contains(std::to_string(i)));
        temp = first_t2[std::to_string(i)];
        ASSERT_NO_THROW(first_t2.at(std::to_string(i)));
    }
}*/

int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


