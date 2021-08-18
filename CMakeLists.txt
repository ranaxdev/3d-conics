cmake_minimum_required(VERSION 3.19)
project(3Dconics)

set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY GLOBAL_DEPENDS_DEBUG_MODE 1)


add_subdirectory(external/sqlite)
add_subdirectory(external/glfw)
add_subdirectory(external/imgui)
add_subdirectory(external/glad)

# external/imgui/imgui.cpp external/imgui/imgui_demo.cpp external/imgui/imgui_draw.cpp external/imgui/imgui_impl_glfw.cpp external/imgui/imgui_impl_opengl3.cpp external/imgui/imgui_tables.cpp external/imgui/imgui_widgets.cpp
add_executable(${PROJECT_NAME} Source/main.cpp Source/Harness.cpp Include/Harness.h Source/Shader.cpp Include/Shader.h Source/Camera.cpp Include/Camera.h Include/KeyListener.h Include/Math.h Source/Utils/Logger.cpp Include/Logger.h Include/Globals.h Source/Renderer.cpp Include/Renderer.h Source/Mesh.cpp Include/Mesh.h Source/GUI/GUI.cpp Include/GUI.h Source/GUI/Menu.cpp Include/Menu.h Source/Utils/KeyListener.cpp Include/Surface.h Source/GUI/Spawner.cpp Include/Spawner.h)


include_directories(Include)

target_link_libraries(3Dconics GLAD IMGUI SQLITE glfw dl pthread)

target_include_directories(${PROJECT_NAME} PUBLIC
            "${PROJECT_SOURCE_DIR}/external"
            "${PROJECT_SOURCE_DIR}/external/sqlite/include"
            "${PROJECT_SOURCE_DIR}/external/imgui/include"
            "${PROJECT_SOURCE_DIR}/external/glfw/include"
            "${PROJECT_SOURCE_DIR}/external/glad/include"
        )