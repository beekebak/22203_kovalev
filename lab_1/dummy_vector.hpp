#include<iostream>

#ifndef DUMMY_VECTOR_H
#define DUMMY_VECTOR_H

template <typename T>
class dummy_vector{
  public:
    dummy_vector(size_t initial_capacity = 16);

    ~dummy_vector();
    
    void push_back(T input_data);

    T& operator[](size_t index);

    void resize(size_t new_size);

    size_t get_size();

  private:
    T* values = nullptr;
    size_t size = 0;
    size_t capacity = 0;

    void reallocate(size_t new_size);
};
#endif