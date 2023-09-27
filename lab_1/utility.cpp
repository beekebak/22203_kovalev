#include "utility.hpp"

pair::pair(key k, value v):first(k), second(v){}

value::operator bool() const{
    return age || weight || height;
}

pair::operator bool() const{
    return first != "" || second;
}

pair& pair::operator=(pair& other){
    first = other.first;
    second = other.second;
    return *this;
}