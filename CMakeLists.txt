cmake_minimum_required(VERSION 3.26)
project(Math_Template)

set(CMAKE_CXX_STANDARD 17)

add_executable(Math_Template main.cpp
        Random/Random_Generator.h
        Random/Random_Generator.cpp
        Random/Random_MT19937.h
        Random/Random_MT19937.cpp
)

message(WARNING "Stale copy of ./Random, please import from library")