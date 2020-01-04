cmake_minimum_required(VERSION 3.15)
project(TestLib)

set(CMAKE_CXX_STANDARD 14)

add_executable(TestLib main.cpp)
target_link_libraries(TestLib referencelib)