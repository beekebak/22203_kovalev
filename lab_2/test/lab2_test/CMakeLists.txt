cmake_minimum_required(VERSION 3.5)

project(lab_2 LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DGTEST_LANGUAGE_CXX11)

find_package(Threads REQUIRED)

set(SOURCES
    ../../src/blackjack.cpp
    ../../src/dealer.cpp
    ../../src/player.cpp
    ../../src/card.cpp
    ../../src/choose_table.cpp
    ../../src/controller.cpp
    ../../src/game.cpp
    ../../src/match.cpp
    ../../src/parser.cpp
    ../../src/strategy.cpp
    ../../src/logger.cpp
)


if ($ENV{GOOGLETEST_DIR})
    set(GOOGLETEST_DIR $ENV{GOOGLETEST_DIR})
else ()
    if (NOT "/home/beekebak/main/plusi/22203_kovalev/lab_2/test/googletest" STREQUAL "")
        message(WARNING "Using googletest src dir specified at Qt Creator wizard")
    endif ()
    set(GOOGLETEST_DIR "/home/beekebak/main/plusi/22203_kovalev/lab_2/test/googletest")
endif ()
if (EXISTS ${GOOGLETEST_DIR})
    set(GTestSrc ${GOOGLETEST_DIR}/googletest)
    set(GMockSrc ${GOOGLETEST_DIR}/googlemock)
elseif (UNIX AND EXISTS /usr/src/gtest)
    set(GTestSrc /usr/src/gtest)
    message(WARNING "Using gtest from system")
    if (EXISTS /usr/src/gmock)
        set(GMockSrc /usr/src/gmock)
    endif ()
else ()
    message( FATAL_ERROR "No googletest src dir found - set GOOGLETEST_DIR to enable!")
endif ()

set(GTestFiles ${GTestSrc}/src/gtest-all.cc)
set(GTestIncludes ${GTestSrc} ${GTestSrc}/include)
if (NOT ${GMockSrc} STREQUAL "")
    list(APPEND GTestFiles ${GMockSrc}/src/gmock-all.cc)
    list(APPEND GTestIncludes ${GMockSrc} ${GMockSrc}/include)
endif ()

include_directories(${GTestIncludes})

add_executable(lab_2 main.cpp tst_lab_2.cpp ${SOURCES}
               ${GTestFiles}
               tst_card.cpp
               tst_strategies.cpp
               tst_choosetable.cpp
               tst_dealer.cpp
               tst_factory.cpp

               tst_player.cpp
               tst_parser.cpp
               tst_match.cpp
               tst_game.cpp
               tst_controller.cpp)
add_test(NAME lab_2 COMMAND lab_2)
target_link_libraries(lab_2 PRIVATE Threads::Threads)
target_include_directories(lab_2 PRIVATE ${PROJECT_SOURCE_DIR}/../../include)
