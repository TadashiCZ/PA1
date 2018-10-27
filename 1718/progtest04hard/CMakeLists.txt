cmake_minimum_required(VERSION 3.8)
project(progtest04hard)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic -Wno-long-long -O2 -c -o")
set(SOURCE_FILES main.c)
add_executable(progtest04hard ${SOURCE_FILES})