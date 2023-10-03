cmake_minimum_required(VERSION 3.20)

project("lab_1")

set(CMAKE_CXX_STANDARD 17)
set(GOOGLETEST_VERSION 1.14.0)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")

enable_testing()

add_subdirectory(googletest)
add_executable(main hash_table.cpp dummy_vector.cpp utility.cpp main.cpp)
target_link_libraries(main gtest_main)