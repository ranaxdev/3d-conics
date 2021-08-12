#include "Spawner.h"


Spawner::Spawner() {
    Spawner::size = ImVec2(360.0f, 360.0f);
    Spawner::pos = ImVec2(SCREEN_W-size.x, 0.0f);

    Spawner::enableAxis = true;

    Spawner::flag_list = {

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
    ImGui::End();
}

