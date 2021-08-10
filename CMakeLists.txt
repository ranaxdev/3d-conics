cmake_minimum_required(VERSION 3.19)
project(3Dconics)
set(CMAKE_CXX_STANDARD 17)

add_executable(3Dconics imgui/imgui.cpp imgui/imgui_demo.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp imgui/imgui_impl_glfw.cpp imgui/imgui_impl_opengl3.cpp imgui/imgui_widgets.cpp Source/main.cpp glad.c Source/Harness.cpp Source/Harness.h Source/Shader.cpp Source/Shader.h Source/Camera.cpp Source/Camera.h Source/Utils/KeyListener.h Source/Utils/Math.h Source/Utils/Logger.cpp Source/Utils/Logger.h Source/Utils/Globals.h Source/Model.cpp Source/Model.h Source/Renderer.cpp Source/Renderer.h Source/Mesh.cpp Source/Mesh.h)
target_link_libraries(3Dconics glfw3 GL dl pthread)