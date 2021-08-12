#ifndef _H_GUI_MENU
#define _H_GUI_MENU

#include "Surface.h"
#include "Globals.h"
#include "GUI.h"

class Menu : public GUI, public KeyListener{

public:
    Menu(float alpha, float beta, int lod, bool isConic, surface s);

    void update() override;

    void editToggled() override;


    float alpha, beta, amp, breath_timer;
    int lod;
    bool breathe;
    bool isConic;
    surface s;
    float MAX_ALPHA, MIN_ALPHA, MAX_BETA, MIN_BETA;
    float breath_alpha_limit;
    float breath_beta_limt;
    float x_trans, y_trans, z_trans;

    ImVec2 pos;
    ImVec2 size;
    const char* text_type;
    const char* text_mesh;
    const char* text_alpha;
    const char* text_beta;

};

#endif