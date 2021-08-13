#include <cmath>
#include <iostream>
#include <string>
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
    Menu::size = ImVec2(400.0f, SCREEN_H);

    Menu::breathe = false;
    Menu::breath_timer = 0.0f;
    Menu::amp = 0.5f;
    Menu::t = 1.0f;

    Menu::flag_list = {
            ImGuiWindowFlags_NoResize,
            ImGuiWindowFlags_NoInputs,
            ImGuiWindowFlags_NoBackground
    };
    updateFlags();



    if(isConic){
        Menu::text_type = "CONIC";
        Menu::text_alpha = "   h-range";
        Menu::text_beta = "   angle (rad)";
        Menu::MAX_ALPHA = 10.0f;
        Menu::MIN_ALPHA = 0.1f;
        Menu::MAX_BETA = 2*PI;
        Menu::MIN_BETA = 0.0f;
    }
    else{
        Menu::text_type = "SURFACE";
        Menu::text_alpha = "   x-range";
        Menu::text_beta = "   y-range";
        Menu::MAX_ALPHA = 5.0f;
        Menu::MIN_ALPHA = -5.0f;
        Menu::MAX_BETA = 5.0f;
        Menu::MIN_BETA = -5.0f;
    }
    Menu::breath_alpha_limit = Menu::MAX_ALPHA/2;
    Menu::breath_beta_limit = Menu::MAX_BETA/2;
    Menu::text_mesh = surface_names[s];

    Menu::x_trans = 0.0f;
    Menu::y_trans = 0.0f;
    Menu::z_trans = 0.0f;
    Menu::xrot = false; Menu::xrot_timer = 0.0f;
    Menu::yrot = false; Menu::yrot_timer = 0.0f;
    Menu::zrot = false; Menu::zrot_timer = 0.0f;
}

void Menu::update() {
    // Breathing function
    if(breathe){
        breath_timer += delta;
        alpha = (float)(breath_alpha_limit*sin(amp*breath_timer));
        beta = (float)(breath_beta_limit*sin(amp*breath_timer));
    }

    if(xrot){
        xrot_timer += delta;
        x_trans = (float) PI+(PI*sin(amp*xrot_timer));
    }
    if(yrot){
        yrot_timer += delta;
        y_trans= (float) PI+(PI*sin(amp*yrot_timer));
    }
    if(zrot){
        zrot_timer += delta;
        z_trans = (float) PI+(PI*sin(amp*zrot_timer));
    }


    /* * * * * * * * * * * * * *
     *      GUI RENDERING
     * * * * * * * * * * * * * */
    ImGui::SetNextWindowPos(pos);
    ImGui::SetNextWindowSize(size);

    ImGui::Begin("Control Menu", &GUI::state, flags);

    ImGui::Text("Press SPACE to enter Edit Mode\n\n");


    ImGui::TextColored(purple, "%s\n", text_mesh);
    ImGui::TextColored(isConic ? cyan:green, "%s\n", text_type);

    // General settings
    ImGui::SliderInt("   LOD", &lod, 5, MAX_LOD);
    ImGui::SliderFloat(text_alpha, &alpha, MIN_ALPHA, MAX_ALPHA);
    ImGui::SliderFloat(text_beta, &beta, MIN_BETA, MAX_BETA);
    ImGui::SliderFloat("   t", &t, 1.0f, 5.0f);
    ImGui::SliderFloat("   Amplitude", &amp, 0.1f, 5.0f);

    // Breathe mode settings
    ImGui::TextColored(yellow, "\n\n===== BREATHE MODE =====");
    ImGui::Checkbox("Breathe On", &breathe);
    ImGui::SliderFloat((std::string(text_alpha)+std::string(" lim")).c_str(), &breath_alpha_limit, 0.1f, MAX_ALPHA);
    ImGui::SliderFloat((std::string(text_beta)+std::string(" lim")).c_str(), &breath_beta_limit, 0.1f, MAX_BETA);
    ImGui::TextColored(yellow, "========================\n\n");

    // Transformation settings
    ImGui::TextColored(lblue, "===== TRANSFORM =====");
    ImGui::SliderFloat("   x-rot", &x_trans, 0.0f, 2*PI, "%.2f rads");
    ImGui::SliderFloat("   y-rot", &y_trans, 0.0f, 2*PI, "%.2f rads");
    ImGui::SliderFloat("   z-rot", &z_trans, 0.0f, 2*PI, "%.2f rads");

    ImGui::Checkbox("xRot", &xrot); ImGui::SameLine();
    ImGui::Checkbox("yRot", &yrot); ImGui::SameLine();
    ImGui::Checkbox("zRot", &zrot);

    ImGui::TextColored(lblue, "========================\n\n");

    ImGui::End();

}