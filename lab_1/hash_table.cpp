#include "hash_table.hpp"
#include <typeinfo>

hash_table::hash_table() = default;

hash_table::~hash_table() = default;

hash_table::hash_table(const hash_table& b):table{b.table}, used_size{b.used_size}{}

hash_table::hash_table(hash_table&& b):table{b.table}, used_size{b.used_size}{
    b.table = dummy_vector();
    b.used_size = 0;
} 

void hash_table::swap(hash_table& b){
    std::swap(b.used_size, used_size);
    table.swap(b.table);
}

hash_table& hash_table::operator=(const hash_table& b){
    used_size = b.used_size;
    table = b.table;
    return *this;
}

void hash_table::clear(){
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
    if(static_cast<double>(table.get_capacity()) * 0.75 <static_cast<double>(used_size)){
        rehash();
    } 
    size_t index = string_hash(static_cast<std::string>(k), table.get_capacity());
    for(size_t i = 0; i < table.get_capacity(); i++){
        if(!table[(index+i) % table.get_capacity()]){
            pair tmp(k,v);
            table[(index+i) % table.get_capacity()] = tmp;
            used_size++;
            return true;
        }
    }
    return false;
}

bool hash_table::contains(const key& k) const{
    try{
        size_t index = find(k);
        if(!table.get_const_value(index).second) return false;
        return true;
    }
    catch(std::string error){
        return false;
    }
}

value& hash_table::operator[](const key& k){ 
    size_t index;
    try{
        index = find(k);
        return table[index].second;
    }
    catch(std::string error){}
    index = string_hash(k, table.get_capacity());
    if(static_cast<double>(table.get_capacity()) * 0.75 <static_cast<double>(used_size)){
        rehash();
    }
    for(size_t i = 0; i < table.get_capacity(); i++){
        if(!table[(index+i) % table.get_capacity()]){
            table[(index+i) % table.get_capacity()].first = k;
            table[(index+i) % table.get_capacity()].second = value();
            used_size++;
            return table[(index+i) % table.get_capacity()].second;
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
    if(table[find(k)].second) return table[find(k)].second;
    else throw("no such element");
}


const value& hash_table::at(const key& k) const{
    if(table.get_const_value(find(k)).second) return table.get_const_value(find(k)).second;
    else throw("no such element");
}

bool hash_table::empty() const{
    return used_size == 0;
}

size_t hash_table::string_hash(std::string string_to_hash, size_t modulo) const{
    unsigned long hash_code = 5381;
    for(auto const &c:string_to_hash){
        hash_code = ((hash_code << 5) + hash_code) + c;
    }
    return hash_code % modulo;
}

size_t hash_table::find(const key k) const{
    size_t index = string_hash(static_cast<std::string>(k), table.get_capacity());
    for(size_t i = 0; i < table.get_capacity(); i++){
        if(!table.get_const_value((index+i) % table.get_capacity())){
            throw std::string("element not found");
        }
        else if(table.get_const_value((index+i) % table.get_capacity()).first == k){
            return (index+i) % table.get_capacity();
        }
    }
    throw std::string("element not found");
}

void hash_table::rehash(){
    dummy_vector temp(table);
    table.reallocate(table.get_capacity()*2);
    for(size_t i = 0; i < temp.get_capacity(); i++){
        if(!temp[i]) continue;
        size_t new_index = string_hash(temp[i].first, table.get_capacity());
        for(size_t j = 0; j < table.get_capacity(); j++){
            if(table[(new_index+j)%table.get_capacity()]) continue;
            table[(new_index+j)%table.get_capacity()] = temp[i];
            break;
        }
    }
}


bool operator==(const hash_table& a, const hash_table& b){
    if(a.used_size != b.used_size) return false;
    for(size_t i = 0; i < a.size(); i++){
        pair temp = a.get_value(i);
        if(temp){
            try{
                size_t idx = b.find(temp.first);
                if(b.get_value(idx) != temp) return false;
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