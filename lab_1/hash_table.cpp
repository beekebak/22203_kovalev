#include "hash_table.hpp"

template <typename key, typename value>
hash_table<key, value>::hash_table(){
    used_size = 0;
    table = dummy_vector<pair>();
}

template <typename key, typename value>
hash_table<key, value>::~hash_table() = default;

template <typename key, typename value>
void hash_table<key, value>::clear(){
    delete table;
    table = dummy_vector<pair>();
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