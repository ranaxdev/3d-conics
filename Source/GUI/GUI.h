#ifndef _H_GUI
#define _H_GUI

#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_glfw.h"
#include "../../imgui/imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "../Utils/Globals.h"

class GUI{
public:
    GUI() = default;
    ~GUI() = default;

    virtual void update() = 0;

    void addFlags(std::vector<ImGuiWindowFlags_>&& flags);
    void removeFlags(std::vector<ImGuiWindowFlags_>&& flags);

protected:
    std::vector<ImGuiWindowFlags_> flag_list;
    ImGuiWindowFlags_ flags = ImGuiWindowFlags_None;

    void updateFlags();

};

#endif