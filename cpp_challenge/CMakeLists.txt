cmake_minimum_required(VERSION 3.5)

project(cpp_assignment)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -O3 -std=c++11")

set(SOURCE_FILES labyrinth.cpp)

add_executable(labyrinth ${SOURCE_FILES})