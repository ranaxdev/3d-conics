#ifndef _H_GUI
#define _H_GUI

#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_glfw.h"
#include "../../imgui/imgui_impl_opengl3.h"

#include <vector>

class GUI{
public:
    GUI() = default;
    virtual ~GUI() = 0;

    virtual void plug(...) =0;
    virtual void update() = 0;

    void addFlags(std::vector<ImGuiWindowFlags_>&& flags);
    void removeFlags(std::vector<ImGuiWindowFlags_>&& flags);

private:

    std::vector<ImGuiWindowFlags_> flag_list;
    ImGuiWindowFlags_ flags = ImGuiWindowFlags_None;

    void updateFlags();

};

#endif