cmake_minimum_required(VERSION 3.15)
project(MyMVC)

set(CMAKE_CXX_STANDARD 14)

add_executable(MyMVC main.cpp Request/Request.cpp Request/Request.h Response/Response.cpp Response/Response.h Listener/Listener.cpp Listener/Listener.h)