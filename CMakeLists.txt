cmake_minimum_required(VERSION 3.25)
project(PROG2400_lectures)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-static")

add_executable(hello_world hello_world/main.cpp)
add_executable(echo echo/main.cpp)
add_executable(command_line command_line/main.cpp)
add_executable(command_parser command_parser/main.cpp)
add_executable(pointers pointers/main.cpp)