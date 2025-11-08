cmake_minimum_required(VERSION 3.14)
project(lab4_oop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    src/main.cpp
)

set(HEADERS
    include/Figure.hpp
    include/Triangle.hpp
    include/Square.hpp
    include/Rectangle.hpp
    include/array.hpp
)

add_executable(lab4 ${SOURCES} ${HEADERS})
target_compile_features(lab4 PRIVATE cxx_std_20)

enable_testing()

find_package(GTest QUIET)

if(GTest_FOUND)
    set(TEST_SOURCES
        tests/test.cpp
    )

    add_executable(runTests ${TEST_SOURCES} ${HEADERS})
    target_link_libraries(runTests GTest::gtest GTest::gtest_main)
    target_include_directories(runTests PRIVATE include)
    target_compile_features(runTests PRIVATE cxx_std_20)

    add_test(NAME AllTests COMMAND runTests)
else()
    message(STATUS "Google Test не найден. Тесты не будут скомпилированы.")
endif()