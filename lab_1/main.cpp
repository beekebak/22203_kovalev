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

TEST(hash_table_test, presence_insertion_operators){
    hash_table first;
    value temp;
    for(int i = 1; i < 1e3; i++){
        temp = value(i,i,i);
        ASSERT_TRUE(first.insert(std::to_string(i), temp));
        ASSERT_TRUE(first.contains(std::to_string(i)));
        value other_temp = first[std::to_string(i)];
        ASSERT_TRUE(other_temp == first.at(std::to_string(i)));
        first[std::to_string(i)] = value(1,2,3);
        temp = first[std::to_string(i)];
        ASSERT_TRUE(temp == value(1,2,3));
    }
    const hash_table second;
    ASSERT_ANY_THROW(second.at(std::string("arbuz")));
    const hash_table third(first);
    ASSERT_NO_THROW(third.at(std::to_string(1)));
    for(int i = 1; i < 1e3; i++){
        ASSERT_TRUE(first.erase(std::to_string(i)));
        ASSERT_ANY_THROW(first.at(std::to_string(i)));
        ASSERT_FALSE(first.contains(std::to_string(i)));
    }
    ASSERT_FALSE(first.erase(std::string("unused")));
    temp = value(0,0,0);
    ASSERT_TRUE(first[std::string("more_unused")] == temp);
    ASSERT_ANY_THROW(first.at(std::string("unused")));
}

TEST(hash_table_test, size_and_swap){
    hash_table first;
    value temp;
    ASSERT_EQ(first.size(), 0);
    ASSERT_TRUE(first.empty());
    for(int i = 1; i < 1e3; i++){
        temp = value(i,i,i);
        first.insert(std::to_string(i), temp);
    }
    ASSERT_EQ(first.size(), 1000-1);
    hash_table second;
    second.swap(first);
    ASSERT_EQ(first.size(), 0);
    ASSERT_EQ(second.size(), 1000-1);
    for(int i = 1; i < 1e3; i++){
        ASSERT_TRUE(second.contains(std::to_string(i)));
    }
    second.clear();
    ASSERT_TRUE(first.empty());
    ASSERT_EQ(second.size(), 0);
    for(int i = 1; i < 1e3; i++){
        ASSERT_FALSE(second.contains(std::to_string(i)));
    }
}

TEST(hash_table_test, assignment){
    hash_table first;
    hash_table second;
    for(int i = 1; i < 1e3; i++){
        value temp(i, i, i);
        first.insert(std::to_string(i), temp);
    }
    second = first;
    ASSERT_TRUE(first == second);
}

void foo(){return;}
int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


