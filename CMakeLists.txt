cmake_minimum_required(VERSION 3.19)
project(3Dconics)

set(CMAKE_CXX_STANDARD 14)

add_executable(3Dconics main.cpp glad.c Source/Harness.cpp Source/Harness.h)
target_link_libraries(3Dconics glfw3 GL dl pthread)