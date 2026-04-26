cmake_minimum_required(VERSION 3.14)
project(banking)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)
option(COVERAGE "Enable coverage reporting" OFF)

add_library(banking STATIC
    src/Account.cpp
    src/Transaction.cpp
)

target_include_directories(banking PUBLIC include)

if(COVERAGE)
    target_compile_options(banking PRIVATE --coverage -O0 -g)
    target_link_libraries(banking PRIVATE --coverage)
endif()
if(BUILD_TESTS)
    enable_testing()
    
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
    )
    FetchContent_MakeAvailable(googletest)
    
    add_executable(banking_tests
        tests/test_account.cpp
        tests/test_transaction.cpp
        tests/mock_account.hpp
    )
    
    target_link_libraries(banking_tests banking gtest_main gmock)
    target_include_directories(banking_tests PRIVATE include)
    add_test(NAME banking_tests COMMAND banking_tests)
endif()
