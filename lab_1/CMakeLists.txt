cmake_minimum_required(VERSION 3.5)

project(lab_1 VERSION 0.1.0 LANGUAGES C CXX)

add_executable(lab_1 main.cpp dummy_vector.cpp hash_table.cpp utility.cpp)

target_include_directories(lab_1 PRIVATE lab1)
