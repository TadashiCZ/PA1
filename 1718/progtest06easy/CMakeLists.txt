cmake_minimum_required(VERSION 3.9)
project(progtest06easy C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -Wno-long-long -Werror")
add_executable(progtest06easy main.c)