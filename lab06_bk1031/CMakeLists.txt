cmake_minimum_required(VERSION 3.21)
project(lab06_bk1031)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab06_bk1031
        evalfull.cpp
        intstack.h
        usestack.cpp)
