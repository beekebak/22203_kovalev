#include <iostream>
#include <cstring>

class string{
  public:
    string(size_t initial_capacity): capacity(initial_capacity){
        memory = (char*) malloc(initial_capacity+1);
        memory[initial_capacity] = '\0';
        std::cout << "constructed by size " << capacity << std::endl;
    }
    string(){
      string(16);
    }
    string(const string& other_str): capacity(other_str.capacity), size(other_str.size){
        memory = (char*) malloc(other_str.capacity+1);
        std::strcpy(memory, other_str.memory);
        std::cout << "constructed by other_str " << memory << std::endl;
    }
    ~string(){
        free(memory);
        std::cout << "destroyed" << std::endl;
    }
    void append(char c){
        if(size == capacity){
          reallocate();
        }
        if(size == capacity){
          std::cout << "bad allocation" << std::endl;
          return;
        }
        memory[size++] = c; 
        memory[size] = '\0';
    }
    void operator=(const string& right_string){
        if(memory){
          free(memory);
        }
        memory = (char*) malloc(right_string.capacity+1);
        std::strcpy(memory, right_string.memory);
        capacity = right_string.capacity;
        size = right_string.size;
    }
    char& operator[](size_t index){
        return memory[index];
    }
    void operator+=(string right_string){
      if(size + right_string.size > capacity){
        reallocate(size + right_string.size);
      }
      if(size + right_string.size > capacity){
        return;
      }
      memcpy(memory+size, right_string.memory, right_string.size);
      size += right_string.size;
    }
  private:
    char* memory = nullptr;
    size_t capacity = 0;
    size_t size = 0;
    void reallocate(){
        char* tmp = (char*) realloc(memory, capacity*2+1);
        if(!tmp){
          return;
        }
        memory = tmp;
        capacity *= 2;
        memory[capacity] = '\0';
    }
    void reallocate(size_t needed_size){
      char* tmp = (char*) realloc(memory, needed_size+1);
        if(!tmp){
          return;
        }
        memory = tmp;
        capacity = needed_size;
        memory[capacity] = '\0';
    }
};

int main(){
    return 0;
}