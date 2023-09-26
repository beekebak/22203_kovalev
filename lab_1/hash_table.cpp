#include "hash_table.hpp"
#include <typeinfo>

template <typename key, typename value>
hash_table<key, value>::hash_table() = default;

template <typename key, typename value>
hash_table<key, value>::~hash_table() = default;

template <typename key, typename value>
hash_table<key, value>::hash_table(const hash_table& b):table{b.table}, used_size{b.used_size}{}

template <typename key, typename value>
hash_table<key, value>::hash_table(const hash_table&& b):table{b.table}, used_size{b.used_size}{}


template <typename key, typename value>
hash_table<key, value>& hash_table<key, value>::operator=(const hash_table& b){
    used_size = b.used_size;
    table = b.table;
    return *this;
}

template <typename key, typename value>
void hash_table<key, value>::clear(){
    delete &table;
    table = dummy_vector<pair<key, value>>();
    used_size = 0;
}

template <typename key, typename value>
bool hash_table<key, value>::erase(const key& k){
    try{
        size_t idx = find(k);
        table[idx] = value();
        return true;
    }
    catch(std::string error){
        return false;
    }
}

template <typename key, typename value>
bool hash_table<key, value>::insert(const key& k, const value& v){
    if(static_cast<double>(table.get_size()) * 0.75 <static_cast<double>(used_size)){
        rehash();
    } 
    size_t index = string_hash(static_cast<std::string>(k), table.get_size());
    for(int i = 0; i < table.get_size(); i++){
        if(!table[(index+i) % table.get_size()]){
            table[(index+i) % table.get_size()] = {k, v};
            used_size++;
            return true;
        }
    }
    return false;
}

template <typename key, typename value>
bool hash_table<key, value>::contains(const key& k) const{
    try{
        find(k);
        return true;
    }
    catch(std::string error){
        return false;
    }
}

template <typename key, typename value>
value& hash_table<key, value>::operator[](const key& k){ 
    size_t index;
    try{
        index = find(k);
        return table[index].second;
    }
    catch(std::string error){}
    for(int i = 0; i < table.get_size(); i++){
        if(!table[(index+i) % table.get_size()]){
            table[(index+i) % table.get_size()] = value();
            return table[(index+i) % table.get_size()];
        }
    }
}

template <typename key, typename value>
size_t hash_table<key, value>::size() const{
    return used_size;
}

template <typename key, typename value>
value& hash_table<key, value>::at(const key& k){
    return table[find(k)].second;
}

template <typename key, typename value>
const value& hash_table<key, value>::at(const key& k) const{
    return table[find(k)].second;;
}

template <typename key, typename value>
bool hash_table<key, value>::empty() const{
    return used_size == 0;
}

template <typename key, typename value>
size_t hash_table<key, value>::string_hash(std::string string_to_hash, size_t modulo){
    unsigned long hash_code = 5381;
    for(auto const &c:string_to_hash){
        hash_code = ((hash_code << 5) + hash_code) + c;
    }
    return hash_code % table.get_size();
}

template <typename key, typename value>
size_t hash_table<key, value>::find(const key k){
    size_t index = string_hash(static_cast<std::string>(k), table.get_size());
    for(int i = 0; i < table.get_size(); i++){
        if(!table[(index+i) % table.get_size()]){
            throw "element not found";
        }
        else if(table[(index+i) % table.get_size()].first == k){
            table[(index+i) % table.get_size()] = pair<key, value>();
            return i;
        }
    }
    throw std::string("element not found");
}

template <typename key, typename value>
void hash_table<key, value>::rehash(){
    dummy_vector<pair<key, value>> temp(2*table.get_size());
    for(int i = 0; i < table.get_size(); i++){
        if(!table[i]) continue;
        size_t new_index = string_hash(table[i].first, 2*table.get_size());
        temp[new_index] = table[i];
    }
    delete &table;
    table = temp;
}

template <typename key, typename value>
bool operator==(const hash_table<std::string, pair<key, value>>& a, const hash_table<std::string, pair<key, value>>& b){
    if(a.used_size != b.used_size) return false;
    for(int i = 0; i < a.size(); i++){
        try{
            if(a[i]) b.find(a[i].first);
        }
        catch(std::string error){
            return false;
        }
    }
    return true;
}

template <typename key, typename value>
bool operator!=(const hash_table<std::string, pair<key, value>>& a, const hash_table<std::string, pair<key, value>>& b){
    return !(a==b);
}

template class hash_table<std::string, int>;