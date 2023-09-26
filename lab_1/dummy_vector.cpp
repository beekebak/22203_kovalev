#include "dummy_vector.hpp"

template<typename T>
dummy_vector<T>::dummy_vector(size_t initial_capacity): capacity(initial_capacity){
    values = new T[initial_capacity*sizeof(T)];
}

template<typename T>
void dummy_vector<T>::push_back(T input_data){
    if(size == capacity){
        reallocate(capacity*2);
    }
    values[size++] = input_data;
}

template<typename T>
T& dummy_vector<T>::operator[](size_t index){
    return values[index];
}

template<typename T>
void dummy_vector<T>::resize(size_t new_size){
    reallocate(new_size);
}

template<typename T>
size_t dummy_vector<T>::get_size(){
    return size;
}

template<typename T>
void dummy_vector<T>::reallocate(size_t new_size){
    if(new_size < capacity) throw "negative resizing";
    T* temp = new T[new_size*sizeof(T)];
    for(int i = 0; i < capacity; i++){
        temp[i] = values[i];
    }
    delete[] values;
    values = temp;
    capacity = new_size;
}

template class dummy_vector<int>;