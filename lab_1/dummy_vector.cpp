#include "dummy_vector.hpp"

dummy_vector::dummy_vector(size_t initial_capacity): capacity(initial_capacity){
    values = new pair[initial_capacity];
}


dummy_vector::dummy_vector(const dummy_vector& vector):size{vector.size}{
    for(int i = 0; i < size; i++){
        values[i] = (vector.values)[i];
    }
} 

dummy_vector& dummy_vector::operator=(const dummy_vector& vector){
    size = vector.size;
    delete[] values;
    values = new pair[size];
    for(int i = 0; i < size; i++){
        values[i] = (vector.values)[i];
    }
    return *this;
}

dummy_vector::dummy_vector(const dummy_vector&& vector):size{vector.size}, values{vector.values}{} 

void dummy_vector::push_back(pair input_data){
    if(size == capacity){
        reallocate(capacity*2);
    }
    values[size++] = input_data;
}

const pair& dummy_vector::get_const_value(size_t index) const{
    return values[index];
}

pair& dummy_vector::operator[](size_t index){
    return values[index];
}

void dummy_vector::resize(size_t new_size){
    if(new_size < 1) throw "prohibited size";
    reallocate(new_size);
}

size_t dummy_vector::get_size() const{
    return size;
}

void dummy_vector::reallocate(size_t new_size){
    pair* temp = new pair[new_size];
    for(int i = 0; i < std::min(capacity, new_size); i++){
        temp[i] = values[i];
    }
    delete[] values;
    values = temp;
    capacity = new_size;
}