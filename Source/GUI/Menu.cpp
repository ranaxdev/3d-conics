#include <cmath>
#include <iostream>
#include "Menu.h"

void Menu::editToggled() {
    if(editing){ // Bug: editing updates for listeners before this callback, so opposite here
        addFlags({ImGuiWindowFlags_NoInputs, ImGuiWindowFlags_NoBackground});
    }
    else{
        removeFlags({ImGuiWindowFlags_NoInputs, ImGuiWindowFlags_NoBackground});
    }
}

Menu::Menu(float alpha, float beta, int lod, bool isConic, surface s)
: alpha(alpha), beta(beta), lod(lod), isConic(isConic), s(s)
{
    // Register as KL
    KeyListener::listeners.push_back(this);

    // Init members
    Menu::pos  = ImVec2(0.0f, 0.0f);
    Menu::size = ImVec2(320.0f, 300.0f);

    Menu::breathe = false;
    Menu::breath_timer = 0.0f;
    Menu::amp = 0.5f;

    Menu::flag_list = {
            ImGuiWindowFlags_NoResize,
            ImGuiWindowFlags_NoInputs,
            ImGuiWindowFlags_NoBackground
    };
    updateFlags();

    Menu::alpha = 1.0f;
    Menu::beta = 1.0f;
    Menu::lod = 20;

    if(isConic)
        text_type = "CONIC";
    else
        text_type = "SURFACE";

    text_mesh = surface_names[s];
}

void Menu::update() {
    // Breathing function
    if(breathe){
        breath_timer += delta;
        alpha = 5+(5*sin(amp*breath_timer));
        beta = 5+(5*sin(amp*breath_timer));
    }

    // Window
    ImGui::SetNextWindowPos(pos);
    ImGui::SetNextWindowSize(size);
    ImGui::SetNextWindowFocus();

    ImGui::Begin("Control Menu", nullptr,
                 // Menu window properties
                 flags);

    // Surface state
    ImGui::Text("Press SPACE to enter Edit Mode\n\n");

    style->Colors[ImGuiCol_Text] = purple;
    ImGui::Text("%s\n", text_mesh);

    if(isConic)
        style->Colors[ImGuiCol_Text] = cyan;
    else
        style->Colors[ImGuiCol_Text] = green;
    ImGui::Text("%s\n", text_type);

    style->Colors[ImGuiCol_Text] = white;

    ImGui::SliderInt("   LOD", &lod, 5.0f, MAX_LOD);
    ImGui::SliderFloat("   alpha", &alpha, 0.1f, 10.0f);
    ImGui::SliderFloat("   beta", &beta, 0.1f, 10.0f);

    ImGui::Checkbox("Breath", &breathe);
    ImGui::SliderFloat("Amplitude", &amp, 0.1f, 5.0f);

    ImGui::End();
}