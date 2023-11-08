#include <algorithm>
#include "dummy_vector.hpp"

dummy_vector::dummy_vector(size_t initial_capacity): capacity{initial_capacity}{
    values = new pair[initial_capacity];
}

dummy_vector::~dummy_vector(){
    delete[] values;
}

dummy_vector::dummy_vector(const dummy_vector& vector):capacity{vector.capacity}{
    values = new pair[vector.capacity];
    std::copy(vector.values, vector.values+capacity, values);
} 

dummy_vector& dummy_vector::operator=(const dummy_vector& vector){
    if(this == &vector) return *this;
    capacity = vector.capacity;
    delete[] values;
    values = new pair[capacity];
    std::copy(vector.values, vector.values+capacity, values);
    return *this;
}

dummy_vector::dummy_vector(dummy_vector&& vector):capacity{vector.capacity}, values{vector.values}{
    vector.values = nullptr;
    vector.capacity = 0;
} 

dummy_vector& dummy_vector::operator=(dummy_vector&& vector){
    if(this != &vector){
        delete[] values;
        values = vector.values;
        capacity = vector.capacity;
        vector.values = nullptr;
        vector.capacity = 0;
    }
    return *this;
}

const pair& dummy_vector::operator[](size_t index) const{
    return values[index];
}

pair& dummy_vector::operator[](size_t index){
    return values[index];
}

size_t dummy_vector::get_capacity() const{
    return capacity;
}

void dummy_vector::make_bigger(size_t new_size){
    delete[] values;
    values = new pair[new_size];
    capacity = new_size;
}

void dummy_vector::swap(dummy_vector& other){
    std::swap(capacity, other.capacity);
    std::swap(values, other.values);
}