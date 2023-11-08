#include "hash_table.hpp"

static const int element_not_found = -1;

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
    size_t idx = find(k);
    if(idx == element_not_found) return false;
    table[idx] = pair();
    fix_claster(idx);
    used_size--;
    return true;
}

bool hash_table::insert(const key& k, const value& v){
    // no copypasta
    if(static_cast<double>(table.get_capacity()) * fill_factor < static_cast<double>(used_size)){
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
    size_t index = find(k);
    if(index == element_not_found) return false;
    return true;
}

value& hash_table::operator[](const key& k){ 
    size_t index;
    index = find(k);
    if(index != element_not_found) return table[index].second;
    insert(k, value(0,0,0));
    index = find(k);
    return table[index].second;
}

pair hash_table::get_value(const size_t& index) const{
    return table[index];
}

size_t hash_table::size() const{
    return used_size;
}

value& hash_table::at(const key& k){
    int idx = find(k);
    if(idx != element_not_found && table[idx].second) return table[idx].second;
    else throw no_such_element();
}

const value& hash_table::at(const key& k) const{
    int idx = find(k);
    if(idx != element_not_found && table[idx].second) return table[idx].second;
    else throw no_such_element();
}

bool hash_table::empty() const{
    return used_size == 0;
}

// https://stackoverflow.com/questions/7666509/hash-function-for-string
// djb2 algorithm
size_t hash_table::string_hash(std::string string_to_hash, size_t modulo) const{
    size_t hash_code = 5381;
    for(char c:string_to_hash){
        hash_code = ((hash_code << 5) + hash_code) + c;
    }
    return hash_code % modulo;
}

int hash_table::find(const key k) const{
    size_t index = string_hash(k, table.get_capacity());
    for(size_t i = 0; i < table.get_capacity(); i++){
        if(table[(index+i) % table.get_capacity()].first == k){
            return (index+i) % table.get_capacity();
        }
        else if(!table[(index+i) % table.get_capacity()]){
            return element_not_found;
        }
    }
    return element_not_found;
}

void hash_table::fix_claster(size_t idx){
    for(size_t i = 1; i < table.get_capacity(); i++){
        if(!table[(i+idx) % table.get_capacity()]){
            return;
        }
        if(string_hash(table[(i+idx) % table.get_capacity()].first, table.get_capacity()) <= idx){
            std::swap(table[i+idx % table.get_capacity()], table[idx]);
            idx = i+idx % table.get_capacity();
            i = 0;
        }
    }
}

void hash_table::rehash(){
    dummy_vector temp(table);
    table.make_bigger(table.get_capacity()*2);
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
            size_t idx = b.find(temp.first);
            if(idx == element_not_found || b.get_value(idx) != temp) return false;
        }
    }
    return true;
}

bool operator!=(const hash_table& a, const hash_table& b){
    return !(a==b);
}