cmake_minimum_required(VERSION 3.15)
project(referencelib)

set(CMAKE_CXX_STANDARD 14)

add_executable(referencelib main.cpp base/Object.cpp base/Object.h base/Reference.hpp)