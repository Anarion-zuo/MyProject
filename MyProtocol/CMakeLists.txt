cmake_minimum_required(VERSION 3.15)
project(MyProtocol)

set(CMAKE_CXX_STANDARD 14)

add_executable(MyProtocol main.cpp DatagramChannel/DatagramChannel.cpp DatagramChannel/DatagramChannel.h)