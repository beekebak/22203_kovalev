#include "hash_table.hpp"

int main(){
    hash_table test;
    hash_table second;
    test[std::string("abgriz")] = value(1,1,1);
    second[std::string("abgriz")] = value(11,12,13);
    second[std::string("arbuz")] = value(4,15,61);
    if(test.contains(std::string("arbuz"))){
        std::cout << "YES";
    }
    else{
        std::cout << "NO";
    }
}