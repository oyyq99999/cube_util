cmake_minimum_required(VERSION 3.0)

project(cube_util)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB SRC_LIST "src/*.cpp")

add_executable(test ${SRC_LIST})
