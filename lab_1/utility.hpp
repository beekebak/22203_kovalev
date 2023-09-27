#include <string>

typedef std::string key;

struct value{
  int age = 0;
  int weight = 0;
  int height = 0;

  operator bool() const;
};

struct pair{
  public:
    key first = "";
    value second;

    pair() = default;

    pair(key k, value v);

    operator bool() const;

    pair& operator=(pair& other);
};