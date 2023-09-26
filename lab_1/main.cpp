#include "hash_table.hpp"

int main(){
    int a = 1;
    {
        dummy_vector<int> vec;
        for(int i = 0; i < 13; i++){
            vec.push_back(i);
        }
        for(int i = 13; i < 65; i++){
            vec.push_back(i);
        }
        for(int i = 0; i < 65; i++){
            vec[i] += 10;
            std::cout << vec[i];
        }
    char b = 'z';
    }
    int z = 123;
}
