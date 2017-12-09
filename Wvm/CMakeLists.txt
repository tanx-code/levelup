cmake_minimum_required(VERSION 3.3)
project(Wvm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
                Scan.cpp Scan.h Core.cpp Core.h)
add_executable(Wvm ${SOURCE_FILES})