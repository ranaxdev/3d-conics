#ifndef _H_GUI
#define _H_GUI

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "KeyListener.h"
#include "Globals.h"

class GUI{
public:
    GUI() = default;
    ~GUI();

    virtual void update() = 0;

    void addFlags(std::vector<ImGuiWindowFlags_>&& flags);
    void removeFlags(std::vector<ImGuiWindowFlags_>&& flags);

protected:
    std::vector<ImGuiWindowFlags_> flag_list;
    ImGuiWindowFlags_ flags = ImGuiWindowFlags_None;

    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4 green    =     ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
    ImVec4 cyan     =     ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
    ImVec4 purple   =     ImVec4(1.0f, 0.0f, 1.0f ,1.0f);
    ImVec4 white    =     ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    ImVec4 yellow   =     ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
    ImVec4 lblue    =     ImVec4(0.47f, 0.54f, 1.0f, 1.0f);

    void updateFlags();
    static bool state;

};

#endif