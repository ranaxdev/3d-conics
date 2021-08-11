#ifndef _H_GUI_MENU
#define _H_GUI_MENU

#include "Globals.h"
#include "GUI.h"

class Menu : public GUI, public KeyListener{

public:
    Menu(float alpha, float beta, int lod);

    void update() override;

    void editToggled() override;


    float alpha, beta, amp, breath_timer;
    int lod;
    bool breathe;

    ImVec2 pos;
    ImVec2 size;

};

#endif