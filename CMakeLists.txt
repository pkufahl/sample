cmake_minimum_required(VERSION 3.2)
project(sample)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES sample.cpp)
add_executable(sample ${SOURCE_FILES})