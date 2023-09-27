#include "dummy_vector.hpp"

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

    bool contains(const key& k) const; //smth wrong

    value& operator[](const key& k); 

    value& at(const key& k); //smth wrond
    const value& at(const key& k) const; 

    size_t size() const; 

    bool empty() const; 

    friend bool operator==(const hash_table& a, const hash_table& b);
    friend bool operator!=(const hash_table& a, const hash_table& b);

  private:
    dummy_vector table;
    size_t used_size;

    size_t string_hash(std::string string_to_hash, size_t modulo) const;

    size_t find(key k) const;

    pair get_value(const size_t& index) const;

    void rehash();
};

bool operator==(const hash_table& a, const hash_table& b);

bool operator!=(const hash_table& a, const hash_table& b);
