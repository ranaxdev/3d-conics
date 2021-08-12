#include "Spawner.h"


Spawner::Spawner() {
    Spawner::state = true;
    Spawner::size = ImVec2(360.0f, 360.0f);
    Spawner::pos = ImVec2(SCREEN_W-size.x, 0.0f);

}

void Spawner::update() {
    /* * * * * * * * * * * * * *
     *      GUI RENDERING
     * * * * * * * * * * * * * */
    ImGui::SetNextWindowSize(size);
    ImGui::SetNextWindowPos(pos);
    ImGui::SetNextWindowFocus();

    style->Colors[ImGuiCol_Text] = white;
    ImGui::Begin("Spawner", &state, flags);

    ImGui::End();
}

