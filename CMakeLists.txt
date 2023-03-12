cmake_minimum_required(VERSION 3.24)
project(CPP_Projekt1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CPP_Projekt1
        List.cpp
        List.h
        main.cpp Tab.h Tab.cpp)
