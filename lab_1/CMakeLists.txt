cmake_minimum_required(VERSION 3.20)

project("lab_1")

set(CMAKE_CXX_STANDARD 17)
set(GOOGLETEST_VERSION 1.14.0)

enable_testing()
include(googletest)
add_subdirectory(googletest)
add_executable(main main.cpp hash_table.cpp dummy_vector.cpp)
target_link_libraries(main gtest_main gmock_main)