cmake_minimum_required(VERSION 3.19)
project(IMGUI)
add_library(IMGUI imgui.cpp imgui_demo.cpp imgui_draw.cpp imgui_impl_glfw.cpp imgui_impl_opengl3.cpp imgui_tables.cpp imgui_widgets.cpp)

target_include_directories(IMGUI PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../glad/include")
target_link_libraries(IMGUI glfw GLAD)

