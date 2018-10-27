cmake_minimum_required(VERSION 3.12)
project(progtest01)

set(CMAKE_CXX_STANDARD 14)
set ( CMAKE_CXX_FLAGS "-Wall -pedantic")

add_executable(progtest01 main.cpp)