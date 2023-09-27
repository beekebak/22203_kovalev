#include <iostream>
#include "utility.hpp"

#ifndef DUMMY_VECTOR_H
#define DUMMY_VECTOR_H

class dummy_vector{
  public:
    dummy_vector(size_t initial_capacity = 16);

    dummy_vector(const dummy_vector& vector);

    dummy_vector(const dummy_vector&& vector);

    dummy_vector& operator=(const dummy_vector& vector);
    
    void push_back(pair input_data);

    const pair& get_const_value(size_t index) const;

    pair& operator[](size_t index);

    void resize(size_t new_size);

    size_t get_size() const;

  private:
    pair* values = nullptr;
    size_t size = 0;
    size_t capacity = 0;

    void reallocate(size_t new_size);
};
#endif