#pragma once

#include <string>

typedef std::string key;

struct value {
  int age;
  int weight;
  int height;

  value(int in_age=0, int in_weight=0, int in_height=0);

  operator bool() const;

  friend bool operator==(const value& a, const value& b); 
  friend bool operator!=(const value& a, const value& b); 
};

bool operator==(const value& a, const value& b);
bool operator!=(const value& a, const value& b);

struct pair {
  public:
    key first = "";
    value second;

    pair() = default;

    pair(key k, value v);

    operator bool() const;

    friend bool operator==(const pair& a, const pair& b); 
    friend bool operator!=(const pair& a, const pair& b); 
};

bool operator==(const pair& a, const pair& b);
bool operator!=(const pair& a, const pair& b);