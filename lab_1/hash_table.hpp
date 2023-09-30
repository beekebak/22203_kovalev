#include "dummy_vector.hpp"

class hash_table
{
  public:
    hash_table(); //seems to work
    ~hash_table(); //seems to work
  
    hash_table(const hash_table& b); 
    //hash_table(const hash_table&& b); ????

    void swap(hash_table& b); //not done yet

    hash_table& operator=(const hash_table& b); //seems to work

    void clear(); //seems to work

    bool erase(const key& k); //seems to work
  
    bool insert(const key& k, const value& v); //seems to work

    bool contains(const key& k) const; //smth wrong

    value& operator[](const key& k); //seems to work

    value& at(const key& k); //smth wrond
    const value& at(const key& k) const; 

    size_t size() const; //seems to work

    bool empty() const; //seems to work

    pair get_by_index(size_t idx);

    friend bool operator==(const hash_table& a, const hash_table& b); //seems to work
    friend bool operator!=(const hash_table& a, const hash_table& b); //seems to work

  private:
    dummy_vector table;
    size_t used_size = 0;

    size_t string_hash(std::string string_to_hash, size_t modulo) const;

    size_t find(key k) const;

    pair get_value(const size_t& index) const;

    void rehash();
};

bool operator==(const hash_table& a, const hash_table& b);

bool operator!=(const hash_table& a, const hash_table& b);
