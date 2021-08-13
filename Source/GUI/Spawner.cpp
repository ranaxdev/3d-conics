#include <iostream>
#include <string>
#include "Spawner.h"


Spawner::Spawner() {
    Spawner::size = ImVec2(360.0f, 360.0f);
    Spawner::pos = ImVec2(SCREEN_W-size.x, 0.0f);

    Spawner::enableAxis = true;

    Spawner::current_surface = END;
    Spawner::mesh_generated = false;
    Spawner::text_alpha = ""; Spawner::text_beta = "";
    Spawner::lod = 5; Spawner::alpha = 0.0f, Spawner::beta = 0.0f;
    Spawner::MIN_ALPHA = 0.0f; Spawner::MAX_ALPHA = 0.0f;
    Spawner::MIN_BETA = 0.0f; Spawner::MAX_BETA = 0.0f;

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
        isConic = active > surface::SEPARATOR;
       if(isConic){
            text_alpha = "   height";
            text_beta = "   angle (rad)";
            Spawner::MAX_ALPHA = 10.0f;
            Spawner::MIN_ALPHA = 0.1f;
            Spawner::MAX_BETA = 2*PI;
            Spawner::MIN_BETA = 0.0f;
        }
       else {
            text_alpha = "   x-range";
            text_beta = "   y-range";
            Spawner::MAX_ALPHA = 5.0f;
            Spawner::MIN_ALPHA = -5.0f;
            Spawner::MAX_BETA = 5.0f;
            Spawner::MIN_BETA = -5.0f;
        }

        ImGui::TextColored(purple, "%s", (std::string("\nCREATING ")+std::string(surface_names[active])).c_str());
        ImGui::TextColored(yellow, "Select Initial Mesh Properties:");

        ImGui::SliderInt("   LOD", &lod, 5, 200);
        ImGui::SliderFloat(text_alpha, &alpha, MIN_ALPHA, MAX_ALPHA);
        ImGui::SliderFloat(text_beta, &beta, MIN_BETA, MAX_BETA);

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

