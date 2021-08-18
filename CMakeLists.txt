cmake_minimum_required(VERSION 3.19)
project(3Dconics)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES Source/main.cpp Source/Harness.cpp Include/Harness.h Source/Shader.cpp Include/Shader.h Source/Camera.cpp Include/Camera.h Include/KeyListener.h Source/Utils/Logger.cpp Include/Logger.h Include/Globals.h Source/Renderer.cpp Include/Renderer.h Source/Mesh.cpp Include/Mesh.h Source/GUI/GUI.cpp Include/GUI.h Source/GUI/Menu.cpp Include/Menu.h Source/Utils/KeyListener.cpp Include/Surface.h Source/GUI/Spawner.cpp Include/Spawner.h)

set(IMGUI_SOURCE_FILES
        external/imgui/imgui.cpp
        external/imgui/imgui_demo.cpp
        external/imgui/imgui_draw.cpp
        external/imgui/imgui_impl_glfw.cpp
        external/imgui/imgui_impl_opengl3.cpp
        external/imgui/imgui_tables.cpp
        external/imgui/imgui_widgets.cpp)

set(GLAD_SOURCE_FILES external/glad/glad.c)

set(SQLITE_SOURCE_FILES
        external/sqlite/sqlite3.c
        )


#           DOWNLOAD ALL THE SUBMODULES
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

add_subdirectory(external/glfw)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${IMGUI_SOURCE_FILES} ${GLAD_SOURCE_FILES} ${SQLITE_SOURCE_FILES})

include_directories(Include)

target_link_libraries(${PROJECT_NAME} glfw dl pthread)

target_include_directories(${PROJECT_NAME} PUBLIC
        "${PROJECT_SOURCE_DIR}/external/glfw/include")
