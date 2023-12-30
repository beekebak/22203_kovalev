cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
#set(GOOGLETEST_VERSION 1.14.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

project("lab_2")

set(SOURCES 
    src/blackjack.cpp
    src/dealer.cpp
    src/player.cpp 
    src/card.cpp 
    src/choose_table.cpp 
    src/controller.cpp 
    src/factories_initialization.cpp 
    src/game.cpp 
    src/match.cpp 
    src/parser.cpp 
    src/strategy.cpp 
    src/logger.cpp
)

#enable_testing()

#add_subdirectory(googletest)
add_executable(main ${SOURCES})

target_include_directories(main PRIVATE ${PROJECT_SOURCE_DIR}/include)

#target_link_libraries(main gtest_main)
