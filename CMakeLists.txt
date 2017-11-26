cmake_minimum_required(VERSION 3.8)
project(DBigNums)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp DBigInteger.hpp DBigDecimal.cpp DBigDecimal.hpp)
add_executable(DBigNums ${SOURCE_FILES})