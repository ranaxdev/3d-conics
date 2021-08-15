#include <iostream>
#include <string>
#include "Spawner.h"


Spawner::Spawner() {
    // Init members
    Spawner::size = ImVec2(360.0f, 360.0f);
    Spawner::pos = ImVec2(SCREEN_W-size.x, 0.0f);

    Spawner::lod = 5; Spawner::alpha = 0.0f, Spawner::beta = 0.0f;
    Spawner::t = 0.0f;
    Spawner::min_alpha = 0.0f; Spawner::max_alpha = 0.0f;
    Spawner::min_beta = 0.0f; Spawner::max_beta = 0.0f;
    Spawner::max_time = 0.0f;

    Spawner::enableAxis = true;
    Spawner::current_surface = END;
    Spawner::mesh_generated = false;

    // Init flags
    Spawner::flag_list = {
            ImGuiWindowFlags_MenuBar
    };
    updateFlags();

}

void Spawner::update() {
    /* * * * * * * * * * * * * *
     *      GUI RENDERING
     * * * * * * * * * * * * * */
    if(Spawner::mesh_generated)
        Spawner::mesh_generated = false;

    ImGui::SetNextWindowSize(size);
    ImGui::SetNextWindowPos(pos);

    ImGui::Begin("Spawner", &GUI::state, flags);
    ImGui::Checkbox("   Enable Axis", &enableAxis);


    // Mesh Selection Menubar
    if(ImGui::BeginMenuBar()){
        if(ImGui::BeginMenu("Select Mesh")){
            for(int i=0; i < surface::END+1; i++){
                // Ignore checkpoints
                if(i == SEPARATOR || i == END)
                    continue;

                // Selects only 1 mesh at a time (disables rest)
                if(ImGui::MenuItem(surface_names[i], nullptr, &mesh_items_selected[i])){
                    disableExcept(i);
                }
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    // Display mesh creation options for the currently selected mesh
    int active = findActive();
    if(active > -1){
        // Load default config of selected mesh into members
        load_mesh_config(static_cast<surface>(active));

        ImGui::TextColored(purple, "%s", (std::string("\nCREATING ")+std::string(surface_names[active])).c_str());
        ImGui::TextColored(yellow, "Select Initial Mesh Properties:");

        ImGui::SliderInt("   LOD", &lod, 5, 200);
        ImGui::SliderFloat(text_alpha.c_str(), &alpha, min_alpha, max_alpha);
        ImGui::SliderFloat(text_beta.c_str(), &beta, min_beta, max_beta);
        ImGui::SliderFloat(text_time.c_str(), &t, 1.0f, max_time);

        // Generate mesh button
        if(ImGui::Button("Generate")){
            Spawner::mesh_generated = true;
            current_surface = static_cast<surface>(active);
            mesh_items_selected[active] = false;
        }
    }

    ImGui::End();
}


void Spawner::disableExcept(int i) {
    for(int j=0; j<surface::END+1; j++){
        if(j != i)
            Spawner::mesh_items_selected[j] = false;
    }
}

int Spawner::findActive() {
    int i = -1;
    for(int j=0; j<surface::END+1; j++){
        if(mesh_items_selected[j]){
            i = j;
            return i;
        }
    }
    return i;
}

int Spawner::load_mesh_config_callback(int argc, char **argv, char **azColName) {
    Spawner::alpha         = std::stof(argv[2]);
    Spawner::beta          = std::stof(argv[3]);
    Spawner::t             = std::stof(argv[5]);
    Spawner::lod           = std::stoi(argv[6]);
    Spawner::isConic       = std::stoi(argv[7]);
    Spawner::max_alpha     = std::stof(argv[8]);
    Spawner::min_alpha     = std::stof(argv[9]);
    Spawner::max_beta      = std::stof(argv[10]);
    Spawner::min_beta      = std::stof(argv[11]);
    Spawner::max_time      = std::stof(argv[12]);
    Spawner::text_alpha    = argv[13];
    Spawner::text_beta     = argv[14];
    Spawner::text_time     = argv[15];
    Spawner::text_type     = argv[16];
    return 0;
}
