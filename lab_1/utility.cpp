#include "utility.hpp"

pair::pair(key k, value v):first(k), second(v){}

value::value(int in_age, int in_weight, int in_height):age(in_age), weight(in_weight), height(in_height){}

value::value():age(0), weight(0), height(0){}

value::operator bool() const{
    return age || weight || height;
}

bool operator==(const value& a, const value& b){
    return a.age == b.age && a.height == b.height && a.weight == b.weight;
}

bool operator!=(const value& a, const value& b){
    return !(a==b);
}

pair::operator bool() const{
    return first != std::string("") || second;
}

pair& pair::operator=(pair& other){
    first = other.first;
    second = other.second;
    return *this;
}

bool operator==(const pair& a, const pair& b){
    return a.first == b.first && a.second == b.second;
}
bool operator!=(const pair& a, const pair& b){
    return !(a==b);
}