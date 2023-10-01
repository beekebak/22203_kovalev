#include <string>

typedef std::string key;

struct value{
  int age = 0;
  int weight = 0;
  int height = 0;

  value();

  value(int in_age, int in_weight, int in_height);

  operator bool() const;

  friend bool operator==(const value& a, const value& b); 
  friend bool operator!=(const value& a, const value& b); 
};

bool operator==(const value& a, const value& b);
bool operator!=(const value& a, const value& b);

struct pair{
  public:
    key first = "";
    value second;

    pair() = default;

    pair(key k, value v);

    operator bool() const;

    pair& operator=(pair& other);

    friend bool operator==(const pair& a, const pair& b); 
    friend bool operator!=(const pair& a, const pair& b); 
};

bool operator==(const pair& a, const pair& b);
bool operator!=(const pair& a, const pair& b);