cmake_minimum_required(VERSION 3.21)
project(lab01_bk1031)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab01_bk1031
        car.cpp
        car.hpp
        doors.hpp
        main.cpp
        perf.cpp
        perf.hpp)
