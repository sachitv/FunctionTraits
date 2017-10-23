cmake_minimum_required(VERSION 3.2)
project(FunctionTraits)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        headers/functiontraits.h
        unittests.cpp)

add_executable(FunctionTraits ${SOURCE_FILES})