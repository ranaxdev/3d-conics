#ifndef _H_GUI_MENU
#define _H_GUI_MENU

#include "Surface.h"
#include "Globals.h"
#include "GUI.h"

class Menu : public GUI, public KeyListener{

public:
    Menu(float alpha, float beta, int lod, bool isConic, float t, surface s);

    void update() override;
    void editToggled() override;

protected:
    int load_mesh_config_callback(int argc, char **argv, char **azColName) override;

public:
    // Main
    surface s;
    float alpha, beta, amplitude, t;
    float max_alpha, min_alpha, max_beta, min_beta, max_time;
//    const char* text_alpha, *text_beta, *text_type, *text_mesh, *text_time;
    std::string text_alpha, text_beta, text_type, text_mesh, text_time;
    int lod;
    bool isConic;

    // Breathe functionality
    bool breathe_btn;
    float breathe_alpha_lim, breath_beta_lim;
    float breathe_timer;

    // Transform functionality
    bool x_rot_btn, y_rot_btn, z_rot_btn;
    float x_rot, y_rot, z_rot;
    float x_rot_timer, y_rot_timer, z_rot_timer;

    // Color controls
    bool plain;
    float color[3];

    ImVec2 pos;
    ImVec2 size;

};

#endif