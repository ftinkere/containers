cmake_minimum_required(VERSION 3.20)
project(containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_COMPILER clang++)

include_directories(include /usr/include)

add_executable(containers srcs/main.cpp include/vector.hpp include/iterator.hpp include/cmp.hpp)
