cmake_minimum_required(VERSION 3.22)
project(CalcGTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(CalcLib
        ICalculator.h
        SimpleCalculator.h SimpleCalculator.cpp
        IHistory.h
        InMemoryHistory.h InMemoryHistory.cpp
)

enable_testing()

add_subdirectory(googletest googletest-build)

add_executable(CalcLibTests CalculatorTests/tests.cpp)

target_link_libraries(CalcLibTests
    gtest
    gmock
    CalcLib
)

include(GoogleTest)
gtest_discover_tests(CalcLibTests)

target_include_directories(CalcLibTests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/googletest/include
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(CalcLib PRIVATE --coverage -fprofile-arcs -ftest-coverage)
  target_link_libraries(Calculator_test --coverage)
endif()