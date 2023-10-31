#pragma once 

#include <algorithm>
#include <iostream>

#include "utility.hpp"

class dummy_vector {
  public:
    dummy_vector(size_t initial_capacity = 16);

    ~dummy_vector();

    dummy_vector(const dummy_vector& vector);

    dummy_vector(dummy_vector&& vector);

    dummy_vector& operator=(const dummy_vector& vector);

    const pair& get_const_value(size_t index) const;

    pair& operator[](size_t index);

    size_t get_capacity() const;

    void reallocate(size_t new_size);

    void swap(dummy_vector& other);

  private:
    size_t capacity = 0;
    pair* values = nullptr;
};
