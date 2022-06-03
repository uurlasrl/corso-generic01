cmake_minimum_required(VERSION 3.21)
project(generic01)

set(CMAKE_CXX_STANDARD 20)

add_executable(generic01 main.cpp constexpr_math.h fp_math.h)
