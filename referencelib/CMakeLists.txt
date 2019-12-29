cmake_minimum_required(VERSION 3.15)
project(referencelib)

set(CMAKE_CXX_STANDARD 14)

add_executable(referencelib main.cpp base/Object.cpp base/Object.h base/Reference.hpp allocator/allocator.cpp allocator/Allocator.hpp allocator/Allocator.h container/List.h container/Container.h container/List/Vector.hpp base/Pointer.hpp)