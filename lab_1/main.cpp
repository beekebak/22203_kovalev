#include "hash_table.hpp"

int main(){
    hash_table test;
    hash_table second;
    std::cout << "oh no";
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 26; j++){
            test.insert(std::string("test") + std::string(i, 'a'+j), value());
        }
    }
    for(int i = 0; i < 6; i++){
        for(int j = 25; j >= 0; j--){
            second.insert(std::string("test") + std::string(i, 'a'+j), value());
        }
    }
    if(test != second){
        std::cout << "YES";
    }
}
