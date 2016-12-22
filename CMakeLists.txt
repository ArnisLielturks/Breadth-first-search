cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(Breadth-first-search)

file(GLOB_RECURSE sources src/*.cpp)
add_executable(Breadth-first-search ${sources})

target_include_directories(Breadth-first-search PUBLIC include)