cmake_minimum_required(VERSION 3.14)
project(myclib C)

set(CMAKE_C_STANDARD 99)

add_executable(myclib main.c memory-management/allocator.c memory-management/allocator.h erronos.h memory-management/vector.c memory-management/vector.h memory-management/list.c memory-management/list.h)

