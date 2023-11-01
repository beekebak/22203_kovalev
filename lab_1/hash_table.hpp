#pragma once

#include "dummy_vector.hpp"

class hash_table
{
  public:
    //default constructor
    hash_table(); 
    //default destructor
    ~hash_table(); 
  
    //copy costructor
    hash_table(const hash_table& b); 
    //move constructor
    hash_table(hash_table&& b); 

    /** 
     * @brief swaps two hash_tables
     * 
     * std::swap() to use move semantics 
    */
    void swap(hash_table& b); 

    /**
     * replaces current hash_table data with given hash_table data
     * @return method's owner
    */
    hash_table& operator=(const hash_table& b);

    /// @brief deletes stored data
    void clear(); 

    /**
     * @brief deletes one element by key
     * @param key of element to delete
     * @return success of deletion
    */
    bool erase(const key& k); 
  
    /**
     * @brief inserts one element
     * 
     * Inserts value to hash_table using linear probing algorithm.
     * Extends table if needed.
     * 
     * @param key of element, value of element
     * @return success of insertion
    */
    bool insert(const key& k, const value& v); 

    /**
     * @brief returns if element with given key is in the table
     * 
     * Seeks for given key in table until finds it or checks all elements
     * 
     * @param key of element to find
     * @return true if element is in the table else returns false   
    */
    bool contains(const key& k) const; 
 
    /** 
    * Seeks for value with given key in the table. 
    * If found returns it.
    * Else creates default value for this key and returns it.
    * 
    * @return value with given if it is in table default value else
    */
    value& operator[](const key& k); 

    /**
     * @brief returns value for given key if possible
     * 
     * Seeks for value with given key in the table.
     * If found returns it.
     * Else throws "element not found" exception.
     * 
     * @return found element
    */
    value& at(const key& k); 

    /**
     * @brief returns value for given key if possible
     * 
     * Seeks for value with given key in the table.
     * If found returns it.
     * Else throws "element not found" exception.
     * 
     * @return found element
    */
    const value& at(const key& k) const; 

    //returns count of elements in the table
    size_t size() const;

    //returns if table is empty
    bool empty() const;

    /**
     * @brief compares two hash_tables
     * 
     * Compares two tables sizes. If don't match returns false.
     * If match, for each element if first table looks for the same in second table.
     * If every element has it's match returns true else false.
     * 
     * @return true if table have same <key, value> pairs else false
    */
    friend bool operator==(const hash_table& a, const hash_table& b); 

    /**
     * @brief compares two hash_tables
     * 
     * negation of operator== method.
     * Compares two tables sizes. If don't match returns true.
     * If match, for each element if first table looks for the same in second table.
     * If every element has it's match returns false else true.
     * 
     * @return false if table have same <key, value> pairs else true.
    */
    friend bool operator!=(const hash_table& a, const hash_table& b); 

    size_t get_all_size(){
      return table.get_capacity();
    }

    pair get_by_index(size_t index){
      return table[index];
    }

    size_t string_hash(std::string string_to_hash, size_t modulo) const;

  private:
    dummy_vector table;
    size_t used_size = 0;
    static const inline double fill_factor = 0.75;

    //size_t string_hash(std::string string_to_hash, size_t modulo) const;

    int find(key k) const;

    void fix_claster(size_t k);

    pair get_value(const size_t& index) const;

    void rehash();

    class no_such_element{};
};

bool operator==(const hash_table& a, const hash_table& b);

bool operator!=(const hash_table& a, const hash_table& b);
