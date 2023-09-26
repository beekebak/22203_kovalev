#include "dummy_vector.hpp"

template <typename key, typename value>
class hash_table
{
  public:
    hash_table(); //done
    ~hash_table(); //done
  
    hash_table(const hash_table& b);
    hash_table(const hash_table&& b);

    void swap(hash_table& b);

    hash_table& operator=(const hash_table& b);

    void clear(); //done

    bool erase(const key& k);
  
    bool insert(const key& k, const value& v);

    bool contains(const key& k) const;

    value& operator[](const key& k);

    value& at(const key& k);
    const value& at(const key& k) const;

    size_t size() const; //done

    bool empty() const; //done

    friend bool operator==(const hash_table& a, const hash_table& b);
    friend bool operator!=(const hash_table& a, const hash_table& b);

  private:
    struct pair{
      private:
          key first;
          value second;
    };
    dummy_vector<pair> table;
    size_t used_size;
};
