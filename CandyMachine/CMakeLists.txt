cmake_minimum_required(VERSION 3.26)
project(CandyMachine)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE=1 -finput-charset=UTF-8 -fexec-charset=UTF-8")

set(CMAKE_CXX_STANDARD 17)

add_executable(CandyMachine main.cpp
        CandyMachine.cpp
        CandyMachine.h
        states.cpp
        states.h)
