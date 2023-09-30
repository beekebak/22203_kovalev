#include "hash_table.hpp"

int main(){
    hash_table test;
    hash_table second;
    hash_table third;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 11; j++){
            test.insert(std::string("test") + std::string(i+1, 'a'+j), value(18, 70+i*12+j, 150+i*12+j));
            std::cout << test[std::string("test") + std::string(i+1, 'a'+j)].weight << std::endl;
        }
    }
    second = test;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 11; j++){
            std::cout << second[std::string("test") + std::string(i+1, 'a'+j)].weight << std::endl;
        }
    }
}