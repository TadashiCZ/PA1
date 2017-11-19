cmake_minimum_required(VERSION 3.8)
project(progtest03hard)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wall -pedantic")
set(SOURCE_FILES main.c)
add_executable(progtest03hard ${SOURCE_FILES})