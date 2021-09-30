cmake_minimum_required(VERSION 3.20)
project(containers)

set(CMAKE_CXX_STANDARD 98)

include_directories(libstdc++-v3/include include)

add_executable(containers srcs/main.cpp include/vector.hpp include/iterator.hpp)
