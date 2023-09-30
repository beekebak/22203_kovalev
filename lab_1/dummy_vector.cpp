#include "dummy_vector.hpp"

dummy_vector::dummy_vector(size_t initial_capacity): capacity{initial_capacity}{
    values = new pair[initial_capacity];
}


dummy_vector::dummy_vector(const dummy_vector& vector):capacity{vector.capacity}{
    values = new pair[vector.capacity];
    for(int i = 0; i < capacity; i++){
        values[i] = (vector.values)[i];
    }
} 

dummy_vector& dummy_vector::operator=(const dummy_vector& vector){
    capacity = vector.capacity;
    delete[] values;
    values = new pair[capacity];
    for(int i = 0; i < capacity; i++){
        values[i] = (vector.values)[i];
    }
    return *this;
}

dummy_vector::dummy_vector(const dummy_vector&& vector):capacity{vector.capacity}, values{vector.values}{} 

const pair& dummy_vector::get_const_value(size_t index) const{
    return values[index];
}

pair& dummy_vector::operator[](size_t index){
    return values[index];
}

size_t dummy_vector::get_capacity() const{
    return capacity;
}

void dummy_vector::reallocate(size_t new_size){
    delete[] values;
    values = new pair[new_size];
    capacity = new_size;
}