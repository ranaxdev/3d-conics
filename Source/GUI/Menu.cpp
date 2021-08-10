#include <cmath>
#include "Menu.h"


Menu::Menu(float alpha, float beta, int lod)
: alpha(alpha), beta(beta), lod(lod)
{
    Menu::pos  = ImVec2(0.0f, 0.0f);
    Menu::size = ImVec2(320.0f, 300.0f);

    Menu::breathe = false;
    Menu::amp = 0.5f;

    Menu::flag_list = {
            ImGuiWindowFlags_NoResize,
            ImGuiWindowFlags_NoInputs,
            ImGuiWindowFlags_NoBackground
    };
}


void Menu::update() {
    if(breathe){
        alpha = 5+(5*sin(amp*glfwGetTime()));
        beta = 5+(5*sin(amp*glfwGetTime()));
    }

    ImGui::SetNextWindowPos(pos);
    ImGui::SetNextWindowSize(size);
    ImGui::SetNextWindowFocus();

    ImGui::Begin("Control Menu", nullptr,
                 // Menu window properties
                 flags);

    // Surface state
    ImGui::Text("Press SPACE to enter Edit Mode\n\n");
    ImGui::SliderInt("   LOD", &lod, 5.0f, MAX_LOD);
    ImGui::SliderFloat("   alpha", &alpha, 0.1f, 10.0f);
    ImGui::SliderFloat("   beta", &beta, 0.1f, 10.0f);

    ImGui::Checkbox("Breath", &breathe);
    ImGui::SliderFloat("Amplitude", &amp, 0.1f, 5.0f);

    ImGui::End();
}

