#include "hash_table.hpp"

int main(){
    int a = 1;
    {
        hash_table<std::string, int> table;
        if(table["asd"]){
            std::cout << "YES";
        }
        else{
            std::cout << "NO";
        }
    }
    std::cout << "DONE";
    int z = 123;
}
