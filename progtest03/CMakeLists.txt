cmake_minimum_required(VERSION 3.12)
project(progtest03 C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "-Wall -pedantic")

add_executable(progtest03 main.c)