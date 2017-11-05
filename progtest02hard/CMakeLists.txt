cmake_minimum_required(VERSION 3.8)
project(progtest02hard)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wall -Wextra -pedantic")
set(SOURCE_FILES main.c)
add_executable(progtest02hard ${SOURCE_FILES})