cmake_minimum_required(VERSION 3.13)
project(progtest06 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -pedantic -g")
add_executable(progtest06 main.c)