#include "hash_table.hpp"
#include "dummy_vector.hpp"

template <typename key, typename value>
hash_table<key, value>::~hash_table(){}

template <typename key, typename value>
void hash_table<key, value>::clear(){
    delete table;
    table = dummy_vector<pair>;
    used_size = 0;
}

template <typename key, typename value>
size_t hash_table<key, value>::size() const{
    return used_size;
}

template <typename key, typename value>
bool hash_table<key, value>::empty() const{
    return used_size == 0;
}