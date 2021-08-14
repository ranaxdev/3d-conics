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

Menu::Menu(float alpha, float beta, int lod, bool isConic, float t, surface s)
: alpha(alpha), beta(beta), lod(lod), isConic(isConic), t(t), s(s)
{
    // Register as KL
    KeyListener::listeners.push_back(this);

    // Init members
    Menu::pos  = ImVec2(0.0f, 0.0f);
    Menu::size = ImVec2(460.0f, SCREEN_H);

    // Init flags
    Menu::flag_list = {
            ImGuiWindowFlags_NoResize,
            ImGuiWindowFlags_NoInputs,
            ImGuiWindowFlags_NoBackground
    };
    updateFlags();

    // Configure properties
    load_mesh_config(s);


    Menu::breathe_btn = false;
    Menu::breathe_timer = 0.0f;

    Menu::breathe_alpha_lim = 0.0f;
    Menu::breath_beta_lim = 0.0f;
    Menu::text_mesh = surface_names[s];

    Menu::x_rot = 0.0f;
    Menu::y_rot = 0.0f;
    Menu::z_rot = 0.0f;
    Menu::x_rot_btn = false; Menu::x_rot_timer = 0.0f;
    Menu::y_rot_btn = false; Menu::y_rot_timer = 0.0f;
    Menu::z_rot_btn = false; Menu::z_rot_timer = 0.0f;

    Menu::plain = false;
    Menu::color[0] = 0.0f; Menu::color[1] = 1.0f; Menu::color[2] = 0.0f;
}

void Menu::update() {
    // Breathing function
    if(breathe_btn){
        breathe_timer += delta;
        alpha = (float)breathe_alpha_lim/2+((breathe_alpha_lim/2)*sin(amplitude*breathe_timer));
        beta = (float)breath_beta_lim/2+((breath_beta_lim/2)*sin(amplitude*breathe_timer));
    }

    if(x_rot_btn){
        x_rot_timer += delta;
        x_rot = (float) PI+(PI*sin(amplitude*x_rot_timer));
    }
    if(y_rot_btn){
        y_rot_timer += delta;
        y_rot= (float) PI+(PI*sin(amplitude*y_rot_timer));
    }
    if(z_rot_btn){
        z_rot_timer += delta;
        z_rot = (float) PI+(PI*sin(amplitude*z_rot_timer));
    }


    /* * * * * * * * * * * * * *
     *      GUI RENDERING
     * * * * * * * * * * * * * */
    ImGui::SetNextWindowPos(pos);
    ImGui::SetNextWindowSize(size);

    ImGui::Begin("Control Menu", &GUI::state, flags);

    ImGui::Text("Press SPACE to enter Edit Mode\n\n");


    ImGui::TextColored(purple, "%s\n", text_mesh.c_str());
    ImGui::TextColored(isConic ? cyan:green, "%s\n", text_type.c_str());

    // General settings
    ImGui::SliderInt("   LOD", &lod, 5, MAX_LOD);
    ImGui::SliderFloat(text_alpha.c_str(), &alpha, min_alpha, max_alpha);
    ImGui::SliderFloat(text_beta.c_str(), &beta, min_beta, max_beta);
    ImGui::SliderFloat(text_time.c_str(), &t, 1.0f, max_time);
    ImGui::SliderFloat("   Amplitude", &amplitude, 0.1f, 5.0f);

    // Breathe mode settings
    ImGui::TextColored(yellow, "\n\n===== BREATHE MODE =====");
    ImGui::Checkbox("Breathe On", &breathe_btn);
    ImGui::SliderFloat((std::string(text_alpha)+std::string(" lim")).c_str(), &breathe_alpha_lim, 0.1f, max_alpha);
    ImGui::SliderFloat((std::string(text_beta)+std::string(" lim")).c_str(), &breath_beta_lim, 0.1f, max_beta);
    ImGui::TextColored(yellow, "========================\n\n");

    // Transformation settings
    ImGui::TextColored(lblue, "====== TRANSFORM ======");
    ImGui::SliderFloat("   x-rot", &x_rot, 0.0f, 2*PI, "%.2f rads");
    ImGui::SliderFloat("   y-rot", &y_rot, 0.0f, 2*PI, "%.2f rads");
    ImGui::SliderFloat("   z-rot", &z_rot, 0.0f, 2*PI, "%.2f rads");

    ImGui::Checkbox("xRot", &x_rot_btn); ImGui::SameLine();
    ImGui::Checkbox("yRot", &y_rot_btn); ImGui::SameLine();
    ImGui::Checkbox("zRot", &z_rot_btn);
    ImGui::TextColored(lblue, "========================\n\n");

    // Color settings
    ImGui::TextColored(cyan, "========= COLOR =========");
    ImGui::Text("Select plain and color or deselect for ");
    ImGui::SameLine(); ImGui::TextColored(red,"R"); ImGui::SameLine(); ImGui::TextColored(orange,"A"); ImGui::SameLine();
    ImGui::TextColored(yellow, "I"); ImGui::SameLine(); ImGui::TextColored(green,"N"); ImGui::SameLine(); ImGui::TextColored(blue,"B");
    ImGui::SameLine(); ImGui::TextColored(indigo, "O"); ImGui::SameLine(); ImGui::TextColored(violet, "W");

    ImGui::Checkbox("Plain", &plain);
    ImGui::ColorEdit3("Select Color", color);
    ImGui::TextColored(cyan, "========================\n\n");

    ImGui::End();

}

int Menu::load_mesh_config_callback(int argc, char **argv, char **azColName) {
    Menu::text_mesh     = argv[1];
    Menu::alpha         = std::stof(argv[2]);
    Menu::beta          = std::stof(argv[3]);
    Menu::amplitude     = std::stof(argv[4]);
    Menu::t             = std::stof(argv[5]);
    Menu::lod           = std::stoi(argv[6]);
    Menu::isConic       = std::stoi(argv[7]);
    Menu::max_alpha     = std::stof(argv[8]);
    Menu::min_alpha     = std::stof(argv[9]);
    Menu::max_beta      = std::stof(argv[10]);
    Menu::min_beta      = std::stof(argv[11]);
    Menu::max_time      = std::stof(argv[12]);
    Menu::text_alpha    = argv[13];
    Menu::text_beta     = argv[14];
    Menu::text_time     = argv[15];
    Menu::text_type     = argv[16];

    return 0;
}
