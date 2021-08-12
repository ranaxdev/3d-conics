#include <iostream>

#include "Spawner.h"


Spawner::Spawner() {
    Spawner::size = ImVec2(360.0f, 360.0f);
    Spawner::pos = ImVec2(SCREEN_W-size.x, 0.0f);

    Spawner::enableAxis = true;

    Spawner::flag_list = {
            ImGuiWindowFlags_MenuBar
    };
    updateFlags();



}

void Spawner::update() {
    /* * * * * * * * * * * * * *
     *      GUI RENDERING
     * * * * * * * * * * * * * */
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


    ImGui::End();
}


void Spawner::disableExcept(int i) {
    for(int j=0; j<surface::END+1; j++){
        if(j != i)
            Spawner::mesh_items_selected[j] = false;
    }
}

