#include "dummy_vector.hpp"

class hash_table
{
  public:
    hash_table(); //seems to work tested
    ~hash_table(); //seems to work 
  
    hash_table(const hash_table& b); //seems to work tested
    hash_table(hash_table&& b); //seems to work tested

    void swap(hash_table& b); //seems to work tested

    hash_table& operator=(const hash_table& b); //seems to work tested

    void clear(); //seems to work tested

    bool erase(const key& k); //seems to work tested
  
    bool insert(const key& k, const value& v); //seems to work tested

    bool contains(const key& k) const; //seems to work tested
 
    value& operator[](const key& k); //seems to work tested

    value& at(const key& k); //seems to work tested
    const value& at(const key& k) const; //seems to work tested

    size_t size() const; //seems to work tested

    bool empty() const; //seems to work tested

    friend bool operator==(const hash_table& a, const hash_table& b); //seems to work tested
    friend bool operator!=(const hash_table& a, const hash_table& b); //seems to work tested

  private:
    dummy_vector table;
    size_t used_size = 0;

    //make a shrink metod?

    size_t string_hash(std::string string_to_hash, size_t modulo) const;

    size_t find(key k) const;

    pair get_value(const size_t& index) const;

    void rehash();
};

bool operator==(const hash_table& a, const hash_table& b);

bool operator!=(const hash_table& a, const hash_table& b);
