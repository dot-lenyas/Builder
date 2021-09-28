cmake_minimum_required(VERSION 3.17)
project(builder)

set(CMAKE_CXX_STANDARD 17)

add_executable(builder main.cpp src/Method.h)