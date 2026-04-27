cmake_minimum_required(VERSION 3.14)
project(lab05)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)

add_executable(lab05 main.cpp)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(third-party/gtest)
    
    file(GLOB TEST_SOURCES tests/*.cpp)
    add_executable(check ${TEST_SOURCES})
    target_link_libraries(check gtest_main)
    add_test(NAME check COMMAND check)
endif()
include(CPackConfig.cmake)
