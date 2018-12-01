cmake_minimum_required(VERSION 3.12)
project(progtest05 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -pedantic")

add_executable(progtest05 main.c)