cmake_minimum_required(VERSION 3.20)


set(CMAKE_CXX_STANDARD 17)
#set(GOOGLETEST_VERSION 1.14.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

project("lab_2")

#enable_testing()

#add_subdirectory(googletest)
add_executable(main main.cpp dealer.cpp player.cpp card.cpp choose_table.cpp controller.cpp factories_initialization.cpp game.cpp match.cpp parser.cpp strategy.cpp logger.cpp)
#target_link_libraries(main gtest_main)
