#include "dummy_vector.hpp"

template <typename key, typename value>
class hash_table
{
  public:
    hash_table(); 
    ~hash_table(); 
  
    hash_table(const hash_table& b); 
    hash_table(const hash_table&& b); 

    void swap(hash_table& b); //not done yet

    hash_table& operator=(const hash_table& b); 

    void clear(); 

    bool erase(const key& k); 
  
    bool insert(const key& k, const value& v); 

    bool contains(const key& k) const;

    value& operator[](const key& k); 

    value& at(const key& k); 
    const value& at(const key& k) const; 

    size_t size() const; 

    bool empty() const; 

    friend bool operator==(const hash_table& a, const hash_table& b);
    friend bool operator!=(const hash_table& a, const hash_table& b);

  private:
    dummy_vector<pair<key, value>> table;
    size_t used_size;

    size_t string_hash(std::string string_to_hash, size_t modulo);

    size_t find(key k);

    void rehash();
};

template <typename key, typename value>
bool operator==(const hash_table<std::string, pair<key,value>>& a, const hash_table<std::string, pair<key,value>>& b);

template <typename key, typename value>
bool operator!=(const hash_table<std::string, pair<key,value>>& a, const hash_table<std::string, pair<key,value>>& b);
