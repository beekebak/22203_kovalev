#include "hash_table.hpp"
#include <typeinfo>

hash_table::hash_table() = default;

hash_table::~hash_table() = default;

hash_table::hash_table(const hash_table& b):table{b.table}, used_size{b.used_size}{}

hash_table::hash_table(const hash_table&& b):table{b.table}, used_size{b.used_size}{}

hash_table& hash_table::operator=(const hash_table& b){
    used_size = b.used_size;
    table = b.table;
    return *this;
}

void hash_table::clear(){
    delete &table;
    table = dummy_vector();
    used_size = 0;
}

bool hash_table::erase(const key& k){
    try{
        size_t idx = find(k);
        value tmp;
        table[idx].second = tmp;
        return true;
    }
    catch(std::string error){
        return false;
    }
}

bool hash_table::insert(const key& k, const value& v){
    if(static_cast<double>(table.get_size()) * 0.75 <static_cast<double>(used_size)){
        rehash();
    } 
    size_t index = string_hash(static_cast<std::string>(k), table.get_size());
    for(int i = 0; i < table.get_size(); i++){
        if(!table[(index+i) % table.get_size()]){
            pair tmp(k,v);
            table[(index+i) % table.get_size()] = tmp;
            used_size++;
            return true;
        }
    }
    return false;
}

/*template <typename key, typename value>
bool hash_table<key, value>::contains(const key& k) const{
    try{
        size_t index = find(k);
        return true;
    }
    catch(std::string error){
        return false;
    }
}*/

value& hash_table::operator[](const key& k){ 
    size_t index;
    try{
        index = find(k);
        return table[index].second;
    }
    catch(std::string error){}
    for(int i = 0; i < table.get_size(); i++){
        if(!table[(index+i) % table.get_size()]){
            value tmp;
            table[(index+i) % table.get_size()].second = tmp;
            return table[(index+i) % table.get_size()].second;
        }
    }
    return table[0].second;
}

pair hash_table::get_value(const size_t& index) const{
    return table.get_const_value(index);
}

size_t hash_table::size() const{
    return used_size;
}

value& hash_table::at(const key& k){
    return table[find(k)].second;
}

/*template <typename key, typename value>
const value& hash_table<key, value>::at(const key& k) const{
    return table[find(k)].second;;
}*/

bool hash_table::empty() const{
    return used_size == 0;
}

size_t hash_table::string_hash(std::string string_to_hash, size_t modulo) const{
    unsigned long hash_code = 5381;
    for(auto const &c:string_to_hash){
        hash_code = ((hash_code << 5) + hash_code) + c;
    }
    return hash_code % table.get_size();
}

size_t hash_table::find(const key k) const{
    size_t index = string_hash(static_cast<std::string>(k), table.get_size());
    for(int i = 0; i < table.get_size(); i++){
        if(table.get_const_value((index+i) % table.get_size())){
            throw "element not found";
        }
        else if(table.get_const_value((index+i) % table.get_size()).first == k){
            return i;
        }
    }
    throw std::string("element not found");
}

void hash_table::rehash(){
    dummy_vector temp(2*table.get_size());
    for(int i = 0; i < table.get_size(); i++){
        if(!table[i]) continue;
        size_t new_index = string_hash(table[i].first, 2*table.get_size());
        temp[new_index] = table[i];
    }
    delete &table;
    table = temp;
}


bool operator==(const hash_table& a, const hash_table& b){
    if(a.used_size != b.used_size) return false;
    for(int i = 0; i < a.size(); i++){
        pair temp = a.get_value(i);
        if(temp.second){
            try{
                b.find(temp.first);
            }
            catch(std::string error){
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const hash_table& a, const hash_table& b){
    return !(a==b);
}