cmake_minimum_required(VERSION 3.8)
project(progtest01hard)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wall -pedantic -lm")
set(SOURCE_FILES main.c)
add_executable(progtest01hard ${SOURCE_FILES})