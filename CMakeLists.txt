cmake_minimum_required(VERSION 3.19)
project(3Dconics)

set(CMAKE_CXX_STANDARD 17)

add_executable(3Dconics Source/main.cpp glad.c Source/Harness.cpp Source/Harness.h Source/Shader.cpp Source/Shader.h Source/Camera.cpp Source/Camera.h Source/Utils/KeyListener.h)
target_link_libraries(3Dconics glfw3 GL dl pthread)